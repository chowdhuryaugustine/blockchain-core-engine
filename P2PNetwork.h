#ifndef P2P_NETWORK_H
#define P2P_NETWORK_H

#include <string>
#include <vector>
#include <map>
#include <cstdint>

struct PeerNode {
    std::string node_id;
    std::string ip_address;
    uint16_t port;
    bool is_active;
    uint64_t last_heartbeat;
};

class P2PNetworkManager {
private:
    std::map<std::string, PeerNode> peer_list;
    uint16_t server_port;

public:
    P2PNetworkManager(uint16_t port = 8080);
    void add_peer(const std::string& node_id, const std::string& ip, uint16_t port);
    void remove_peer(const std::string& node_id);
    void update_peer_status(const std::string& node_id, bool active);
    std::vector<PeerNode> get_active_peers() const;
    size_t get_peer_count() const;
    void broadcast_message(const std::string& message);
};

#endif
