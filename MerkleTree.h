#ifndef MERKLE_TREE_H
#define MERKLE_TREE_H

#include <string>
#include <vector>

class MerkleTree {
private:
    std::vector<std::string> leaf_nodes;
    std::vector<std::string> tree_nodes;
    std::string compute_hash(const std::string& left, const std::string& right);
    void build_tree();

public:
    MerkleTree(const std::vector<std::string>& tx_hashes);
    std::string get_root_hash() const;
    std::vector<std::string> get_proof_path(size_t index);
    bool verify_proof(const std::string& leaf_hash, const std::vector<std::string>& proof, const std::string& root);
};

#endif
