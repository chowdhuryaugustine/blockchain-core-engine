#ifndef CHAIN_STATE_DB_H
#define CHAIN_STATE_DB_H

#include <string>
#include <map>
#include <cstdint>

class ChainStateDatabase {
private:
    std::map<std::string, uint64_t> account_balances;
    std::map<std::string, std::string> contract_storage;
    uint64_t total_supply;

public:
    ChainStateDatabase(uint64_t init_supply = 100000000);
    uint64_t get_balance(const std::string& address) const;
    void set_balance(const std::string& address, uint64_t balance);
    bool transfer_balance(const std::string& from, const std::string& to, uint64_t amount);
    void set_contract_data(const std::string& key, const std::string& value);
    std::string get_contract_data(const std::string& key) const;
    uint64_t get_total_supply() const;
};

#endif
