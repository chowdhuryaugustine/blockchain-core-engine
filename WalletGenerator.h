#ifndef WALLET_GENERATOR_H
#define WALLET_GENERATOR_H

#include <string>
#include <utility>

class CryptoWallet {
public:
    static std::pair<std::string, std::string> generate_key_pair();
    static std::string generate_address_from_public_key(const std::string& pub_key);
    static bool verify_signature(const std::string& data, const std::string& signature, const std::string& pub_key);
    static std::string sign_data(const std::string& data, const std::string& priv_key);
};

#endif
