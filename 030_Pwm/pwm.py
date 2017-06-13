#!/usr/bin/env python
# -*- coding: utf-8 -*-
import RPi.GPIO as GPIO
servo_pin = 18  # équivalent de GPIO 18
GPIO.setmode(GPIO.BCM)  # notation BCM
GPIO.setup(servo_pin, GPIO.OUT)  # pin configurée en sortie
pwm = GPIO.PWM(servo_pin, 50)  # pwm à une fréquence de 50 Hz
rapport = 7       # rapport cyclique initial de 7%
pwm.start(rapport)  
while True:
    print "Rapport cyclique actuel: " , rapport
    rapport = raw_input ("Rapport cyclique désiré:  ")
    pwm.ChangeDutyCycle(float(rapport))
