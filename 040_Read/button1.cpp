#include <iostream>   // Include pour affichage et clavier
#include <signal.h>   // signal de fin de programme
#include <stdlib.h>   // librairie standard c++
#include <unistd.h>   // usleep
#include <wiringPi.h> // Include WiringPi library!

using namespace std;

// Pin number declarations. We're using the Broadcom chip pin numbers.
const int gpio23 = 23; // Regular LED - Broadcom pin 23, P1 pin 16
const int gpio20 = 20; // Regular LED - Broadcom pin 20, P1 pin 38

// Fonction de fin déclenchée par CTRL-C
void fin(int sig)
{
	// Désactive les résistances de pull up, pull down
	pullUpDnControl(gpio23, PUD_OFF);
	pullUpDnControl(gpio20, PUD_OFF);
	cout << "FIN signal: " << sig << endl;
	exit(0);
}

int main(void)
{
	// Ecoute du CTRL-C avec fonction à lancer
	signal(SIGINT, fin);
	
	// Setup 
	wiringPiSetupGpio(); // Initialize wiringPi -- using Broadcom pin numbers

	pinMode(gpio23, INPUT);
	pinMode(gpio20, INPUT);
	pullUpDnControl(gpio23, PUD_DOWN);
	pullUpDnControl(gpio20, PUD_UP);

	cout << "Press CTRL+C pour sortir" << endl;

	// Loop (while(1)):
	int compteur = 0;
	while(1)
	{
		cout << compteur << " GPIO23 = " << digitalRead(23) << " - GPIO20 = " << digitalRead(20) << endl;
		usleep(500000); // Wait 500ms
		compteur++;
	}
}
