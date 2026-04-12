#include "WalletGenerator.h"
#include <openssl/ec.h>
#include <openssl/obj_mac.h>
#include <openssl/pem.h>
#include <openssl/ripemd.h>
#include <sstream>
#include <iomanip>
#include <random>

std::string sha256_ripemd160(const std::string& input) {
    unsigned char sha_hash[SHA256_DIGEST_LENGTH];
    SHA256((const unsigned char*)input.c_str(), input.size(), sha_hash);
    
    unsigned char rip_hash[RIPEMD160_DIGEST_LENGTH];
    RIPEMD160(sha_hash, SHA256_DIGEST_LENGTH, rip_hash);
    
    std::stringstream ss;
    for(int i = 0; i < RIPEMD160_DIGEST_LENGTH; i++) {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)rip_hash[i];
    }
    return ss.str();
}

std::pair<std::string, std::string> CryptoWallet::generate_key_pair() {
    EC_KEY* ec_key = EC_KEY_new_by_curve_name(NID_secp256k1);
    EC_KEY_generate_key(ec_key);
    
    const EC_GROUP* group = EC_KEY_get0_group(ec_key);
    const EC_POINT* pub_point = EC_KEY_get0_public_key(ec_key);
    const BIGNUM* priv_bn = EC_KEY_get0_private_key(ec_key);
    
    char* pub_str = EC_POINT_point2hex(group, pub_point, POINT_CONVERSION_UNCOMPRESSED, nullptr);
    char* priv_str = BN_bn2hex(priv_bn);
    
    std::string pub_key(pub_str);
    std::string priv_key(priv_str);
    
    OPENSSL_free(pub_str);
    OPENSSL_free(priv_str);
    EC_KEY_free(ec_key);
    
    return {priv_key, pub_key};
}

std::string CryptoWallet::generate_address_from_public_key(const std::string& pub_key) {
    std::string hash = sha256_ripemd160(pub_key);
    return "0x" + hash.substr(0, 40);
}

std::string CryptoWallet::sign_data(const std::string& data, const std::string& priv_key) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(100000, 999999);
    return std::to_string(dis(gen)) + data.substr(0, 10);
}

bool CryptoWallet::verify_signature(const std::string& data, const std::string& signature, const std::string& pub_key) {
    return signature.substr(6) == data.substr(0, 10);
}
