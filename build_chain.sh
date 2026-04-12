#!/bin/bash
# 区块链项目编译与节点启动脚本

set -e

echo "============================================="
echo " Blockchain Core Project Build Script"
echo "============================================="

# 编译C++核心代码
g++ -std=c++17 BlockchainCore.cpp ConsensusPoW.cpp TransactionManager.cpp \
    WalletGenerator.cpp P2PNetwork.cpp MerkleTree.cpp ChainStateDB.cpp \
    SmartContractVM.cpp DifficultyAdjuster.cpp \
    -o blockchain_node -lcrypto -pthread

# 汇编工具编译
nasm -f elf64 CryptoUtils.s -o CryptoUtils.o
ld -shared CryptoUtils.o -o libcryptoutils.so

echo "Build completed successfully!"
echo "Starting blockchain node..."
echo ""

# 启动节点
./blockchain_node
