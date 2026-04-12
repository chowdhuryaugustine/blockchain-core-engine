#ifndef BLOCKCHAIN_CORE_H
#define BLOCKCHAIN_CORE_H

#include <string>
#include <vector>
#include <cstdint>

struct ChainBlock {
    uint64_t index;
    uint64_t timestamp;
    std::string data;
    std::string prev_hash;
    std::string block_hash;
    uint64_t nonce;
};

class BlockchainEngine {
private:
    std::vector<ChainBlock> chain;
    uint32_t difficulty;
    std::string generate_block_hash(const ChainBlock& block) const;
    ChainBlock create_genesis_block();

public:
    BlockchainEngine();
    void set_difficulty(uint32_t diff);
    void add_block(const std::string& data);
    bool validate_chain_integrity() const;
    const std::vector<ChainBlock>& get_chain() const;
};

#endif
