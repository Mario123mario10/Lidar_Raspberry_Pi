#ifndef SERVER_H
#define SERVER_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <array>
#include <cstring>
#include <vector>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_set>
#include <arpa/inet.h>

struct Socket {
    Socket() : addr{}, len(sizeof(sockaddr_in)) {}
    sockaddr_in addr;
    socklen_t len;

    bool operator==(const Socket& other) const {
        return this->addr.sin_port == other.addr.sin_port;
    }

    bool operator<(const Socket& other) const {
        if (addr.sin_addr.s_addr != other.addr.sin_addr.s_addr)
            return addr.sin_addr.s_addr < other.addr.sin_addr.s_addr;
        if (addr.sin_port != other.addr.sin_port)
            return addr.sin_port < other.addr.sin_port;
        return false;
    }

    friend std::ostream& operator<<(std::ostream& out, const Socket& socket);
};

struct SocketHash {
    size_t operator() (const Socket& socket) const {
        size_t hash = socket.addr.sin_addr.s_addr;
        hash = hash << 32;
        hash = hash + socket.addr.sin_port;
        return hash;
    }
};

class Server {
public:
    explicit Server(int port = 9090) {
        socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
        sockaddr_in server_addr{};
        server_addr.sin_family = AF_INET;
        server_addr.sin_addr.s_addr = INADDR_ANY;
        server_addr.sin_port = htons(port);
        if (bind(socket_fd, reinterpret_cast<sockaddr *>(&server_addr), sizeof(server_addr)) < 0) {
            throw std::runtime_error("bind failed");
        }
    }

    bool check_messages() {
        Socket s;
        ssize_t n = recvfrom(socket_fd,
                            buffer.data(),
                            buffer.size() - 1,
                            MSG_DONTWAIT,
                             reinterpret_cast<sockaddr *>(&s.addr),
                            &s.len);
        if (n < 0)
            return false;
        buffer[n] = '\0';
        std::string msg = buffer.data();
        bool already_registered = clients.find(s) != clients.end();
        if (msg != "START" && msg != "STOP") {
            std::cerr << "Ignoring unknown message: " << msg << std::endl;
        } else {
            if (!already_registered && msg == "START") {
                clients.insert(s);
                std::cerr << "Registered" << std::endl;
            } else if (already_registered && msg == "STOP") {
                clients.erase(s);
                std::cerr << "Unregistered" << std::endl;
            }
        }
        return true;
    }

    void send(const std::string &msg) {
        for (auto& client : clients) {
            ssize_t n = sendto(socket_fd,
                   msg.c_str(),
                   msg.size(),
                   MSG_DONTWAIT,
                   reinterpret_cast<const sockaddr *>(&client.addr),
                   client.len);
            if (n < 0) {
                perror("Server send sendto");
                std::cout << "Failed sending to " << client << ", ignoring\n";
            }
        }
    }

    [[nodiscard]] size_t client_count() const {
        return clients.size();
    }

    ~Server() {
        close(socket_fd);
    }
private:
    int socket_fd;
    std::array<char, 512> buffer{};
    std::unordered_set<Socket, SocketHash> clients;
};


#endif
