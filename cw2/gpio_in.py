import gpio4
import time

PIN = 27
BUTTON_PIN = 18

gpio = gpio4.SysfsGPIO(PIN)
gpio.export = True
gpio.direction = 'out'

button = gpio4.SysfsGPIO(BUTTON_PIN)
button.export = True
button.direction = 'in'

# 1 bo z ukladu przyciskanie robi zwarcie do masy
while button.value == 1:
	time.sleep(1/60)
gpio.value = 1
time.sleep(3)
gpio.value = 0

button.export = False
gpio.export = False
