import gpio4
import time

PIN = 27

gpio = gpio4.SysfsGPIO(PIN)
gpio.export = True
gpio.direction = 'out'

for _ in range(10):
	gpio.value = 1
	time.sleep(0.5)
	gpio.value = 0
	time.sleep(0.5)

gpio.export = False
