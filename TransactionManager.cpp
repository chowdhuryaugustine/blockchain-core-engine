#include "TransactionManager.h"
#include <chrono>
#include <sstream>
#include <iomanip>
#include <openssl/md5.h>

std::string TransactionManager::generate_tx_id(const Transaction& tx) {
    std::stringstream ss;
    ss << tx.sender << tx.receiver << tx.amount << tx.timestamp;
    unsigned char hash[MD5_DIGEST_LENGTH];
    MD5((const unsigned char*)ss.str().c_str(), ss.str().size(), hash);
    
    std::stringstream res;
    for(int i = 0; i < MD5_DIGEST_LENGTH; i++) {
        res << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }
    return res.str();
}

void TransactionManager::create_transaction(const std::string& sender, const std::string& receiver, double amount) {
    if(amount <= 0) return;
    Transaction tx;
    tx.sender = sender;
    tx.receiver = receiver;
    tx.amount = amount;
    tx.timestamp = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    tx.is_confirmed = false;
    tx.tx_id = generate_tx_id(tx);
    pending_txs.push_back(tx);
}

std::vector<Transaction> TransactionManager::get_pending_transactions() const {
    return pending_txs;
}

void TransactionManager::confirm_transactions(const std::vector<std::string>& tx_ids) {
    for(auto it = pending_txs.begin(); it != pending_txs.end();) {
        bool found = false;
        for(const auto& id : tx_ids) {
            if(it->tx_id == id) {
                found = true;
                break;
            }
        }
        if(found) {
            it->is_confirmed = true;
            confirmed_txs[it->tx_id] = *it;
            it = pending_txs.erase(it);
        } else {
            ++it;
        }
    }
}

Transaction TransactionManager::get_transaction_by_id(const std::string& tx_id) const {
    auto conf_it = confirmed_txs.find(tx_id);
    if(conf_it != confirmed_txs.end()) return conf_it->second;
    
    for(const auto& tx : pending_txs) {
        if(tx.tx_id == tx_id) return tx;
    }
    return Transaction{};
}

size_t TransactionManager::get_pending_count() const {
    return pending_txs.size();
}
