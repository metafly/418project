#ifndef _BUS_H_
#define _BUS_H_
#include "Memory.hpp"
#include <pthread.h>
#include <vector>

enum operations {
    UNACT = 0,
    REQ,
    RESP
};

class Bus {

    public:
        static pthread_mutex_t reqresp_lock;
        static pthread_cond_t reqresp_cvar;
        static int reqresp_count;
        static int owner_id;
        MemRequest request;
        static int cores;
        static long acq_time;
        static long act_time;
        static int wait;

        static operations opt;

        static void init(int num_cores);
        static int acquire(int id, unsigned long address, operations oper);
        static operations status();

};

#endif
