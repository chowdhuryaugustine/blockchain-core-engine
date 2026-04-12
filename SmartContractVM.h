#ifndef SMART_CONTRACT_VM_H
#define SMART_CONTRACT_VM_H

#include <string>
#include <vector>
#include <map>

enum ContractOp {
    OP_STORE,
    OP_LOAD,
    OP_ADD,
    OP_SUB,
    OP_TRANSFER,
    OP_BALANCE
};

struct ContractContext {
    std::string contract_address;
    std::string caller_address;
    std::map<std::string, uint64_t> storage;
    uint64_t gas_limit;
};

class SmartContractVirtualMachine {
private:
    bool execute_op(ContractOp op, const std::vector<std::string>& args, ContractContext& ctx);

public:
    bool deploy_contract(const std::string& address);
    bool execute_contract(const std::string& contract_addr, const std::string& caller, 
                          const std::vector<ContractOp>& ops, const std::vector<std::string>& args, uint64_t gas);
    uint64_t get_contract_storage(const std::string& addr, const std::string& key);
};

#endif
