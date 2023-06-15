#ifndef PROJEKT_SERVO_H
#define PROJEKT_SERVO_H


#include <string>
#include <fstream>
#include <mutex>
#include <thread>

class Servo {
public:
    Servo() {
        write(gpio_base_path + "/export", pin);
        set_period(20);
        set_factor(0);
        thread = std::thread([this]() {
            mtx.lock();
            while (!thread_stop) {
                long thread_period_ns = period_ns;
                double thread_factor = factor;
                mtx.unlock();
                double min_cycle = 1;
                double max_cycle = 2;
                double duty = min_cycle + (max_cycle - min_cycle) * thread_factor;
                long duty_ns = thread_period_ns * duty;

                set_up();
                std::this_thread::sleep_for(std::chrono::nanoseconds(duty_ns));
                set_down();
                std::this_thread::sleep_for(std::chrono::nanoseconds(period_ns - duty_ns));
                mtx.lock();
            }
            mtx.unlock();
        });
    }
    void set_period(double ms) {
        mtx.lock();
        period_ns = static_cast<long>(1e6 * ms);
        mtx.unlock();
    }
    void set_factor(double new_factor) {
        mtx.lock();
        factor = new_factor;
        mtx.unlock();
    }
    ~Servo() {
        mtx.lock();
        thread_stop = true;
        mtx.unlock();
        thread.join();
        write(gpio_base_path + "/gpio" + pin + "/unexport", pin);
    }
private:
    void set_up() {
        write(gpio_base_path + "/gpio" + pin + "/value", 1);
    }
    void set_down() {
        write(gpio_base_path + "/gpio" + pin + "/value", 0);
    }
    void write(const std::string &path, long value) {
        std::ofstream out(path);
        out << std::to_string(value) << "\n";
    }
    void write(const std::string &path, const std::string &data) {
        std::ofstream out(path);
        out << data << "\n";
    }
    double factor = 0.5;
    long period_ns = 20e6;
    std::thread thread;
    std::mutex mtx;
    bool thread_stop = false;
    const std::string pin = "27";
    const std::string gpio_base_path = "/sys/class/gpio";
};


#endif //PROJEKT_SERVO_H
