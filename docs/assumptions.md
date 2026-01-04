# Assumptions


## Memory Management Assumptions
- Block IDs are unique per memory initialization and reset on re-initialization.
- Adjacent free blocks are coalesced immediately for linear allocators.



## Allocator-Specific Assumptions

### First Fit / Best Fit / Worst Fit
- Memory is maintained as a linear list of blocks.
- Internal fragmentation is assumed to be `0`.
- External fragmentation is computed from free block layout.

### Buddy Allocator
- Allocation sizes are rounded up to the nearest power of two.
- Internal fragmentation is not tracked.
- External fragmentation is reported as `0%` by design.
- Buddy allocator maintains its own block structure.



## Memory Statistics Assumptions

- Used memory is derived from allocated block sizes.
- Free memory is computed as `Total − Used`.
- Internal fragmentation is always reported as `0.00%`.



## Cache System Assumptions

- Cache operates on **physical addresses only**.
- Cache levels are accessed sequentially (L1 → L2 → …).
- Replacement policy is **LRU**.



## Virtual Memory Assumptions

- Virtual memory is initialized after physical memory.
- Page size is fixed at initialization.
- Page replacement policy is **LRU**.

