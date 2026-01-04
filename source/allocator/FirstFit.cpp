#include "FirstFit.hpp"
using namespace std;

#define ll size_t

int FirstFit::allocate(vector<MemoryBlock>& blocks, ll size, int& next_block_id) {

    for (auto it= blocks.begin(); it != blocks.end(); ++it) {
        if (it->is_free && it->size >= size) {
            int id= next_block_id++;
            it->is_free= false;
            it->block_id= id;
            it->requested_size= size;

            if (it->size> size) {
                ll remaining_size= it->size - size;
                ll remaining_addr= it->address + size;
                it->size= size;
                blocks.insert(next(it),MemoryBlock(remaining_addr,remaining_size,-1,true,0));
            }
            return id;
        }
    }
    return -1;
}
