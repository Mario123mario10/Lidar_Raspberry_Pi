import gpio_model
import util

def main():
    duration = 1
    def args(t):
        freq = util.lerp(10, 50, t / duration)
        period = 1 / freq
        duty = 0.5
        return period, duty
    model = gpio_model.GPIOModel(duration, args)
    model.run()

if __name__ == "__main__":
    main()
