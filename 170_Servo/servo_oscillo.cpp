#include <iostream>		// Include pour affichage et clavier
#include <wiringPi.h> // Include WiringPi library!
#include <wiringPiSPI.h>
#include <linux/spi/spidev.h>
#include <stdint.h>

#include "mcp3208.h"

using namespace std;

// Pin number declarations. We're using the Broadcom chip pin numbers.
const int pwmPin = 18; // PWM LED - Broadcom pin 18, P1 pin 12

int pwmValue = 20; // Valeur cyclique à tester

int main(void)
{
    // Setup stuff:
    wiringPiSetupGpio(); // Initialize wiringPi -- using Broadcom pin numbers

    pinMode(pwmPin, PWM_OUTPUT); // Set PWM as PWM output
	pwmSetMode(PWM_MODE_MS);
	pwmSetClock(375);
	pwmSetRange(1024);
	pwmWrite(pwmPin, pwmValue); // Entre 0 et 1024
    wiringPiSPISetup (channel1, SPI_SPEED_33);
	
	cout << "temps;valeur" << endl;
	// Mesure le plus vite possible
	while(1){
		cout << clock() << ";" << conversion_mcp3208(channel1, voie_7) << endl;
	}

    return 0;
}