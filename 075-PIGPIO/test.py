import pigpio
import time

RED = 14
GREEN = 15
BLUE = 18
SWITCH = 16
compteur = 0

def setLed(gpio, level, tick):
    global compteur
    if compteur % 9 == 0:
        pi.write(RED, 0)
        pi.write(GREEN, 0)
        pi.write(BLUE, 0)
    if compteur % 9 == 1:
        pi.write(RED, 0)
        pi.write(GREEN, 0)
        pi.write(BLUE, 1)
    if compteur % 9 == 2:
        pi.write(RED, 0)
        pi.write(GREEN, 1)
        pi.write(BLUE, 0)
    if compteur % 9 == 3:
        pi.write(RED, 0)
        pi.write(GREEN, 1)
        pi.write(BLUE, 1)
    if compteur % 9 == 4:
        pi.write(RED, 1)
        pi.write(GREEN, 0)
        pi.write(BLUE, 0)
    if compteur % 9 == 5:
        pi.write(RED, 1)
        pi.write(GREEN, 0)
        pi.write(BLUE, 1)
    if compteur % 9 == 6:
        pi.write(RED, 1)
        pi.write(GREEN, 1)
        pi.write(BLUE, 0)
    if compteur % 9 == 7:
        pi.write(RED, 1)
        pi.write(GREEN, 1)
        pi.write(BLUE, 1)
    if compteur % 9 == 8:
        pi.set_PWM_range(RED, 100)
        pi.set_PWM_range(GREEN, 100)
        pi.set_PWM_range(BLUE, 100)
        pi.set_PWM_frequency(RED, 400)
        pi.set_PWM_frequency(GREEN, 400)
        pi.set_PWM_frequency(BLUE, 400)
        for r in range (0, 100):
            for g in range (0, 100):
                for b in range (0, 100):
                    pi.set_PWM_dutycycle(RED, r)
                    pi.set_PWM_dutycycle(GREEN, g)
                    pi.set_PWM_dutycycle(BLUE, b)
    compteur += 1;
  

pi = pigpio.pi()
pi.set_mode(RED, pigpio.OUTPUT)
pi.set_mode(GREEN, pigpio.OUTPUT)
pi.set_mode(BLUE, pigpio.OUTPUT)
pi.write(RED, 1)
pi.write(GREEN, 1)
pi.write(BLUE, 1)

pi.set_mode(SWITCH, pigpio.INPUT)
pi.set_pull_up_down(SWITCH, pigpio.PUD_UP)
pi.callback(SWITCH, pigpio.EITHER_EDGE, setLed)

while True:
    time.sleep(1)