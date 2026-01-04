#include "VirtualMemoryManager.hpp"
#include <limits>
#include <stdexcept>
#define ll size_t
#define mx ULLONG_MAX
using namespace std;

VirtualMemoryManager::VirtualMemoryManager(ll virt_size,ll phys_size,ll page_sz){
    virtual_address_space=virt_size;
    physical_memory_size=phys_size;
    page_size=page_sz;
    global_time=0;
    page_faults=0;
    page_hits=0;
    num_frames=physical_memory_size/page_size;
    frame_usage.resize(num_frames,mx);
}

ll VirtualMemoryManager::get_page_number(ll virtual_address) const {
    return virtual_address/page_size;
}

ll VirtualMemoryManager::get_offset(ll virtual_address) const {
    return virtual_address%page_size;
}

ll VirtualMemoryManager::handle_page_fault(ll page_number){
    page_faults++;
    for (ll i=0;i<num_frames;++i){
        if (frame_usage[i]==mx){
            frame_usage[i]=page_number;
            return i;
        }
    }
    ll victim_frame=0;
    ll oldest_time=mx;
    for (pair<const ll,PageEntry>& entry : page_table){
        if (entry.second.valid){
            if (entry.second.timestamp<oldest_time){
                oldest_time=entry.second.timestamp;
                victim_frame=entry.second.frame_number;
            }
        }
    }
    for (pair<const ll,PageEntry>& entry : page_table){
        if (entry.second.frame_number==victim_frame){
            if (entry.second.valid){
                entry.second.valid=false;
                break;
            }
        }
    }
    frame_usage[victim_frame]=page_number;
    return victim_frame;
}

ll VirtualMemoryManager::translate(ll virtual_address){
    if (virtual_address>=virtual_address_space){
        throw out_of_range("Virtual address out of range");
    }
    global_time++;
    ll page_number=get_page_number(virtual_address);
    ll offset=get_offset(virtual_address);
    auto& entry=page_table[page_number];
    if (entry.valid){
        page_hits++;
        entry.timestamp=global_time;
    } else {
        ll frame=handle_page_fault(page_number);
        entry.valid=true;
        entry.frame_number=frame;
        entry.timestamp=global_time;
    }
    return entry.frame_number*page_size+offset;
}

ll VirtualMemoryManager::get_page_faults() const {return(page_faults);}
ll VirtualMemoryManager::get_page_hits() const {return(page_hits);}
