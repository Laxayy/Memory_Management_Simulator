#include "cache/CacheHierarchy.hpp"
#include <iostream>
#include <iomanip>
#include <algorithm>

using namespace std;
using ll = size_t;
const ll MEMORY_PENALTY = 100;

CacheLevel::CacheLevel(ll size, ll block, ll assoc, ll time) : cache_size(size), block_size(block), associativity(assoc), access_time(time) {
    num_sets = (block_size * associativity == 0)?1 :(cache_size / (block_size * associativity));
    if (num_sets == 0){
        num_sets = 1;
    }
    sets.resize(num_sets, vector<CacheLine>(associativity));
}

void CacheLevel::decode_address(ll physical_address, ll &index, ll &tag) const {
    ll block_addr= physical_address / block_size;
    index= block_addr%num_sets;
    tag= block_addr/num_sets;
}

bool CacheLevel::access_and_count(ll physical_address) {
    ++timer;
    ll index,tag;
    decode_address(physical_address,index,tag);
    auto &set = sets[index];
    for (auto &line :set) {
        if (line.valid && line.tag== tag) {
            ++hits;
            line.arrival_time= timer;
            return true;
        }
    }
    ++misses;
    return false;
}

bool CacheLevel::probe(ll physical_address) const {
    ll index, tag;
    decode_address(physical_address,index,tag);
    for (const auto &line:sets[index]) {
        if (line.valid && line.tag== tag) return true;
    }
    return false;
}

void CacheLevel::insert_block(ll physical_address) {
    ++timer;
    ll index,tag;
    decode_address(physical_address, index, tag);
    auto &set= sets[index];
    CacheLine *victim= nullptr;
    for (auto &line: set) {
        if (!line.valid) {
            victim= &line;
            break;
        }
    }
    if (!victim) {
        victim= &set[0];
        for (auto &line : set) {
            if (line.arrival_time < victim->arrival_time) victim = &line;
        }
    }
    victim->valid = true;
    victim->tag = tag;
    victim->arrival_time = timer;
}

ll CacheHierarchy::access(ll physical_address) {
    ll total_time = 0;
    if (levels.empty()) return MEMORY_PENALTY;

    total_time += levels[0].get_access_time();
    if (levels[0].access_and_count(physical_address)) return total_time;
    if (levels.size() > 1) {
        total_time += levels[1].get_access_time();
        if (levels[1].access_and_count(physical_address)) {
            levels[0].insert_block(physical_address);
            return total_time;
        } else {
            total_time += MEMORY_PENALTY;
            levels[1].insert_block(physical_address);
            levels[0].insert_block(physical_address);
            return total_time;
        }
    }
    total_time += MEMORY_PENALTY;
    levels[0].insert_block(physical_address);
    return total_time;
}

void CacheHierarchy::print_stats() const {
    cout<<endl<<"===== CACHE HIERARCHY STATS ====="<<endl;
    int lvl = 1;
    for (const auto &l : levels) {
        ll h = l.get_hits(), m = l.get_misses(), t = h + m;
        double ratio = (t == 0) ? 0.0 : (100.0 * h / t);
        cout<<"L"<<lvl++<<" Cache"<<endl;
        cout<<" Hits: "<<h<<endl;
        cout<<" Misses: "<<m<<endl;
        cout<<fixed<<setprecision(2)<<" Hit Ratio: "<<ratio<<"%"<<endl;
        cout<<endl;
    }
    cout<<"==============================="<<endl;
}

void CacheHierarchy::add_level(ll size, ll block_size, ll associativity, ll access_time) {
    levels.emplace_back(size, block_size, associativity, access_time);
}

ll CacheLevel::get_hits() const { return hits; }
ll CacheLevel::get_misses() const { return misses; }
ll CacheLevel::get_access_time() const { return access_time; }
