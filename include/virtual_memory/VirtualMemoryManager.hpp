#ifndef VIRTUAL_MEMORY_MANAGER_HPP
#define VIRTUAL_MEMORY_MANAGER_HPP

#include <map>
#include <vector>
#include <cstddef>
#include <climits>

using namespace std;
#define ll size_t
#define mx ULLONG_MAX

struct PageEntry{
    bool valid;
    ll frame_number;
    ll timestamp;

    PageEntry():valid(false),frame_number(0),timestamp(0){}
};

class VirtualMemoryManager{

    private:
        ll virtual_address_space;
        ll physical_memory_size;
        ll page_size;
        ll num_frames;
        ll global_time;
        ll page_faults;
        ll page_hits;

        map<ll,PageEntry> page_table;
        vector<ll> frame_usage;

        ll get_page_number(ll virtual_address) const;
        ll get_offset(ll virtual_address) const;
        ll handle_page_fault(ll page_number);

    public:
        VirtualMemoryManager(ll virt_size,ll phys_size,ll page_sz);
        ll translate(ll virtual_address);
        ll get_page_faults() const;
        ll get_page_hits() const;

};

#endif
