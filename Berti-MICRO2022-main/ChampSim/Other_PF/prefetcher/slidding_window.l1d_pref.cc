#include "cache.h"

#include <map>

static uint64_t last_block_addr = 0;

uint64_t stride_Cal(uint64_t addr){

	addr = addr >> (LOG2_BLOCK_SIZE); 
	uint64_t stride = addr - last_block_addr;
	last_block_addr = addr;

}

void CACHE::l1d_prefetcher_initialize() 
{

}

void CACHE::l1d_prefetcher_operate(uint64_t addr, uint64_t ip, uint8_t cache_hit, uint8_t type, uint8_t critical_ip_flag)
{



}

void CACHE::l1d_prefetcher_notify_about_dtlb_eviction(uint64_t addr, uint32_t set, uint32_t way, uint8_t prefetch, uint64_t evicted_addr, uint32_t metadata_in)
{

}

void CACHE::l1d_prefetcher_cache_fill(uint64_t v_addr, uint64_t addr, uint32_t set, uint32_t way, uint8_t prefetch, uint64_t v_evicted_addr, uint64_t evicted_addr, uint32_t metadata_in)
{


}

void CACHE::l1d_prefetcher_final_stats()
{

}
