#include <pigpio.h>
#include <signal.h>   // signal de fin de programme
#include <stdlib.h>   // librairie standard c++

#define RED 14
#define GREEN 15
#define BLUE 18
#define SWITCH 16

int compteur = 0;

// Fonction de fin déclenchée par CTRL-C
// Semble ne pas fonctionner car la librairie dot intercepter le signal
void fin(int sig)
{
	gpioWrite(RED, 1);
	gpioWrite(GREEN, 1);
	gpioWrite(BLUE, 1);
	gpioTerminate();
	exit(0);
}

void setLed(int gpio, int level, uint32_t tick)
{
	// Change la couleur à chaque appui sur le bouton
	switch (compteur % 9) {
		case 0: 
			gpioWrite(RED, 0);
			gpioWrite(GREEN, 0);
			gpioWrite(BLUE, 0);
			break;
		case 1:
			gpioWrite(RED, 0);
			gpioWrite(GREEN, 0);
			gpioWrite(BLUE, 1);
			break;
		case 2:
			gpioWrite(RED, 0);
			gpioWrite(GREEN, 1);
			gpioWrite(BLUE, 0);
			break;
		case 3:
			gpioWrite(RED, 0);
			gpioWrite(GREEN, 1);
			gpioWrite(BLUE, 1);
			break;
		case 4:
			gpioWrite(RED, 1);
			gpioWrite(GREEN, 0);
			gpioWrite(BLUE, 0);
			break;
		case 5:
			gpioWrite(RED, 1);
			gpioWrite(GREEN, 0);
			gpioWrite(BLUE, 1);
			break;
		case 6:
			gpioWrite(RED, 1);
			gpioWrite(GREEN, 1);
			gpioWrite(BLUE, 0);
			break;
		case 7:
			gpioWrite(RED, 1);
			gpioWrite(GREEN, 1);
			gpioWrite(BLUE, 1);
			break;
		case 8:
			// Fait varier la couleur avec le PWM
			gpioSetPWMrange(RED, 100);
			gpioSetPWMrange(GREEN, 100);
			gpioSetPWMrange(BLUE, 100);
			gpioSetPWMfrequency(RED, 400);
			gpioSetPWMfrequency(GREEN, 400);
			gpioSetPWMfrequency(BLUE, 400);
			for(int r = 0; r < 100; r++) {
				for(int g = 0; g < 100; g++) {
					for(int b = 0; b < 100; b++) {
						gpioPWM(RED, r);
						gpioPWM(GREEN, g);
						gpioPWM(BLUE, b);
					}
				}
			}
			gpioWrite(RED, 1);
			gpioWrite(GREEN, 1);
			gpioWrite(BLUE, 1);
			break;
	}
	compteur++;
}

int main(int argc, char *argv[])
{
	// Ecoute du CTRL-C avec fonction à lancer
	signal(SIGINT, fin);

	if (gpioInitialise() <0 ) {
		return -1;
	}

	gpioSetMode(RED , PI_OUTPUT);
	gpioSetMode(GREEN , PI_OUTPUT);
	gpioSetMode(BLUE , PI_OUTPUT);
	gpioWrite(RED, 1);
	gpioWrite(GREEN, 1);
	gpioWrite(BLUE, 1);
	
	// Interruption a chaque appui sur le bouton
	gpioSetMode(SWITCH, PI_INPUT);
	gpioSetPullUpDown(SWITCH, PI_PUD_UP);
	gpioSetAlertFunc(SWITCH, setLed);

	// Boucle nfinie
	for(;;) { 
		time_sleep(0.7);
	}
	
	
}

