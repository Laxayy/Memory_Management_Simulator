#include "WorstFit.hpp"
using namespace std;

#define ll size_t


int WorstFit::allocate(vector<MemoryBlock>& blocks, ll size, int& next_block_id) {
    auto worst_it = blocks.end();
    ll worst_size = 0;

    for (auto it = blocks.begin(); it != blocks.end(); ++it) {
        if (it->is_free && it->size >= size) {
            if (it->size > worst_size) {
                worst_size = it->size;
                worst_it = it;
            }
        }
    }
    if (worst_it == blocks.end()) return -1;
    int id = next_block_id++;

    worst_it->is_free = false;
    worst_it->block_id = id;
    worst_it->requested_size = size;

    if (worst_it->size > size) {
        ll remaining_size = worst_it->size - size;
        ll remaining_addr = worst_it->address + size;
        worst_it->size = size;
        blocks.insert(next(worst_it), MemoryBlock(remaining_addr,remaining_size,-1, true, 0));
    }
    return id;
}
