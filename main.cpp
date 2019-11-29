/*
 * The main file for the Cache simulator
 */


#include <iostream>
#include <fstream>
#include <vector>
#include <unistd.h>
#include <stdlib.h>
#include <atomic>


/*
 * Prints usage of the cache simulator
 */
void print_usage() {
    std::cout<<"./cachemall [-s <type of system UMA/NUMA/HYBRID>] [-c <Number of cores 1/2/4/8>]"
                           "[-p <Cache Coherence Protocol>]\n";
}



int main(int argc char *argv[]) {
    int cores = 1;
    std::string protocol = "MSI";
    std::string system = "UMA";

    while((ch = getopt(argc, argv, "s:c:p:")) != -1) {
        switch(ch) {
            case 's':
                system = std::string(optarg);
                break;
            case 'c':
                cores = atoi(optarg);
                break;
            case 'p':
                protocol = std::string(optarg);
                break;
            default:
                std::cerr<< "Illegal arguments\n";
                print_usage();
                return 1;
        }
    }

    if( cores == 1 || system.compare("UMA") == 0) {
        uma_main(protocol, cores);
    }
/*    else if (system.compare("NUMA") == 0) {
        numa_main(protocol, cores);
    }
    else if (system.compare("HYBRID") == 0) {
        hybrid_main(protocol, cores);
    }*/
    else {
        std::cout <<"Invalid system\n";
        print_usage();
    }




}
