#include "Bus.hpp"

#include <iostream>
#include <stdlib.h>

#define WAITTIME 4

pthread_mutex_t Bus::reqresp_lock;
pthread_cond_t Bus::reqresp_cvar;

int Bus::reqresp_count;
int Bus::owner_id;
int Bus::cores;

MemRequest Bus::request;
long Bus::acq_time;
long Bus::act_time; //amount of time bus was active
int Bus::wait;

operations Bus::opt;

void Bus::init(int num_cores) {
    std::cout<<"Initializing Bus...";

    pthread_mutex_init(&reqresp_lock, NULL);
    pthread_cond_init(&reqresp_cvar, NULL);
    reqresp_count = 0;
    owner_id = 0;
     = 0;
    opt = UNACT;
    cores = num_cores;
    acq_time = -1;
    wait = WAITTIME;
    act_time = 0;

    std::cout<<"done!\n";
}

/* return 0 when not acquired */
int Bus::acquire(int id, unsigned long address, operations oper) {
    pthread_mutex_lock(&reqresp_lock);
    if (acq_time != -1) {
        pthread_mutex_unlock(&reqresp_lock);
        return 0;
    }
    addr = address;
    opt = oper;
    wait = WAITTIME;
    reqresp_count++;
    owner_id = id;

    pthread_mutex_unlock(&reqresp_lock);
    return 1;
}

operations Bus::status() {
    return opt;
}
