#ifndef SERVER_H
#define SERVER_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <array>
#include <cstring>
#include <string>
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <chrono>
#include <thread>

struct ClientException {
    std::string message;
    ClientException(std::string message) : message(message) {}
};

class Client {
public:
    explicit Client(char* ip, int port = 9090) {
        socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
        server_addr.sin_family = AF_INET;
        server_addr.sin_addr.s_addr = inet_addr(ip);
        server_addr.sin_port = htons(port);

        send("START");
        std::cerr << "Registered" << std::endl;
    }

    std::string read() {
        socklen_t len = sizeof(server_addr);
        ssize_t n = recvfrom(socket_fd,
                            buffer.data(),
                            buffer.size() - 1,
                            MSG_WAITALL,
                            reinterpret_cast<sockaddr*>(&server_addr),
                            &len);
        if (n < 0)
            throw ClientException("read");
        buffer[n] = '\0';
        return buffer.data();
    }

    ~Client() {
        send("STOP");
        std::cerr << "Unregistered" << std::endl;
        close(socket_fd);
    }
private:
    void send(std::string msg) {
        ssize_t n = sendto(socket_fd,
               msg.c_str(),
               msg.size(),
               MSG_CONFIRM,
               reinterpret_cast<sockaddr*>(&server_addr),
               sizeof(server_addr));
        if (n < 0)
            throw ClientException("sendto");
    }

    int socket_fd;
    sockaddr_in server_addr{};
    std::array<char, 512> buffer{};
};


#endif
