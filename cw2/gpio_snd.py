import gpio4
import time
import math

PIN = 17

def cycle(gpio, period, duty=0.5):
	gpio.value = 1
	time.sleep(period * duty)
	gpio.value = 0
	time.sleep(period * (1 - duty))

gpio = gpio4.SysfsGPIO(PIN)
gpio.export = True
gpio.direction = 'out'

base_frequency = 261.63
mult = 2**(1/12)

for i in range(24):
	duration = 1
	start = time.time()
	end = time.time() + duration
	t = 0
	frequency = base_frequency * mult**i
	period = 1/frequency
	while time.time() < end:
		cycle(gpio, period, 0.5)
		t += period
		dt = start + t - time.time()
		if dt > 0:
			time.sleep(dt)
gpio.export = False
