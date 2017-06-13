#!/usr/bin/env python
# -*- coding: utf-8 -*-
# Une LED branchée à la pin 18 clignote
import RPi.GPIO as GPIO  # bibliothèque pour utiliser les GPIO
import time              # bibliothèque pour gestion du temps
GPIO.setmode(GPIO.BCM)   # mode de numérotation des pins
GPIO.setup(18,GPIO.OUT)  # la pin 18 réglée en sortie (output)
while True:     # boucle répétée jusqu'à l'interruption du programme
    GPIO.output(18,GPIO.HIGH)   # sortie au niveau logique haut (3.3 V)
    time.sleep(0.009)              # on ne change rien pendant 1 ms 
    GPIO.output(18,GPIO.LOW)    # sortie au niveau logique bas (0 V)
    time.sleep(0.001)              # on ne change rien pendant 9 ms
