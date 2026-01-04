#include "MemoryManager.hpp"
#include "FirstFit.hpp"
#include "BestFit.hpp"
#include "WorstFit.hpp"
#include "BuddyAllocator.hpp"
#include <algorithm>
#include <iostream>

using namespace std;
using ll = size_t;

static void coalesce_blocks(vector<MemoryBlock>& blocks) {
    for (size_t i= 0; i+1< blocks.size();i++) {
        if (blocks[i].is_free && blocks[i+1].is_free) {
            blocks[i].size+= blocks[i+1].size;
            blocks.erase(blocks.begin()+i+1);i--;
        } 
    }
}

MemoryManager::MemoryManager() {
    total_memory = 0;
    next_block_id = 1;
    allocator_type = AllocatorType::FIRST_FIT;
    used_memory = 0;
    alloc_success = 0;
    alloc_failure = 0;
}

void MemoryManager::init_memory(ll size) {

    total_memory = size;
    next_block_id = 1;
    used_memory = 0;
    alloc_success = 0;
    alloc_failure = 0;
    blocks.clear();
    blocks.push_back(MemoryBlock(0,size,-1, true));
    buddy.init(size);
}

void MemoryManager::set_allocator(AllocatorType type) {
    if (allocator_type== type) return;
    allocator_type = type;
    if (allocator_type== AllocatorType::BUDDY) buddy.init(total_memory);
}

int MemoryManager::malloc_block(ll size) {
    if (size== 0) { alloc_failure++; return -1; }
    int id= -1;
    if (allocator_type== AllocatorType::FIRST_FIT) id= FirstFit::allocate(blocks,size,next_block_id);
    else if (allocator_type== AllocatorType::BEST_FIT) id= BestFit::allocate(blocks,size,next_block_id);
    else if (allocator_type== AllocatorType::WORST_FIT) id= WorstFit::allocate(blocks,size,next_block_id);
    else if (allocator_type== AllocatorType::BUDDY) id= buddy.allocate(size);

    if (id== -1) { alloc_failure++; }
    else {
        alloc_success++;
        if (allocator_type== AllocatorType::BUDDY) used_memory += buddy.get_allocated_size(id);
        else used_memory += size;
    }
    return id;
}


bool MemoryManager::free_block(int block_id) {
    
    if (allocator_type == AllocatorType::BUDDY) {
        ll sz = buddy.get_allocated_size(block_id);
        if (sz == 0) return false;
        if (buddy.deallocate(block_id)) {used_memory -= sz; return true; }
        return false;
    }
    for (auto &b : blocks) {
        if (!b.is_free && b.block_id == block_id) {
            if (used_memory>= b.size) used_memory -= b.size;
            b.is_free= true;
            b.block_id= -1;
            coalesce_blocks(blocks);
            return true;
        }
    }
    return false;
}

ll MemoryManager::get_external_fragmentation() const {
    if (allocator_type == AllocatorType::BUDDY) return 0;
    ll free_total= 0, largest_free= 0;
    for (const auto &b : blocks) {
        if (b.is_free) {
            free_total += b.size;
            largest_free = max(largest_free,b.size);
        }
    }
    return (free_total == 0) ? 0 : free_total - largest_free;
}

const vector<MemoryBlock>& MemoryManager::get_blocks() const {return blocks; }
ll MemoryManager::get_alloc_success() const {return alloc_success; }
ll MemoryManager::get_alloc_failure() const {return alloc_failure; }
ll MemoryManager::get_total_memory() const {return total_memory; }
ll MemoryManager::get_used_memory() const {return used_memory; }
ll MemoryManager::get_free_memory() const {return total_memory - used_memory; }
