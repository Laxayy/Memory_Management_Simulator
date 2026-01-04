#ifndef MEMORY_MANAGER_HPP
#define MEMORY_MANAGER_HPP

#include <vector>
#include <cstddef>
#include "MemoryBlock.hpp"
#include "BuddyAllocator.hpp"

using namespace std;
using ll = size_t;

enum class AllocatorType {
    FIRST_FIT,
    BEST_FIT,
    WORST_FIT,
    BUDDY
};

class MemoryManager {
    private:
        ll total_memory= 0;
        ll used_memory= 0;
        ll alloc_success= 0;
        ll alloc_failure= 0;
        int next_block_id= 1;

        vector<MemoryBlock> blocks;
        AllocatorType allocator_type= AllocatorType::FIRST_FIT;
        BuddyAllocator buddy;

    public:
        MemoryManager();

        void init_memory(ll size);
        void set_allocator(AllocatorType type);
        int malloc_block(ll size);
        bool free_block(int block_id);

        ll get_total_memory() const;
        ll get_used_memory() const;
        ll get_free_memory() const;
        ll get_external_fragmentation() const;
        ll get_alloc_success() const;
        ll get_alloc_failure() const;

        AllocatorType get_allocator_type() const {return allocator_type;}
        vector<MemoryBlock> get_buddy_blocks() const {return buddy.dump_blocks();}
        bool is_buddy() const {return allocator_type== AllocatorType::BUDDY;}
        const BuddyAllocator& get_buddy() const {return buddy;}
        const vector<MemoryBlock>& get_blocks() const;

};
void dump_memory(const MemoryManager& manager);

#endif
