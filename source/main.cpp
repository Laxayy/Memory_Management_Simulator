#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include "allocator/MemoryManager.hpp"
#include "stats/Stats.hpp"
#include "cache/CacheHierarchy.hpp"
#include "virtual_memory/VirtualMemoryManager.hpp"

using namespace std;
using ll = size_t;

int main() {
    MemoryManager mem_manager;
    CacheHierarchy cache;
    VirtualMemoryManager vm_manager(0,0,0);
    bool vm_initialized = false;

    string line;
    cout<<"Memory Simulator"<<endl;
    cout<<"Type 'help' for commands"<<endl<<endl;

    while (1) {
        cout<<"> ";
        if (!getline(cin, line)) break;
        stringstream ss(line);
        string cmd;
        ss>>cmd;

        if (cmd == "exit" || cmd == "quit") break;
        else if (cmd == "help") {
            cout<<endl<<"Commands:"<<endl;
            cout<<" init memory <size>"<<endl;
            cout<<" set allocator first_fit | best_fit | worst_fit | buddy"<<endl;
            cout<<" malloc <size>"<<endl;
            cout<<" free <block_id>"<<endl;
            cout<<" dump"<<endl;
            cout<<" stats"<<endl;
            cout<<" cache add <size> <block_size> <associativity> <access_time>"<<endl;
            cout<<" cache_stats"<<endl;
            cout<<" access <virtual_address>"<<endl;
            cout<<" vm_stats"<<endl;
            cout<<" exit"<<endl<<endl;
        }
        else if (cmd == "init") {
            string what; ss>>what;
            if (what == "memory") {
                ll size; ss>>size;
                mem_manager.init_memory(size);
                vm_manager = VirtualMemoryManager(4096, size, 256);
                vm_initialized = true;
                cout<<"Initialized memory of size "<<size<<endl;
            }
        }
        else if (cmd == "set") {
            string what, type; ss>>what>>type;
            if (what == "allocator") {
                if (type == "first_fit") mem_manager.set_allocator(AllocatorType::FIRST_FIT);
                else if (type == "best_fit") mem_manager.set_allocator(AllocatorType::BEST_FIT);
                else if (type == "worst_fit") mem_manager.set_allocator(AllocatorType::WORST_FIT);
                else if (type == "buddy") mem_manager.set_allocator(AllocatorType::BUDDY);
                cout<<"Allocator set to "<<type<<endl;
            }
        }
        else if (cmd == "malloc") {
            ll size; ss>>size;
            int id = mem_manager.malloc_block(size);
            if (id == -1) cout<<"Allocation failed"<<endl;
            else cout<<"Allocated block id="<<id<<endl;
        }
        else if (cmd == "free") {
            int id; ss>>id;
            if (mem_manager.free_block(id)) cout<<"Block "<<id<<" freed"<<endl;
            else cout<<"Invalid block id"<<endl;
        }
        else if (cmd == "dump") {
            dump_memory(mem_manager);
        }
        else if (cmd == "stats") {
            Stats::print_memory(mem_manager);
        }
        else if (cmd == "cache") {
            string sub; ss>>sub;
            if (sub == "add") {
                ll size, block, assoc, access_time;
                ss>>size>>block>>assoc>>access_time;
                cache.add_level(size, block, assoc, access_time);
                cout<<"Cache level added"<<endl;
            }
        }
        else if (cmd == "cache_stats") {
            cache.print_stats();
        }
        else if (cmd == "access") {
            ll vaddr; ss>>vaddr;
            if (!vm_initialized) { cout<<"Initialize memory first"<<endl; continue; }
            ll paddr = vm_manager.translate(vaddr);
            cache.access(paddr);
            cout<<"Virtual Addr "<<vaddr<<" -> Physical Addr "<<paddr<<endl;
        }
        else if (cmd == "vm_stats") {
            cout<<endl<<"===== VIRTUAL MEMORY STATS ====="<<endl;
            cout<<"Page hits:   "<<vm_manager.get_page_hits()<<endl;
            cout<<"Page faults: "<<vm_manager.get_page_faults()<<endl;
            cout<<"================================"<<endl;
        }
        else cout<<"Unknown command"<<endl;
    }
    cout<<"Exiting simulator"<<endl;
    return 0;
}
