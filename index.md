# Overview
CacheM_ALL is a directory-based cache coherence simulator that supports MSI and MESI. It takes memory reference traces as inputs, simulates cache and directory traffic, and finally analyzes/reports the behaviors.

# Background
A directory-based cache coherence protocol addresses the cache coherence problem in Distributed Shared Memory or Non-Uniform Memory Access (NUMA) systems. Each core is connected to a directory that keeps track of the state of cache lines in the core's local memory. A significant advantage of a directory-based protocol is the high scalability, as processors only communicate with a few others, instead of making broadcasts across the entire interconnect.

[Proposal](https://github.com/Ridhii/SyncdSim/blob/master/backend/Simulator/FinalProjectProposal.pdf) 
[Checkpoint](https://github.com/Ridhii/SyncdSim/blob/master/backend/Simulator/CheckpointReport.pdf) 

# Project Proposal

### Summary
We plan on taking a previous 15-418 project, 418CacheSim, and modifying it by adding support for NUMA and mixed architectures. Our goal is to study the performance of different cache coherence protocols on different Memory Access layouts.  


### Background
In computer architecture, cache coherence is the uniformity of shared resource data that ends up stored in the multiple local caches. These caches can be connected to memory in various ways:

**1) Uniform Memory Access (UMA)**
In this form of connection, each processor in the model shares the physical memory uniformly. Hence access time to a memory location is independent of which processor makes a request

**2) Non-Uniform Memory Access (NUMA)**
In this form of connection, each processor’s access time depends on the memory’s location relative to the processor. Under this, a processor can access local memory faster than non-local memory. 

**3) NUMA and UMA structures** are often combined to make scalable architectures. In this, processors in a Node have uniform access time to their local memory and have non-uniform access time to memories outside of their node depending on the distance.  
We are trying to create a comparative study of cache coherence in different memory access layouts of nodes.  


### The Challenge
This project will have several challenges for us: 

**1)** We need to understand how the 418CacheSim Repository works, and see whether we can just build a different memory access layout on that, or will we have to redefine how the simulator addresses various aspects of cache coherence. 

**2)** We believe that timing is an important factor for cache coherence across NUMA. So, an important part of the project will be to decide a method to be able to calculate clock ticks. Or some other similar metric to calculate time. For example, measuring how much time does it take to service a request internally vs externally. 

Deciding on what other metrics that should be compared across these architectures. 


### Resources
We will be building off of a previous 15-418 project:
418CacheSim: https://kshitizdange.github.io/418CacheSim/proposal-page

The project provides a code base for snooping-based cache coherence protocols on basic UMA architecture. 

Since we will be running the simulations with traces, we will not need any additional machines.


### Goals and Deliverables
Goals: 
- Implement memory access models drawn in the background section: NUMA, and UMA+NUMA
- Add support for  full bit vector directory-based cache coherence
- Take Memory Traces and run them with our simulator to generate statistics like avg service request time, internal service request time vs external request time, number of cache to cache transfers, number of snooping bus transactions for each bus, etc. 

Performance:
- A number of bus transactions, per bus. 
- Graphs comparing actual performance with theoretical performance.
- Avg. memory request serving time
- Memory contention 

Extra stuff if we have time: 
- Add different sparse directory-based protocols to the simulator
- Find additional metrics to compare things. 

### Platform Choice
We will be using C++, since the project we are referring to was in C++. It also works well for reading memory traces and outputting the simulation results. 

### Schedule

Markdown is a lightweight and easy-to-use syntax for styling your writing. It includes conventions for

```markdown
Syntax highlighted code block

# Header 1
## Header 2
### Header 3

- Bulleted
- List

1. Numbered
2. List

**Bold** and _Italic_ and `Code` text

[Link](url) and ![Image](src)
```

