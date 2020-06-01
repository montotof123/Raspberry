#include "GestionPinGPIO.h"
#include <signal.h>   // signal de fin de programme
#include <stdlib.h>   // librairie standard c++

GestionPinGPIO red(GPIO14);
GestionPinGPIO green(GPIO15);
GestionPinGPIO blue(GPIO18);
GestionPinGPIO sensor(GPIO16);

int compteur = 0;

void setLed(int pi, unsigned int gpio, unsigned int level, unsigned int tick)
{
	// Change la couleur à chaque appui sur le bouton
	switch (compteur % 9) {
		case 0: 
			red.off();
			green.off();
			blue.off();
			break;
		case 1:
			red.off();
			green.off();
			blue.on();
			break;
		case 2:
			red.off();
			green.on();
			blue.off();
			break;
		case 3:
			red.off();
			green.on();
			blue.on();
			break;
		case 4:
			red.on();
			green.off();
			blue.off();
			break;
		case 5:
			red.on();
			green.off();
			blue.on();
			break;
		case 6:
			red.on();
			green.on();
			blue.off();
			break;
		case 7:
			red.on();
			green.on();
			blue.on();
			break;
		case 8:
			// Fait varier la couleur avec le PWM
			red.setPWMRange(100);
			green.setPWMRange(100);
			blue.setPWMRange(100);
			red.setPWMFrequency(400);
			green.setPWMFrequency(400);
			blue.setPWMFrequency(400);

			for(int r = 0; r < 100; r ++) {
				for(int g = 0; g < 100; g ++) {
					for(int b = 0; b < 100; b ++) {
						red.PWMOn(r);
						green.PWMOn(g);
						blue.PWMOn(b);
					}
				}
			}
			red.PWMOn();
			green.PWMOn();
			blue.PWMOn();
			break;
	}
	compteur++;
}

int main(int argc, char *argv[])
{
	red.out();
	green.out();
	blue.out();
	red.on();
	green.on();
	blue.on();
	
	// Interruption a chaque appui sur le bouton
	sensor.in();
	sensor.pullUp();
	sensor.fctInterrupt(setLed);

	// Boucle infinie
	for(;;) { 
		time_sleep(0.7);
	}
}

