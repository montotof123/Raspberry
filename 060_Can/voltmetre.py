#!/usr/bin/python
 
import spidev
import time
import os
 
# Open SPI bus
spi = spidev.SpiDev()
spi.open(0,1)
 
# Fonction de lecture du MCP3208 via SPI
# Channel doit être un entier entre 0 et 7
def ReadChannel(channel):
  adc = spi.xfer2([4 | 2 | (channel >> 2), (channel & 3) << 6, 0])
  data = ((adc[1] & 15) << 8) + adc[2]
  return data
 
# Fonction pour convertir en volt
def ConvertVolts(data,places):
  volts = (data * 3.3) / float(4096)
  volts = round(volts,places)
  return volts
 
# Channel
channel = 0
 
# Delay
delay = 0.1
 
compteur = 0
while True:
 
  # Read the light sensor data
  level = ReadChannel(channel)
 
  # Affiche résultat
  print("Nb: {} tension = {} V valeur brute = {}".format(compteur, level, time.time()))
 
  compteur += 1