
#include "UMA.hpp"
#include "Bus.hpp"

#include <iostream>
#include <vector>
#include <fstream>
#include <atomic>
#include <unistd.h>
#include <stdlib.h>
#include <string>


int uma_main(std::string protocol, int cores) {
    std::cout<<"In UMA main\n";
    uma_init(protocol, cores);
    return 0;
}

int uma_init(std::string protocol, int cores) {
    /*Initialize:
     * bus, memory, cache protocol (tracefile???) */
    Bus::init(cores);
    return 0;
}

int uma_cycle() {
    return 0;
}
