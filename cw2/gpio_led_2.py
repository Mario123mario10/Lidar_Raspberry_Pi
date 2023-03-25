import gpio4
import time
import math

PIN = 27

def cycle(gpio, period, duty=0.5):
	gpio.value = 1
	time.sleep(period * duty)
	gpio.value = 0
	time.sleep(period * (1 - duty))

gpio = gpio4.SysfsGPIO(PIN)
gpio.export = True
gpio.direction = 'out'

duration = 10
start = time.time()
end = time.time() + duration
t = 0
frequency = 100
period = 1/frequency

while time.time() < end:
	duty = math.sin(math.pi * t/duration)
	print(duty)
	cycle(gpio, period, duty)
	t += period
	dt = start + t - time.time()
	if dt > 0:
		time.sleep(dt)

gpio.export = False
