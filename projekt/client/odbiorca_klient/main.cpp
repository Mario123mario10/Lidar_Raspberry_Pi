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

bool stop = false;

void stop_program(int sig)
{
    stop = true;
    sig = sig + 0;
}

int main(int argc, char *argv[]) {

//int main(){

    signal(SIGINT, stop_program);

    if (argc < 2)
    {
        std::cout << "Enter ip" << std::endl;
        return -1;
    }

    Client client(argv[1]);
    
    // for (size_t i = 0; i < 100; ++i) {
    //     std::cout << std::setw(2) << i << "  received: " << client.read() << std::endl;
    // }



    std::vector<double> vx = {};
    std::vector<double> vy = {};


    while (!stop) {

        std::string data = client.read();
        // changed data to stream
        std::stringstream SS(data);

        int angle, distance;

        SS >> angle >> distance;

        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "Received Hello" << std::endl;


        double x = distance * cos(angle * M_PI / 180);
        double y = distance * sin(angle * M_PI / 180);

        vx.push_back(x);
        vy.push_back(y);

        std::cout<< x << " " << y << " " << angle << " " << distance << std::endl;

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

