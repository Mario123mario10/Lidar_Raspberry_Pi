#include <iostream>
#include <chrono>
#include <thread>
#include "Server.h"
// extern "C" {
//     #include "tof.h"
// }

int main() {
    // int handle = tofInit(1, 0x29, 1);
    // if (handle != 1)
	// {
    //     std::cerr << "VL53L0X init error" << std::endl;
	// 	return -1;
	// } else {
    //     int model, revision;
    //     tofGetModel(&model, &revision);
    //     std::cout << "model " << model << " revision " << revision << std::endl;
    //     while (true) {
    //         std::cout << tofReadDistance() << std::endl;
    //         std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    //     }
    // }
    Server server;
    while (true) {
        std::cout << server.client_count() << " clients" << std::endl;
        while (server.check_messages());

        for (int request_nbr = 0; request_nbr != 50; request_nbr++) {
            // send a message
            //std::cout << "Sending Hello " << request_nbr <<"…" << std::endl;

            // compose a message from a string and a number
            double dist = 100.0;
            if (request_nbr >= 20)
            dist = 80.0;

            server.send(request_nbr * 15.0, dist);
            std::this_thread::sleep_for(std::chrono::milliseconds(100));

        }
    }
}
