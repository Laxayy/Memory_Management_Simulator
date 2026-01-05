# Memory & Cache Simulator

A modular **Operating Systems–inspired simulator** that models **memory allocation**, **virtual memory paging**, and **multi-level cache hierarchy** using classical algorithms.  


## Project Overview

This project simulates how modern operating systems manage memory by combining:

- **Dynamic memory allocation**
- **Virtual memory with page replacement**
- **Multi-level cache hierarchy**


### Supported CLI Commands

* `init <memory_size>`  
    Initializes the physical memory with the specified size.
* `set allocator <first | best | worst | buddy>`  
    Selects the memory allocation strategy at runtime.
* `malloc <size>`  
    Allocates a block of memory of the given size and returns a block ID.
* `free <block_id>`  
    Frees the allocated memory block associated with the given ID.
* `cache add <cache_size> <block_size> <associativity>`  
    Adds a cache level (e.g., L1, L2) to the cache hierarchy.
* `access <virtual_address>`  
    Translates a virtual address to a physical address using the virtual memory manager and accesses it through the cache hierarchy.
* `stats`  
    Displays detailed memory statistics including usage, utilization, and fragmentation.
* `cache_stats`  
    Displays hit/miss statistics for each cache level.
* `vm_stats`  
    Displays virtual memory statistics such as page hits and page faults.
* `dump`  
    Prints the current layout of physical memory blocks.
* `exit`  
    Terminates the simulator.


## Core Components

### Memory Allocation
Supports multiple allocation strategies:
- **First Fit**
- **Best Fit**
- **Worst Fit**
- **Buddy Allocator**


### Virtual Memory
- Address translation using **paging**
- Page replacement policy: **LRU (Least Recently Used)**
- Tracks **page hits** and **page faults**


### Cache Hierarchy
- Configurable **L1 / L2 caches**
- Supports:
  - Direct-mapped and set-associative caches
  - Custom block size, associativity, and access time
- Replacement policy: **LRU**
- Accurate hit/miss accounting


### Statistics & Debugging
- Memory usage and utilization
- Fragmentation metrics
- Cache hit ratios
- Virtual memory performance
- Detailed memory dumps


## Project Structure (High Level)

```text
Memory_Simulator/
├── include/      # Header files (.hpp)
├── source/       # Implementation files (.cpp)
├── tests/        # Testcases & expected outputs
├── docs/         # Documentation & Design docs
├── logs/         # Generated execution logs
└── main.cpp      
```

## Documentation Files

The `docs/` directory contains **three important design documents**:

### `design.md`
- Explains the **complete system architecture**
- Includes **data flow diagrams**
- Describes interaction between:
  - Memory Manager
  - Cache Hierarchy
  - Virtual Memory Manager
- Shows end-to-end execution flow


### `assumptions.md`
- Lists **design assumptions** made during implementation
- Separates **general assumptions** from **internal implementation assumptions**


### `files_location_explaination.md`
- Explains **why files are placed where they are**
- Describes the role of:
  - `include/`
  - `source/`
  - `tests/`
  - `logs/`



