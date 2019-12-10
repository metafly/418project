

#ifndef _UMA_H_
#define _BUS_H_

#include <unistd.h>
#include <stdlib.h>
#include <string>

int uma_main(std::string protocol, int cores);
int uma_init(std::string protocol, int cores);
int uma_cycle();






#endif
