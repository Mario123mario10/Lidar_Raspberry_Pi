#ifndef PROJEKT_SERVO_H
#define PROJEKT_SERVO_H


#include <string>
#include <fstream>

class Servo {
public:
    Servo() {
        set_period(20);
        write(base_path + "/export", channel);
    }
    void set_period(double ms) {
        period_ns = static_cast<long>(1e6 * ms);
        recalculate();
    }
    void set_factor(double new_factor) {
        factor = new_factor;
        recalculate();
    }
    void set(bool enable) {
        enabled = enable;
        write(channel_path + "/enabled", enabled ? 1 : 0);
    }
    void enable() {
        set(true);
    }
    void disable() {
        set(false);
    }
    bool isEnabled() const {
        return enabled;
    }
    double getFactor() const {
        return factor;
    }
    ~Servo() {
        write(base_path + "/unexport", channel);
    }
private:
    void recalculate() {
        write(channel_path + "/period", period_ns);
        double duty = min_cycle + (max_cycle - min_cycle) * factor;
        long duty_ns = period_ns * duty;
        write(channel_path + "/duty_cycle", duty_ns);
    }
    void write(const std::string &path, long value) {
        std::ofstream out(path);
        out << std::to_string(value) << "\n";
    }
    void write(const std::string &path, const std::string &data) {
        std::ofstream out(path);
        out << data << "\n";
    }
    double min_cycle = 1;
    double max_cycle = 2;
    double factor = 0.5;
    long period_ns = 20e6;
    bool enabled = false;
    const std::string channel = "0";
    const std::string base_path = "/sys/class/pwm/pwmchip0";
    const std::string channel_path = base_path + "/pwm" + channel;
};


#endif //PROJEKT_SERVO_H
