

#ifndef _UMA_H_
#define _BUS_H_

#include <unistd.h>
#include <stdlib.h>
#include <string>
#include <vector>

extern int numTasks = 0;

typedef struct {
    int tid;
    std::sting op;
    unsigned long addr;
} task;

extern std::vector<task *> task_list;


int uma_main(std::string protocol, int cores);
int uma_init(std::string protocol, int cores, std::string src);
int uma_cycle();

void process_trace_file(stf::string src);






#endif
