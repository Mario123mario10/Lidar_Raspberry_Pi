import time
import util

def _plot(ts, vs):
    try:
        import matplotlib.pyplot as plt
        plt.plot(ts, vs, drawstyle='steps-post')
        plt.show()
        return True
    except ImportError:
        return False

class GPIOModel:
    def __init__(self, duration, arg_func, use_real_gpio=False, plot=True, pin_number=27):
        self._duration = duration
        self._arg_func = arg_func
        self._use_real_gpio = use_real_gpio
        self._plot = plot
        self._pin_number = pin_number

    def run(self):
        if self._use_real_gpio:
            import gpio4
            gpio = gpio4.SysfsGPIO(self._pin_number)
        else:
            import gpiomock
            gpio = gpiomock.GPIOMock(self._pin_number)
        gpio.export = True
        gpio.direction = "out"
        start = time.time()
        end = start + self._duration
        while time.time() < end:
            t = time.time() - start
            period, duty = self._arg_func(t)
            util.cycle(gpio, period, duty)
        gpio.export = False
        if not self._use_real_gpio and self._plot:
            hist = gpio.get_history()
            ts = [t for t, _ in hist]
            vs = [v for _, v in hist]
            if not _plot(ts, vs):
                print("No library to draw")

    def duration(self):
        return self._duration
