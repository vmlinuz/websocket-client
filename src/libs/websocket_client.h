//
// Created by mauro delazeri on 4/4/21.
//

#pragma once

#include <cstdint>
#include <string>
#include <memory>
#include <map>

struct request_info;

class socket_service;

class client_callback_t;

struct websocket_opaque_user_data {
    std::map<std::string, std::string> headers_map;
    // Add other fields if necessary
};

class websocket_client {
    client_callback_t *callback_;
    request_info *request_ = nullptr;
    socket_service *service_ = nullptr;
    std::string url_;
    websocket_opaque_user_data *user_data_ = nullptr;
    std::string address_;
    std::string origin_;
    std::string path_;
    int16_t port_ = -1;

public:
    websocket_client(client_callback_t *callback,
                     std::string url_,
                     std::map<std::string, std::string> headers_map = std::map<std::string, std::string>(),
                     std::string origin = "",
                     std::string ca_file_path = "",
                     int32_t cpu_affinity = -1,
                     bool use_global_service = false);

    virtual ~websocket_client() noexcept;

    [[nodiscard]] const std::string &url() const noexcept { return url_; }

    /**
     * Connect to WebSocket server
     * @return False if error occurred. Otherwise True.
     */
    bool connect() noexcept;

    /**
     * Stop WebSocket Client
     */
    void stop() noexcept;

    /**
     * Send message to WebSocket server
     * @param msg     The message to send
     * @param len     The length of the message
     * @return        True on success. Otherwise False.
     */
    bool send(const char *msg, size_t len) noexcept;
};