import RPi.GPIO as GPIO    # utilisation GPIO
from time import sleep     # utilisation sleep  
GPIO.setmode(GPIO.BCM)     # numérotation BCM
GPIO.setup(23, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)  # GPIO23 en entrée avec résistance pull down  
GPIO.setup(20, GPIO.IN, pull_up_down=GPIO.PUD_UP)    # GPIO20 en entrée avec résistance pull up  
  
try:  
    compteur = 0
    while True:            # Jusqu'à CTRL+C  
        print compteur, " GPIO23 = ", GPIO.input(23), " - GPIO20 = ", GPIO.input(20)
        sleep(0.5)         # Attend 0.5s
        compteur += 1;
  
finally:                   # Bloc de fin aprés CTRL-C 
    GPIO.cleanup()         # Nettoyage des GPIO (force les GPIO utilisés en entrée sans résistance)
    print "FIN"