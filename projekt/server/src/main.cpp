#include <iostream>
#include <chrono>
#include <thread>
#include <csignal>
#include "Server.h"
#include "Servo.h"

extern "C" {
    #include "tof.h"
}

sig_atomic_t stop = false;

void stop_program(int sig) {
    (void) sig;
    stop = true;
}

void block_signals() {
    struct sigaction sa{};
    sa.sa_handler = stop_program;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGINT, &sa, nullptr);
}

int main() {
    block_signals();

    int handle = tofInit(1, 0x29, 1);
    if (handle != 1)
	{
        std::cerr << "VL53L0X init error" << std::endl;
		return -1;
	}

    int model, revision;
    tofGetModel(&model, &revision);
    std::cerr << "TOF model " << model << " revision " << revision << std::endl;

    Server server;
    Servo servo;
    servo.enable();
    int angle = 0;
    servo.set_factor(angle / 360.0);
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    while (!stop) {
        while (server.check_messages());
        std::cerr << server.client_count() << " clients" << std::endl;

        servo.set_factor(angle / 360.0);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        int distance = tofReadDistance();

        std::stringstream stream;
        stream << angle << " " << distance;
        server.send(stream.str());
        std::cerr << "Sent: " << stream.str() << std::endl;

        angle = (angle + 1) % 360;
    }
}
