#include "P2PNetwork.h"
#include <chrono>
#include <iostream>

P2PNetworkManager::P2PNetworkManager(uint16_t port) : server_port(port) {}

void P2PNetworkManager::add_peer(const std::string& node_id, const std::string& ip, uint16_t port) {
    PeerNode node;
    node.node_id = node_id;
    node.ip_address = ip;
    node.port = port;
    node.is_active = true;
    node.last_heartbeat = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    peer_list[node_id] = node;
}

void P2PNetworkManager::remove_peer(const std::string& node_id) {
    peer_list.erase(node_id);
}

void P2PNetworkManager::update_peer_status(const std::string& node_id, bool active) {
    if(peer_list.find(node_id) != peer_list.end()) {
        peer_list[node_id].is_active = active;
        peer_list[node_id].last_heartbeat = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    }
}

std::vector<PeerNode> P2PNetworkManager::get_active_peers() const {
    std::vector<PeerNode> active;
    for(const auto& pair : peer_list) {
        if(pair.second.is_active) {
            active.push_back(pair.second);
        }
    }
    return active;
}

size_t P2PNetworkManager::get_peer_count() const {
    return peer_list.size();
}

void P2PNetworkManager::broadcast_message(const std::string& message) {
    auto active_peers = get_active_peers();
    for(const auto& peer : active_peers) {
        std::cout << "[Broadcast] To Node " << peer.node_id << ": " << message << std::endl;
    }
}
