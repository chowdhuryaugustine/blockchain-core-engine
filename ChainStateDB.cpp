#include "ChainStateDB.h"

ChainStateDatabase::ChainStateDatabase(uint64_t init_supply) : total_supply(init_supply) {
    account_balances["genesis"] = init_supply;
}

uint64_t ChainStateDatabase::get_balance(const std::string& address) const {
    auto it = account_balances.find(address);
    return it != account_balances.end() ? it->second : 0;
}

void ChainStateDatabase::set_balance(const std::string& address, uint64_t balance) {
    account_balances[address] = balance;
}

bool ChainStateDatabase::transfer_balance(const std::string& from, const std::string& to, uint64_t amount) {
    if(get_balance(from) < amount) return false;
    account_balances[from] -= amount;
    account_balances[to] += amount;
    return true;
}

void ChainStateDatabase::set_contract_data(const std::string& key, const std::string& value) {
    contract_storage[key] = value;
}

std::string ChainStateDatabase::get_contract_data(const std::string& key) const {
    auto it = contract_storage.find(key);
    return it != contract_storage.end() ? it->second : "";
}

uint64_t ChainStateDatabase::get_total_supply() const {
    return total_supply;
}
