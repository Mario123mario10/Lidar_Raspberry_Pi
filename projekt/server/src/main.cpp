#include <iostream>
#include <chrono>
#include <thread>
#include "Server.h"


int main() {
    Server server;
    while (true) {
        std::cout << server.client_count() << " clients" << std::endl;
        while (server.check_messages());
        server.send();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}
