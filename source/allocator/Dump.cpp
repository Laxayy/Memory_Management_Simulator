#include "MemoryManager.hpp"
#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>

using namespace std;
using ll = size_t;

void dump_memory(const MemoryManager& manager) {
    
    vector<MemoryBlock> blocks;
    if (manager.is_buddy()) {
        blocks = manager.get_buddy().dump_blocks();
    }
    else {
        blocks = manager.get_blocks();
    }
    for (const auto& block : blocks) {
        cout<<"[0x"<<setw(4)<<setfill('0')<<hex<<block.address<<" - 0x" <<setw(4)<<setfill('0')<<hex<<(block.address+ block.size- 1)<<"] ";
        if (block.is_free) cout<<"FREE"<<endl;
        else cout<<"USED (id="<<dec<<block.block_id <<")"<<endl;
    }
    cout << dec;
}
