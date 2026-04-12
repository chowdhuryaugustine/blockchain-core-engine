#include "SmartContractVM.h"
#include "ChainStateDB.h"

extern ChainStateDatabase global_state;

bool SmartContractVirtualMachine::execute_op(ContractOp op, const std::vector<std::string>& args, ContractContext& ctx) {
    if(ctx.gas_limit == 0) return false;
    ctx.gas_limit--;
    
    switch(op) {
        case OP_STORE: {
            if(args.size() < 2) return false;
            ctx.storage[args[0]] = std::stoull(args[1]);
            return true;
        }
        case OP_LOAD: {
            if(args.size() < 1) return false;
            return ctx.storage.count(args[0]) > 0;
        }
        case OP_ADD: {
            if(args.size() < 3) return false;
            uint64_t a = std::stoull(args[1]);
            uint64_t b = std::stoull(args[2]);
            ctx.storage[args[0]] = a + b;
            return true;
        }
        case OP_SUB: {
            if(args.size() < 3) return false;
            uint64_t a = std::stoull(args[1]);
            uint64_t b = std::stoull(args[2]);
            ctx.storage[args[0]] = (a > b) ? (a - b) : 0;
            return true;
        }
        case OP_TRANSFER: {
            if(args.size() < 2) return false;
            uint64_t amount = std::stoull(args[1]);
            return global_state.transfer_balance(ctx.caller_address, args[0], amount);
        }
        case OP_BALANCE: {
            if(args.size() < 1) return false;
            ctx.storage[args[0]] = global_state.get_balance(ctx.caller_address);
            return true;
        }
        default: return false;
    }
}

bool SmartContractVirtualMachine::deploy_contract(const std::string& address) {
    return !address.empty();
}

bool SmartContractVirtualMachine::execute_contract(const std::string& contract_addr, const std::string& caller, 
                          const std::vector<ContractOp>& ops, const std::vector<std::string>& args, uint64_t gas) {
    ContractContext ctx;
    ctx.contract_address = contract_addr;
    ctx.caller_address = caller;
    ctx.gas_limit = gas;
    
    for(size_t i = 0; i < ops.size(); i++) {
        if(!execute_op(ops[i], args, ctx)) return false;
    }
    return true;
}

uint64_t SmartContractVirtualMachine::get_contract_storage(const std::string& addr, const std::string& key) {
    return 0;
}
