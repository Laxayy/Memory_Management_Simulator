#include "Stats.hpp"
#include <iostream>
#include <iomanip>
#include <algorithm>

using namespace std;
#define setp(x) fixed<<setprecision(x)

static vector<MemoryBlock> get_blocks_for_stats(const MemoryManager& manager) {
    if (manager.is_buddy()) return manager.get_buddy().dump_blocks();
    else return manager.get_blocks();
}

ll Stats::total_used(const MemoryManager& manager) {
    ll used = 0;
    for (const auto& b: get_blocks_for_stats(manager)) { if (!b.is_free) used += b.size; }
    return used;
}

ll Stats::total_free(const MemoryManager& manager) { 
    return manager.get_total_memory()-total_used(manager); 
}

double Stats::memory_utilization(const MemoryManager& manager) {
    ll total = manager.get_total_memory();
    if (total == 0) return 0.0;
    return (double)total_used(manager)*100.0/total;
}

double Stats::external_fragmentation(const MemoryManager& manager) {
    if (manager.is_buddy()) return 0.0;
    ll total_free = 0, largest_free = 0;
    for (const auto& b: manager.get_blocks()) {
        if (b.is_free) {
            total_free += b.size;
            largest_free = max(largest_free, b.size);
        }
    }
    ll total = manager.get_total_memory();
    if (total == 0) return 0.0;
    ll fragmented = (total_free > largest_free) ? (total_free-largest_free) : 0;
    return (double)fragmented*100.0/total;
}

double Stats::internal_fragmentation(const MemoryManager& manager) {
    return 0.0;
}

void Stats::print_memory(const MemoryManager& manager) {
    cout<<endl<<"===== MEMORY STATS ====="<<endl;
    cout<<"Total memory: "<<manager.get_total_memory()<<endl;
    cout<<"Used memory: "<<total_used(manager)<<endl;
    cout<<"Free memory: "<<total_free(manager)<<endl;
    cout<<"Allocation success: "<<manager.get_alloc_success()<<endl;
    cout<<"Allocation failure: "<<manager.get_alloc_failure()<<endl;
    cout<<setp(2)<<"Memory utilization: "<<memory_utilization(manager)<<"%"<<endl;
    cout<<setp(2)<<"External fragmentation: "<<external_fragmentation(manager)<<"%"<<endl;
    cout<<setp(2)<<"Internal fragmentation: "<<internal_fragmentation(manager)<<"%"<<endl;
    cout<<"========================"<<endl<<endl;
}

void Stats::print_cache(const CacheHierarchy& cache) { cache.print_stats(); }
