import time


def clamp(value, min_value=0.0, max_value=1.0):
    return max(min(value, max_value), min_value)


def cycle(gpio, period, duty, sleep=None):
    if sleep is None:
        sleep = time.sleep
    duty = clamp(duty)
    gpio.value = 1
    sleep(period * duty)
    gpio.value = 0
    sleep(period * (1 - duty))


def lerp(start, end, t):
    t = clamp(t)
    return start + t * (end - start)
