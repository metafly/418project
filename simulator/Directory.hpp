#ifndef _DIRECTORY_H_
#define _DIRECTORY_H_

#include <stdlib.h>
#include <iostream>
#include <map>
#include <unistd.h>
#include <vector>


enum DirectoryEntryStatus {UNCACHED, SHARED, MODIFIED, EXCLUSIVE};

struct DirectoryEntry {
    std::vector<bool> processorMask;
    DirectoryEntryStatus status;
};

class Directory
{
    public:
        static std::map<uint64_t, DirectoryEntry>directory;
        static int num_cores;

        static void directory_init(int cores);
        static DirectoryEntry& lookUpEntry(uint64_t addr);
        static void updateEntry(uint64_t addr, DirectoryEntryStatus status, int procID);
        static DirectoryEntry& getOwners(uint64_t addr);
};


#endif
