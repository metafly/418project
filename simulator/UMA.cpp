
#include "UMA.hpp"
#include "Bus.hpp"

#include <iostream>
#include <vector>
#include <fstream>
#include <atomic>
#include <unistd.h>
#include <stdlib.h>
#include <string>


int numTasks;
std::vector<task *> task_list;

void process_trace_file(std::string src) {
    std::ifstream tracefile(src.c_str());
    if !(tracefile) {
        std::cerr <<"Cound not open file: "<<src<<"\n";
        exit(1);
    }

    task curr;

    while(tracefile>>std::dec>>curr.tid) {
        tracefile >>curr.op;
        tracefile >> std::hex>>curr.addr;
        task_list.push_back(curr);
        numTasks++;
    }
}



int uma_main(std::string protocol, int cores, std::string src) {
    std::cout<<"In UMA main\n";
    uma_init(protocol, cores, src);
    return 0;
}


int uma_init(std::string protocol, int cores, std::string src) {
    /*Initialize:
     * bus, memory, cache protocol (tracefile???) */
    Bus::init(cores);
    Memory::mem_init("UMA", cores, -1, protocol);
    return 0;
}

int uma_cycle() {
  while(numTasks != 0) {



  }
}
