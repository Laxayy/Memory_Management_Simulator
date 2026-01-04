#ifndef CACHE_HIERARCHY_HPP
#define CACHE_HIERARCHY_HPP

#include <vector>
#include <cstddef>

using namespace std;
using ll = size_t;

struct CacheLine {
    bool valid = false;
    ll tag = 0;
    ll arrival_time = 0;
};

class CacheLevel {
    public:
        CacheLevel(ll size, ll block_size, ll associativity, ll access_time);
        bool access_and_count(ll physical_address);
        bool probe(ll physical_address) const;
        void insert_block(ll physical_address);

        ll get_hits() const;
        ll get_misses() const;
        ll get_access_time() const;

    private:
        ll cache_size;
        ll block_size;
        ll associativity;
        ll num_sets;
        ll access_time;

        ll timer = 0;
        ll hits = 0;
        ll misses = 0;

        vector<vector<CacheLine>> sets;
        void decode_address(ll physical_address, ll &index, ll &tag) const;
};

class CacheHierarchy {
    public:
        void add_level(ll size, ll block_size, ll associativity, ll access_time);
        ll access(ll physical_address);
        void print_stats() const;

    private:
        vector<CacheLevel> levels;
};

#endif
