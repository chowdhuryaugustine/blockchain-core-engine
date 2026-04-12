#ifndef DIFFICULTY_ADJUSTER_H
#define DIFFICULTY_ADJUSTER_H

#include <cstdint>
#include <vector>

class DifficultyAdjustmentAlgorithm {
private:
    uint32_t base_difficulty;
    uint64_t target_block_time;
    uint32_t adjustment_interval;

public:
    DifficultyAdjustmentAlgorithm(uint32_t base_diff, uint64_t target_time, uint32_t interval);
    uint32_t calculate_new_difficulty(const std::vector<uint64_t>& block_times) const;
    uint64_t get_target_block_time() const;
    uint32_t get_adjustment_interval() const;
};

#endif
