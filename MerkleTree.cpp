#include "MerkleTree.h"
#include <openssl/sha.h>
#include <sstream>
#include <iomanip>

std::string sha256(const std::string& str) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX ctx;
    SHA256_Init(&ctx);
    SHA256_Update(&ctx, str.c_str(), str.size());
    SHA256_Final(hash, &ctx);
    
    std::stringstream ss;
    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }
    return ss.str();
}

std::string MerkleTree::compute_hash(const std::string& left, const std::string& right) {
    return sha256(left + right);
}

MerkleTree::MerkleTree(const std::vector<std::string>& tx_hashes) {
    leaf_nodes = tx_hashes;
    build_tree();
}

void MerkleTree::build_tree() {
    tree_nodes = leaf_nodes;
    while(tree_nodes.size() > 1) {
        std::vector<std::string> new_level;
        for(size_t i = 0; i < tree_nodes.size(); i += 2) {
            if(i + 1 < tree_nodes.size()) {
                new_level.push_back(compute_hash(tree_nodes[i], tree_nodes[i+1]));
            } else {
                new_level.push_back(tree_nodes[i]);
            }
        }
        tree_nodes = new_level;
    }
}

std::string MerkleTree::get_root_hash() const {
    return tree_nodes.empty() ? "" : tree_nodes[0];
}

std::vector<std::string> MerkleTree::get_proof_path(size_t index) {
    std::vector<std::string> proof;
    size_t idx = index;
    std::vector<std::string> current = leaf_nodes;
    
    while(current.size() > 1) {
        if(idx % 2 == 0 && idx + 1 < current.size()) {
            proof.push_back(current[idx + 1]);
        } else if(idx % 2 == 1) {
            proof.push_back(current[idx - 1]);
        }
        idx /= 2;
        
        std::vector<std::string> next_level;
        for(size_t i = 0; i < current.size(); i += 2) {
            if(i + 1 < current.size()) {
                next_level.push_back(compute_hash(current[i], current[i+1]));
            } else {
                next_level.push_back(current[i]);
            }
        }
        current = next_level;
    }
    return proof;
}

bool MerkleTree::verify_proof(const std::string& leaf_hash, const std::vector<std::string>& proof, const std::string& root) {
    std::string current = leaf_hash;
    for(const auto& p : proof) {
        current = compute_hash(current, p);
    }
    return current == root;
}
