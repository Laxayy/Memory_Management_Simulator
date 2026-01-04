#include "BuddyAllocator.hpp"
#include <algorithm>
using namespace std;
using ll = size_t;

ll BuddyAllocator::next_power_of_two(ll size) const {
    if (size== 0) return 1;
    ll p= 1;
    while (p < size) p <<= 1;
    return p;
}

void BuddyAllocator::init(ll memory_size) {
    total_memory= memory_size;
    free_lists.clear();
    allocated.clear();
    allocated_sizes.clear();
    next_block_id= 1;
    free_lists[memory_size].push_back(MemoryBlock(0,memory_size,-1, true));
}


void BuddyAllocator::add_free_block(const MemoryBlock &b) {
    free_lists[b.size].push_back(b);
}


void BuddyAllocator::split_block(ll block_size) {
    auto it= free_lists.upper_bound(block_size);
    if (it== free_lists.end() || it->second.empty()) return;

    ll big_size= it->first;
    MemoryBlock block= it->second.back();

    it->second.pop_back();
    ll half= big_size / 2;

    add_free_block(MemoryBlock(block.address+ half,half,-1, true));
    add_free_block(MemoryBlock(block.address,half,-1, true));
}


int BuddyAllocator::allocate(ll size) {
    if (size== 0) return -1;
    ll req_size= next_power_of_two(size);
    if (req_size> total_memory) return -1;

    ll cur_size= req_size;

    while (cur_size<= total_memory && free_lists[cur_size].empty()) {
        cur_size <<= 1;
    }

    if (cur_size> total_memory ||free_lists[cur_size].empty()) return -1;
    auto &list= free_lists[cur_size];
    auto best_it= min_element(list.begin(), list.end(), [](const MemoryBlock &a, const MemoryBlock &b){ 
        return a.address< b.address; 
    });
    MemoryBlock block= *best_it;
    list.erase(best_it);
    while (cur_size> req_size) {
        cur_size >>= 1;
        add_free_block(MemoryBlock(block.address+ cur_size,cur_size,-1, true));
        block.size = cur_size;
    }
    block.is_free= false;
    block.block_id= next_block_id++;
    allocated.push_back(block);
    allocated_sizes[block.block_id]= block.size;
    return block.block_id;
}
bool BuddyAllocator::deallocate(int block_id) {
    auto it= find_if(allocated.begin(),allocated.end(),[block_id](const MemoryBlock &b){ return b.block_id == block_id; });
    
    if (it== allocated.end()) return false;

    MemoryBlock block= *it;
    allocated.erase(it);
    ll addr= block.address;
    ll size= block.size;

    while (size< total_memory) {

        ll buddy_addr= addr ^ size;
        auto &vec= free_lists[size];
        auto buddy_it= find_if(vec.begin(), vec.end(), [buddy_addr](const MemoryBlock &b){ return b.address == buddy_addr; });
        if (buddy_it== vec.end()) {
            add_free_block(MemoryBlock(addr,size,-1, true));
            break;
        }
        vec.erase(buddy_it);
        addr= min(addr,buddy_addr);
        size <<= 1;

    }

    if (size>= total_memory) add_free_block(MemoryBlock(addr,size,-1,true));
    allocated_sizes.erase(block_id);
    return true;
}


vector<MemoryBlock> BuddyAllocator::dump_blocks() const {
    vector<MemoryBlock> out= allocated;
    for (const auto &p: free_lists){
        for (const auto &b: p.second){
            out.push_back(b);
        }
    }

    sort(out.begin(),out.end(),[](const MemoryBlock &a, const MemoryBlock &b){ return a.address < b.address; });
    return out;
}

ll BuddyAllocator::get_allocated_size(int block_id) const {
    auto it= find_if(allocated.begin(), allocated.end(), [block_id](const MemoryBlock &b) { return b.block_id == block_id; });
    return (it== allocated.end())? 0: it->size;
}
