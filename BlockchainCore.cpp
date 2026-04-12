#include "BlockchainCore.h"
#include <chrono>
#include <sstream>
#include <iomanip>
#include <openssl/sha.h>

std::string sha256(const std::string& str) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, str.c_str(), str.size());
    SHA256_Final(hash, &sha256);
    
    std::stringstream ss;
    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }
    return ss.str();
}

std::string BlockchainEngine::generate_block_hash(const ChainBlock& block) const {
    std::stringstream ss;
    ss << block.index << block.timestamp << block.data << block.prev_hash << block.nonce;
    return sha256(ss.str());
}

BlockchainEngine::BlockchainEngine() {
    difficulty = 4;
    chain.emplace_back(create_genesis_block());
}

ChainBlock BlockchainEngine::create_genesis_block() {
    ChainBlock genesis;
    genesis.index = 0;
    genesis.timestamp = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    genesis.data = "Genesis Block - Blockchain Core";
    genesis.prev_hash = "0";
    genesis.nonce = 0;
    
    while(true) {
        genesis.block_hash = generate_block_hash(genesis);
        if(genesis.block_hash.substr(0, difficulty) == std::string(difficulty, '0')) {
            break;
        }
        genesis.nonce++;
    }
    return genesis;
}

void BlockchainEngine::set_difficulty(uint32_t diff) {
    difficulty = diff;
}

void BlockchainEngine::add_block(const std::string& data) {
    ChainBlock new_block;
    new_block.index = chain.back().index + 1;
    new_block.timestamp = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    new_block.data = data;
    new_block.prev_hash = chain.back().block_hash;
    new_block.nonce = 0;
    
    while(true) {
        new_block.block_hash = generate_block_hash(new_block);
        if(new_block.block_hash.substr(0, difficulty) == std::string(difficulty, '0')) {
            break;
        }
        new_block.nonce++;
    }
    chain.push_back(new_block);
}

bool BlockchainEngine::validate_chain_integrity() const {
    for(size_t i = 1; i < chain.size(); i++) {
        const ChainBlock& curr = chain[i];
        const ChainBlock& prev = chain[i-1];
        
        if(curr.block_hash != generate_block_hash(curr)) return false;
        if(curr.prev_hash != prev.block_hash) return false;
        if(curr.block_hash.substr(0, difficulty) != std::string(difficulty, '0')) return false;
    }
    return true;
}

const std::vector<ChainBlock>& BlockchainEngine::get_chain() const {
    return chain;
}
