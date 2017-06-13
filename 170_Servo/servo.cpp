#include <iostream>		// Include pour affichage et clavier
#include <wiringPi.h> // Include WiringPi library!

using namespace std;

// Pin number declarations. We're using the Broadcom chip pin numbers.
const int pwmPin = 18; // PWM LED - Broadcom pin 18, P1 pin 12

int pwmValue = 0; // Use this to set an LED brightness

int main(void)
{
    // Setup stuff:
    wiringPiSetupGpio(); // Initialize wiringPi -- using Broadcom pin numbers

    pinMode(pwmPin, PWM_OUTPUT); // Set PWM LED as PWM output
	pwmSetMode(PWM_MODE_MS);
	pwmSetClock(375);
	pwmSetRange(1024);
    cout << "PWM is running! Press CTRL+C to quit" << endl;

    // Loop (while(1)):
    while(1)
    {
		cout << "Rapport cyclique actuel: " << pwmValue << endl;
		cout << "Rapport cyclique désiré: ";
		cin >> pwmValue;
		pwmWrite(pwmPin, pwmValue); // Entre 0 et 1024
    }

    return 0;
}