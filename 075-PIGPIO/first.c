#include <pigpio.h>
#include <unistd.h>

#define GPIO 14

int main(int argc, char *argv[])
{
	if (gpioInitialise() <0 ) {
		return -1;
	}

	gpioSetMode(GPIO , PI_OUTPUT);

	for(int compteur = 0; compteur < 60; compteur++) {
		gpioWrite(GPIO, 1);
		sleep(1);
		gpioWrite(GPIO, 0);
		sleep(1);
	}
	gpioTerminate();
}

