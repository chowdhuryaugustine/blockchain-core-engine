#ifndef TRANSACTION_MANAGER_H
#define TRANSACTION_MANAGER_H

#include <string>
#include <vector>
#include <map>

struct Transaction {
    std::string tx_id;
    std::string sender;
    std::string receiver;
    double amount;
    uint64_t timestamp;
    bool is_confirmed;
};

class TransactionManager {
private:
    std::vector<Transaction> pending_txs;
    std::map<std::string, Transaction> confirmed_txs;
    std::string generate_tx_id(const Transaction& tx);

public:
    void create_transaction(const std::string& sender, const std::string& receiver, double amount);
    std::vector<Transaction> get_pending_transactions() const;
    void confirm_transactions(const std::vector<std::string>& tx_ids);
    Transaction get_transaction_by_id(const std::string& tx_id) const;
    size_t get_pending_count() const;
};

#endif
