import gpio4
import time
import math

PIN = 17

def cycle(gpio, period, duty=0.5):
	gpio.value = 1
	time.sleep(period * duty)
	gpio.value = 0
	time.sleep(period * (1 - duty))

def position(gpio, value, duration):
	period = 0.020
	start = time.time()
	end = time.time() + duration
	t = 0
	freq = 1/period
	duty = 0.1 * 0.1 * period
	while time.time() < end:
		cycle(gpio, period, duty)
		t += period
		dt = start + t - time.time()
		if dt > 0:
			time.sleep(dt)

gpio = gpio4.SysfsGPIO(PIN)
gpio.export = True
gpio.direction = 'out'

for i in range(12):
	v = (i % 3) / 3
	position(gpio, v, 1)
gpio.export = False
