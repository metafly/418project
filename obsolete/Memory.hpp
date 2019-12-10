#ifndef _MEMORY_H_
#define _MEMORY_H_

#include "Directory.hpp"
#include <stdlib.h>
#include <unistd.h>

enum RequestType {READ=0, WRITE};

enum ProtocolType { MSI=0, MESI, MOSI};

class MemRequest {
    public:
        int procID;
        unsigned long addr;
        RequestType type;
        long request_time;
        long wait_time;

        MemRequest(int pID, unsigned long a, RequestType t, long reqt) {
            procID = pID;
            addr = a;
            type = t;
            request_time = reqt;
        }
        //make waittime as 0 initially
}

class Memory {
    public:
        static int num_cores;
        static std::vector<MemRequest *> req_table;
        static unsigned long low_add;
        static unsigned long upp_add;
        static Directory directory;
        static ProtocolType protocol;
        static MemRequest curr_request;
        static bool valid_req;
        static void mem_init(std:;string processor, int cores, int procID, std::string cache_pcl)
};






#endif
