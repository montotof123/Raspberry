#include <stdio.h>    // Used for printf() statements
#include <wiringPi.h> // Include WiringPi library!

// Pin number declarations. We're using the Broadcom chip pin numbers.
const int ledPin = 25; // Regular LED - Broadcom pin 25, P1 pin 22

int main(void)
{
    // Setup stuff:
    wiringPiSetupGpio(); // Initialize wiringPi -- using Broadcom pin numbers

    pinMode(ledPin, OUTPUT);     // Set regular LED as output

    printf("Blinker is running! Press CTRL+C to quit.\n");

    // Loop (while(1)):
    while(1)
    {
		// Do some blinking on the ledPin:
		digitalWrite(ledPin, HIGH); // Turn LED ON
		delay(500); // Wait 500ms
		digitalWrite(ledPin, LOW); // Turn LED OFF
		delay(500); // Wait 500ms again
    }

    return 0;
}
