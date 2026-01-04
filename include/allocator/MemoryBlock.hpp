#ifndef MEMORY_BLOCK_HPP
#define MEMORY_BLOCK_HPP
#include <cstddef>

using namespace std;
using ll = size_t;

struct MemoryBlock {
    ll address;
    ll size;
    ll requested_size;
    int block_id;
    bool is_free;
    MemoryBlock(ll addr,ll sz,int id= -1,bool free= true, ll req= 0): address(addr),size(sz),requested_size(req),block_id(id),is_free(free){}
};

#endif
