#include "cache.h"

#include <map>
#include <algorithm>

#define offset_numbers_count 20001
#define access_interval 512


static std::vector<int32_t> offsets;
// for (int i = -10000; i <= 10000; ++i)
// {
//     offsets.push_back(i);
// }

static std::vector<int32_t> arm_n_count(offset_numbers_count, 0);

static uint64_t n_total = 0;

static std::vector<int32_t> reward(offset_numbers_count, 0);

static std::vector<int64_t> rr(access_interval);
static std::vector<int64_t> pf(access_interval);

static std::vector<double> potential(offset_numbers_count, 0);

static uint32_t access_index = 0;
static int offsets_index = 0;

void CACHE::l1d_prefetcher_initialize()
{
    // static std::vector<int32_t> offsets;
    for (int i = -10; i <= 10 ; ++i) {
    offsets.push_back(i);
    }
}

void CACHE::l1d_prefetcher_operate(uint64_t addr, uint64_t ip, uint8_t cache_hit, uint8_t type, uint8_t critical_ip_flag)
{
    // Assert that the address is non-negative
    assert(addr >= 0);
    

    static int64_t best_arm = 0;
    uint64_t temp_addr = addr >> LOG2_BLOCK_SIZE;
    if (offsets_index >= 20)
    {
        int access_index = 0;
        int reward_index = 0;
        int c = 6;
        int32_t offset_reward = reward[reward_index];

        int n_arms = reward.size();
        // int n_total = std::accumulate(arm_counts.begin(), arm_counts.end(), 0);
        // std::vector<double> ucb_values(n_arms);

        for (int i = 0; i < n_arms; ++i)
        {
            double bonus = c * sqrt(log(n_total) / (arm_n_count[i]));
            potential[i] = reward[i] + bonus;
        }

        // Find the iterator to the maximum element
        auto maxElementIterator = std::max_element(potential.begin(), potential.end());

        // Find the index of the maximum element
        size_t maxIndex = std::distance(potential.begin(), maxElementIterator);

        arm_n_count[maxIndex]++;
        n_total++;

        rr[access_index] = temp_addr;
        

        best_arm = offsets[maxIndex];

        uint64_t prefetch_addr = temp_addr + best_arm;

        pf[access_index] = prefetch_addr << LOG2_BLOCK_SIZE;
        prefetch_line(ip,addr,prefetch_addr,FILL_L1,0);

        if (access_index == 511)
        {
            // arm_n_count[offsets_index] = 1;

            // n_total++;

            int countSame = 0;

            // Compare each entry in the vectors
            for (size_t i = 0; i < rr.size(); ++i)
            {
                if (rr[i] == pf[i])
                {
                    countSame++;
                }
            }

            reward[maxIndex] = (reward[maxIndex]* (arm_n_count[maxIndex]-1)+countSame)/arm_n_count[maxIndex];
            std::cout << "Selected Offset "<< best_arm << endl;
        }
        access_index++;
        return;// forget to put in starting
	std::cout << "Selected Offset" << best_arm << endl;   
 }

    int64_t arm;

    // if (best_arm != 0)
    // {
    //     uint64_t pf_best_arm = temp_addr + best_arm;
    //     pf_best_arm << LOG2_BLOCK_SIZE;
    //     prefetch_line(ip, addr, pf_best_arm, FILL_L1, 0);
    // }

    rr[access_index] = temp_addr;

    arm = offsets[offsets_index];

    uint64_t prefetch_addr = temp_addr + arm;

    pf[access_index] = prefetch_addr << LOG2_BLOCK_SIZE;
    // prefetch_line(ip,addr,prefetch_addr,FILL_L1,0);

    if (access_index == 511)
    {
        arm_n_count[offsets_index] = 1;

        n_total++;

        int countSame = 0;

        // Compare each entry in the vectors
        for (size_t i = 0; i < rr.size(); ++i)
        {
            if (rr[i] == pf[i])
            {
                countSame++;
            }
        }

        reward[offsets_index] = countSame;

        access_index = 0;

        offsets_index++;
    }

    access_index = (access_index + 1) % access_interval;
    return;
}

void CACHE::l1d_prefetcher_notify_about_dtlb_eviction(uint64_t addr, uint32_t set, uint32_t way, uint8_t prefetch, uint64_t evicted_addr, uint32_t metadata_in)
{
}

void CACHE::l1d_prefetcher_cache_fill(uint64_t v_addr, uint64_t addr, uint32_t set, uint32_t way, uint8_t prefetch, uint64_t v_evicted_addr, uint64_t evicted_addr, uint32_t metadata_in)
{

#ifdef TRACE_DUMP
    cout << "FILL:  CL Addr: " << (addr >> LOG2_BLOCK_SIZE) << "  Prefetch: " << unsigned(prefetch) << "  Cycle: " << current_core_cycle[cpu] << endl;
#endif
}

void CACHE::l1d_prefetcher_final_stats()
{
    std::cout << "ucb ended" << endl;
}
