#ifndef BUDDY_ALLOCATOR_HPP
#define BUDDY_ALLOCATOR_HPP
#include <map>
#include <vector>
#include <cstddef>
#include <unordered_map>
#include "MemoryBlock.hpp"

using namespace std;
using ll = size_t;

class BuddyAllocator{
    private:
        ll total_memory = 0;
        map<ll, vector<MemoryBlock>> free_lists;
        vector<MemoryBlock> allocated;
        int next_block_id = 1;
        unordered_map<int, ll> allocated_sizes;
        ll next_power_of_two(ll size) const;
        void add_free_block(const MemoryBlock &b);
        void split_block(ll block_size);

    public:
        BuddyAllocator() = default;
        void init(ll memory_size);
        int allocate(ll size);
        bool deallocate(int block_id);
        ll get_allocated_size(int block_id) const;
        vector<MemoryBlock> dump_blocks() const;
    };
#endif 
