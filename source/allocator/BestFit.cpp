#include "BestFit.hpp"
#include <climits>

using namespace std;

#define ll size_t
#define mx ULLONG_MAX


int BestFit::allocate(vector<MemoryBlock>& blocks, ll size, int& next_block_id) {
    auto best_it = blocks.end();
    ll best_size = mx;
    for (auto it = blocks.begin(); it != blocks.end(); ++it) {
        if (it->is_free && it->size >= size) {
            if (it->size < best_size) {
                best_size = it->size;
                best_it = it;
            }
        }
    }
    if (best_it == blocks.end()) return -1;
    int id = next_block_id++;

    best_it->is_free = false;
    best_it->block_id = id;
    best_it->requested_size = size;

    if (best_it->size > size) {
        ll remaining_size = best_it->size - size;
        ll remaining_addr = best_it->address + size;
        best_it->size = size;
        blocks.insert(next(best_it), MemoryBlock(remaining_addr, remaining_size, -1, true, 0));
    }
    
    return id;
}
