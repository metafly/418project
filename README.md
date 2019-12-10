# CacheM_ALL: Cache Memory Access Load Latency Simulator

This project implements a directory-based cache coherence protocol that can be used for non-uniform memory access (NUMA) systems. In a directory-based system, the data being shared is placed in a common directory that maintains the coherence between caches. The directory acts as a filter through which the processor must ask permission to load an entry from the primary memory to its cache. When an entry is changed, the directory either updates or invalidates the other caches with that entry.

## How to Run

``` 
make 
./cache_sim [-c <Number of cores>] [-s <Cache_size in MB>] [-a <Set Associativity>] [-p <Cache Coherence Protocol>] [-t <Trace File>]
```

## Current Status of Repository

 * Clone the 418CacheSim repo by @kshitizdange and understand how it works and run.

## Future Goals

* Implement NUMA processor architecture
* Implement hybrid architecture
* Get traces 
* Start testing and writing reports


