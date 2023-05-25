#include <iostream>
#include <iomanip>
#include "Client.h"

int main() {
    Client client;
    for (size_t i = 0; i < 100; ++i) {
        std::cout << std::setw(2) << i << "  received: " << client.read() << std::endl;
    }
}
