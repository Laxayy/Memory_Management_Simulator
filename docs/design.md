## 1. Overall System Architecture
+--------------------------------------------------+
|                   User Input                     |
|      (CLI commands: init, malloc, cache, etc.)   |
+--------------------------+-----------------------+
                           |
                           v
+--------------------------------------------------+
|                    main.cpp                      |
|          Command Parser & Dispatcher              |
+--------------------------+-----------------------+
                           |
        +------------------+------------------+
        |                  |                  |
        v                  v                  v
+---------------+  +------------------+  +---------------------+
| MemoryManager |  | CacheHierarchy   |  | VirtualMemoryManager|
+---------------+  +------------------+  +---------------------+


## 2. Memory Allocation Subsystem

### 2.1 Runtime Allocation Strategy Selection
+-------------------------------+
| Allocation Strategy (runtime) |
| First | Best | Worst | Buddy  |
+-------------------------------+



## 3. MemoryManager Internal Design

+----------------------+
|   MemoryManager      |
|----------------------|
| total_memory         |
| used_memory          |
| alloc_success/fail   |
| allocator_type       |
+----------+-----------+
           |
           v
+-------------------------------+
|   Allocation Strategy         |
|-------------------------------|
| FirstFit / BestFit / WorstFit |
| BuddyAllocator                |
+-------------------------------+
           |
           v
+----------------------+
|   MemoryBlock List   |
|----------------------|
| address              |
| size                 |
| is_free              |
| block_id             |
+----------------------+


## 4. Statistics Collection Design

+---------------------+
| MemoryManager       |
|---------------------|
| get_blocks()        |
| get_total_memory()  |
+----------+----------+
           |
           v
+---------------------+
| Stats Module        |
|---------------------|
| Used / Free Memory  |
| Utilization (%)     |
| Fragmentation       |
+---------------------+


## 5. Virtual Memory System

Virtual Address
|
v
+---------------------+
| Page Table Lookup |
+---------------------+
|
Hit / Miss
|
v
+---------------------+
| Page Replacement |
|                  |
+---------------------+

## 6. Cache Hierarchy Design
+-------------+
| CPU |
+-------------+
|
v
+-------------+
| L1 Cache |
+-------------+
|
v
+-------------+
| L2 Cache | 
+-------------+
|
v
+-------------+
| Main Memory |
+-------------+


## 7. End-to-End Execution Flow

User Command
|
v
Memory Allocation / Free
|
v
Virtual Address Access
|
v
VM Translation 
|
v
Cache Access (L1 → L2)
|
v
Stats Updated

