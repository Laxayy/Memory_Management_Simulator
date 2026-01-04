#ifndef STATS_HPP
#define STATS_HPP

#include <cstddef>
#include "../allocator/MemoryManager.hpp"
#include "../cache/CacheHierarchy.hpp"

using namespace std;
#define ll size_t

class Stats{
    
    public:

        static ll total_used(const MemoryManager& manager);
        static ll total_free(const MemoryManager& manager);

        static double memory_utilization(const MemoryManager& manager);
        static double external_fragmentation(const MemoryManager& manager);
        static double internal_fragmentation(const MemoryManager& manager);

        static void print_memory(const MemoryManager& manager);
        static void print_cache(const CacheHierarchy& cache);
};

#endif
