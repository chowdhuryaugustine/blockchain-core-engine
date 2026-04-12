#include "ConsensusPoW.h"
#include <sstream>
#include <iomanip>
#include <openssl/sha.h>

ProofOfWork::ProofOfWork(uint32_t diff) : pow_difficulty(diff) {}

std::string calculate_sha256(const std::string& input) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((const unsigned char*)input.c_str(), input.length(), hash);
    std::stringstream ss;
    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }
    return ss.str();
}

std::string ProofOfWork::calculate_target_hash() const {
    return std::string(pow_difficulty, '0');
}

uint64_t ProofOfWork::mine_block(const std::string& block_header, std::string& out_hash) {
    uint64_t nonce = 0;
    std::string target = calculate_target_hash();
    while(true) {
        std::stringstream ss;
        ss << block_header << nonce;
        out_hash = calculate_sha256(ss.str());
        if(out_hash.substr(0, pow_difficulty) == target) {
            return nonce;
        }
        nonce++;
    }
}

bool ProofOfWork::validate_pow(const std::string& block_header, uint64_t nonce, const std::string& hash) const {
    std::stringstream ss;
    ss << block_header << nonce;
    std::string computed_hash = calculate_sha256(ss.str());
    return computed_hash == hash && hash.substr(0, pow_difficulty) == calculate_target_hash();
}

void ProofOfWork::update_difficulty(uint32_t new_diff) {
    pow_difficulty = new_diff;
}
