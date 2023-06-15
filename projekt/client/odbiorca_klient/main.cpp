#include <iostream>
#include <iomanip>
#include <string>
#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include <cmath>
#include <sstream>
#include <signal.h>
#include "Client.h"
#include "matplotlibcpp.h"

namespace plt = matplotlibcpp;

sig_atomic_t stop = false;

void stop_program(int sig) {
    (void) sig;
    stop = true;
}

void block_signals() {
    struct sigaction sa;
    sa.sa_handler = stop_program;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGINT, &sa, NULL);
}

int main(int argc, char *argv[]) {
    block_signals();

    if (argc < 2) {
        std::cerr << "Enter ip" << std::endl;
        return -1;
    }

    Client client(argv[1]);
    std::vector<double> vx = {};
    std::vector<double> vy = {};

    while (!stop) {
        std::string data;
        try {
            data = client.read();
        } catch (ClientException e) {
            std::cerr << "Client exception: " << e.message << std::endl;
            break;
        }
        std::stringstream SS(data);
        int angle, distance;
        SS >> angle >> distance;

        double x = distance * cos(angle * M_PI / 180);
        double y = distance * sin(angle * M_PI / 180);

        vx.push_back(x);
        vy.push_back(y);

        std::cout << x << " " << y << " " << angle << " " << distance << std::endl;

        plt::clf();
        // Plot line from given x and y data. Color is selected automatically.
        plt::plot(vx, vy);

        plt::xlim(-100, 100);
        plt::ylim(-100, 100);

        // Add graph title
        plt::title("Sample figure");
        // Enable legend.
        //plt::legend();
        // Display plot continuously
        plt::pause(0.1);
    }
}

