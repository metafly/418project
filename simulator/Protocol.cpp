/**
 * The implementation for the Protocol class. Holds the important state for
 * the cache simulator to work
 *
 * Authors :-
 * Kshitiz Dange <kdange@andrew.cmu.edu>
 * Yash Tibrewal <ytibrewa@andrew.cmu.edu>
 * Shivani Prasad <sprasad1>
 */

#include <iostream>
#include <pthread.h>
#include <vector>
#include <assert.h>
#include "Protocol.h"
#include "MSI.h"
#include "MESI.h"
#include "MOSI.h"
#include "MOESI.h"
#include "Dragon.h"
#include "CompSnooping.h"
#include "Cache.h"
#include "MESIF.h"

pthread_mutex_t Protocol::lock;
pthread_cond_t Protocol::trace_cv;
pthread_cond_t Protocol::worker_cv;
bool Protocol::ready;
int Protocol::request_id;
std::string Protocol::request_op;
unsigned long Protocol::request_addr;
int Protocol::num_cores;
std::vector<SnoopingCache *> Protocol::sn_caches;

//Variables needed for MESIF protocol, if a forward state is evicted
bool Protocol::forward_evicted;
unsigned long Protocol::f_tag;
unsigned long Protocol::f_set;

std::atomic<long> Protocol::bus_transactions;
std::atomic<long> Protocol::mem_reqs;
std::atomic<long> Protocol::mem_write_backs;
std::atomic<long> Protocol::cache_transfers;
std::atomic<long> Protocol::trace_count;

std::atomic<long> Protocol::cache_miss;
std::atomic<long> Protocol::cache_hits;
std::atomic<long> Protocol::cache_evict;
std::atomic<long> Protocol::num_invalids;
std::atomic<long> Protocol::num_modified;

/**
 * Initialize the Protocol
 */
void Protocol::initialize(std::string protocol, int num_cores, int cache_size,
                                int associativity) {
    Protocol::num_cores = num_cores;
    pthread_mutex_init(&lock, NULL);
    pthread_cond_init(&worker_cv, NULL);
    pthread_cond_init(&trace_cv, NULL);

    /* Set cache properties */
    Cache::cache_init((long)cache_size, (long)associativity);
    for(int i = 0; i < num_cores; i++) {
        if(protocol == "MSI") {
            sn_caches.push_back(new MSI(i));
        } else if(protocol == "MESI") {
            sn_caches.push_back(new MESI(i));
        } else if(protocol == "MOSI") {
            sn_caches.push_back(new MOSI(i));
        } else if(protocol == "MOESI") {
            sn_caches.push_back(new MOESI(i));
        } else if(protocol == "Dragon") {
            sn_caches.push_back(new Dragon(i));
        } else if(protocol == "CompSnooping") {
            sn_caches.push_back(new CompSnooping(i));
        } else if(protocol == "MESIF") {
            sn_caches.push_back(new MESIF(i));
        } else {
            assert(0);
        }
    }

    /* Initialize metrics */
    Protocol::cache_miss = 0;
    Protocol::cache_hits = 0;
    Protocol::cache_evict = 0;
    Protocol::num_invalids = 0;
    Protocol::num_modified = 0;

    Protocol::forward_evicted = false;
}

/**
 * Called by the trace worker to forward a request to proper processor
 */
void Protocol::process_mem_access(int thread_id, std::string op,
                                            unsigned long addr) {
    pthread_mutex_lock(&lock);
    while(ready) {
        pthread_cond_wait(&trace_cv, &lock);
    }
    request_id = thread_id;
    request_op = op;
    /* Reset the block bits of the address */
    assert(addr);
    request_addr = addr & (~((1 << Cache::block_bits) - 1));
    assert(request_addr);
    ready = true;
    pthread_cond_broadcast(&worker_cv);
    pthread_mutex_unlock(&lock);

    if(Protocol::forward_evicted) {
        for(int i = 0; i < num_cores; i++) {

            pthread_mutex_lock(&sn_caches[i]->lock);
            if(sn_caches[i]->cache.cache_check_tag_status(Protocol::f_tag, Protocol::f_set) == Shared) {
                sn_caches[i]->cache.cache_set_cache_tag_status(Protocol::f_tag, Protocol::f_set);
                pthread_mutex_unlock(&sn_caches[i]->lock);
                break;
            }
            pthread_mutex_unlock(&sn_caches[i]->lock);
        }
    }
}


