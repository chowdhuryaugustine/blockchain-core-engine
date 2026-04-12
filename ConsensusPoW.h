#ifndef CONSENSUS_POW_H
#define CONSENSUS_POW_H

#include <string>
#include <cstdint>

class ProofOfWork {
private:
    uint32_t pow_difficulty;
    std::string calculate_target_hash() const;

public:
    ProofOfWork(uint32_t diff = 4);
    uint64_t mine_block(const std::string& block_header, std::string& out_hash);
    bool validate_pow(const std::string& block_header, uint64_t nonce, const std::string& hash) const;
    void update_difficulty(uint32_t new_diff);
};

#endif
