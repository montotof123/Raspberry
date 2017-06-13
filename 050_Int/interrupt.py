import RPi.GPIO as GPIO    # utilisation GPIO
import time     			# utilisation time
  
GPIO.setmode(GPIO.BCM)     # numérotation BCM
GPIO.setup(20, GPIO.IN, pull_up_down=GPIO.PUD_UP)    # GPIO20 en entrée avec résistance pull up  
 
eventCounter = 0

def my_interrupt(channel):
    global eventCounter
    eventCounter += 1
    print "Nb: ", eventCounter, " temps: ", time.time()

GPIO.add_event_detect(20, GPIO.FALLING, callback=my_interrupt)
	
try:  
    while True:            # Jusqu'à CTRL+C
        pass

finally:                   # Bloc de fin aprés CTRL-C 
    GPIO.cleanup()         # Nettoyage des GPIO (force les GPIO utilisés en entrée sans résistance)
    print "FIN"