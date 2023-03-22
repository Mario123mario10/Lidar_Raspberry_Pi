import gpio_model
import util

def main():
    duration = 1
    def args(t):
        freq = 10
        period = 1 / freq
        duty = util.lerp(0.1, 0.9, t / duration)
        return period, duty
    model = gpio_model.GPIOModel(duration, args)
    model.run()

if __name__ == "__main__":
    main()
