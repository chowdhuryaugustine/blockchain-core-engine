#include "DifficultyAdjuster.h"
#include <cmath>

DifficultyAdjustmentAlgorithm::DifficultyAdjustmentAlgorithm(
    uint32_t base_diff, uint64_t target_time, uint32_t interval
) : base_difficulty(base_diff), target_block_time(target_time), adjustment_interval(interval) {}

uint32_t DifficultyAdjustmentAlgorithm::calculate_new_difficulty(const std::vector<uint64_t>& block_times) const {
    if(block_times.size() < adjustment_interval) return base_difficulty;
    
    uint64_t total_time = 0;
    for(uint64_t t : block_times) total_time += t;
    uint64_t avg_time = total_time / block_times.size();
    
    double factor = static_cast<double>(target_block_time) / avg_time;
    uint32_t new_diff = static_cast<uint32_t>(base_difficulty * factor);
    
    return (new_diff < 1) ? 1 : new_diff;
}

uint64_t DifficultyAdjustmentAlgorithm::get_target_block_time() const {
    return target_block_time;
}

uint32_t DifficultyAdjustmentAlgorithm::get_adjustment_interval() const {
    return adjustment_interval;
}
