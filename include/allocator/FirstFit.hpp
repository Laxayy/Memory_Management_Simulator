#ifndef FIRST_FIT_HPP
#define FIRST_FIT_HPP

#include <vector>
#include <cstddef>
#include "MemoryBlock.hpp"

using namespace std;
#define ll size_t

class FirstFit {

public:
    static int allocate(vector<MemoryBlock>& blocks,ll size,int& next_block_id);
};

#endif
