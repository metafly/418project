#include "Directory.hpp"
#include <map>
#include <vector>
#include <unistd.h>
#include <iostream>

int Directory::num_cores;
std::map<uint64_t, DirectoryEntry> Directory::directory;

void Directory::directory_init(int cores) {

    Directory::num_cores = cores;
}


DirectoryEntry& Directory::lookUpEntry(uint64_t addr) {
    if(directory.find(addr) == directory.end()) {
        std::cout<<"no entry in directory, creating now\n";
        updateEntry(addr, DirectoryEntryStatus::UNCACHED, -1);
    }
    return directory[addr];
}

void Directory::updateEntry(uint64_t addr, DirectoryEntryStatus status, int procID) {

    if(directory.find(addr) == directory.end()) {
        DirectoryEntry dirEntry;
        dirEntry.processorMask.reserve(num_cores);

        for(int i = 0; i < num_cores; i++) {
            if(i == procID) {
                dirEntry.processorMask.push_back(true);
            } else {
                dirEntry.processorMask.push_back(false);
            }
        }

        dirEntry.status = status;
        directory.insert(std::pair<uint64_t, DirectoryEntry>(addr, dirEntry));
        return;
    }

    if (status == DirectoryEntryStatus::SHARED) {
        directory[addr].status = status;
        directory[addr].processorMask[procID] = true;
    }

    if (status == DirectoryEntryStatus::EXCLUSIVE) {
        //assert(protocol == protocol::MESI);
        //assert(directory[addr].status ==  DirectoryEntryStatus::UNCACHED); //before gaining exclusive rights it should be uncached
        directory[addr].status = status;

        for(int i = 0; i < num_cores; i++) {
            if(i == procID) {
                directory[addr].processorMask[i] = true;
            }
            else {
                directory[addr].processorMask[i] = false;
            }
        }
    }

    if(status == DirectoryEntryStatus::MODIFIED) {
        directory[addr].status = status;
        for(int i = 0; i < num_cores; i++) {
            if (i == procID) {
                directory[addr].processorMask[i] = true;
            }
            else {
                directory[addr].processorMask[i] = false;
            }
        }
    }

    if(status == DirectoryEntryStatus::UNCACHED) {
        directory.erase(addr);
    }

}

DirectoryEntry& Directory::getOwners(uint64_t addr) {
    return directory[addr]; //can be directory.end()
}


