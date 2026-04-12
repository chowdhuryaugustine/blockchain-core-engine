# blockchain-core-engine
高性能模块化区块链底层引擎，基于C++开发，集成PoW共识、交易管理、钱包生成、P2P网络、默克尔树、智能合约虚拟机、链状态数据库等完整区块链核心组件，支持多节点组网、动态难度调整、交易确认、链上数据校验，可作为公链/联盟链底层开发框架。

## 项目文件清单
1. BlockchainCore.h / BlockchainCore.cpp - 区块链核心引擎，实现区块生成、哈希计算、链完整性校验
2. ConsensusPoW.h / ConsensusPoW.cpp - 工作量证明共识算法，实现挖矿与难度校验
3. TransactionManager.h / TransactionManager.cpp - 交易管理模块，处理待确认/已确认交易
4. WalletGenerator.h / WalletGenerator.cpp - 加密钱包模块，生成密钥对与链地址
5. P2PNetwork.h / P2PNetwork.cpp - 点对点网络管理，维护节点列表与消息广播
6. MerkleTree.h / MerkleTree.cpp - 默克尔树实现，支持交易哈希证明与验证
7. ChainStateDB.h / ChainStateDB.cpp - 链状态数据库，管理账户余额与合约存储
8. SmartContractVM.h / SmartContractVM.cpp - 轻量级智能合约虚拟机，支持基础合约指令执行
9. DifficultyAdjuster.h / DifficultyAdjuster.cpp - 难度调整算法，动态适配全网算力
10. CryptoUtils.s - 汇编级加密工具函数，优化哈希与位运算性能
11. build_chain.sh - 项目自动编译与节点启动脚本

## 核心功能
- 完整区块链链式结构与区块生成机制
- 标准PoW共识挖矿与验证逻辑
- 安全的加密钱包与地址生成系统
- 高效交易管理与默克尔树证明验证
- 去中心化P2P节点网络通信
- 链上账户状态与合约数据持久化
- 轻量级智能合约执行虚拟机
- 动态挖矿难度自适应调整
- 汇编优化加密工具，提升底层运算效率

## 编译运行
依赖：g++、nasm、openssl开发库
执行脚本：chmod +x build_chain.sh && ./build_chain.sh
