#include "Memory.hpp"
#include "Bus.hpp"
#include "Directory.hpp"

#include <string>
#include <iostream>
#include <unistd.h>
#include <vector>
#include <stdlib.h>

#define DRAMSIZE 64000

std::vector<MemRequest *> Memory::req_table;
unsigned long Memory::low_add;
unsigned long Memory::upp_add;
Directory Memory::directory;
int Memory::num_cores;
std::string Memory::cache_protocol;
ProtocolType Memory::protocol;
MemRequest Memory::curr_request;
bool Memory::valid_req;

void Memory::mem_init(std::string processor, int cores, int procID, std::string cache_pcl) {
    num_cores = cores;

    if(processor.compare("UMA") == 0) {
        low_add = 0;
        upp_add = DRAMSIZE;
    }
    else if(processor.compare("NUMA") == 0) {
        int size = DRAMSIZE/cores;
        low_add = procID*size;
        upp_add = low_add + size;
    }
    else if(processor.compare("HYBRID") == 0) {
        if (procID < 4) {
            low_add = 0;
            upp_add = DRAMSIZE/2 - 1;
        }
        else {
            low_add = DRAMSIZE/2;
            upp_add = DRAMSIZE;
        }
    }

    directory.init(cores);

    if(cache_pcl.compare("MSI") == 0) {
        protocol = ProtocolType::MSI;
    }
    else if(cache_pcl.compare("MESI") == 0) {
        protocol = ProtocolType::MESI;
    }
    else if(cache_pcl.compare("MOSI") == 0) {
        protocol = ProtocolType::MOSI;
    }

    valid_req = false;
    curr_request(-1, -1, 0, -1);

}

int Memory::mem_cycle() {
    operations bus_status = Bus::status();

    if (bus_status == operations::UNACT) {
        if(valid_req == false) {
            return 1;
        }

        int acquire = Bus:;acquire(




    return 1;
}


