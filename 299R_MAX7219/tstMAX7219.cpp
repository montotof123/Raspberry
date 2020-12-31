/*!
 *   \file    tstMAX7219.cpp
 *   \brief   Programme allumant des pixels sur les matrices
 *   \author  Totof (raspberry.pi123@orange.fr)
 *   \version 1.0
 *   \date    30/12/2020
 */
 
#include <iostream>
#include <pigpio.h>
#include <signal.h>
#include <stdlib.h>

#include "GestionMAX7219.h"
#include "GestionSPI.h"

using namespace std;

/**
 * \brief   Fonction de fin déclenchée par CTRL-C. 
 *
 * \details Force à sortir proprement du programme.
 *
 * \param   sig Le signal d'interruption ayant déclenché la fonction (ici sigint).
 */
void fin(int sig) 
{
	cout << "Fin" << endl;
	exit(0);
}

GestionMAX7219 MAX7219(GestionSpi::channel_0);

/**
 * \brief   Allume aléatoirement des LED sur la matrice, fin par CTRL-C. 
 */
int main(void) 
{
	// Ecoute du CTRL-C avec fonction à lancer.
	// Indispensable car sinon un CTRL-C bloque le bus spi obligeant à un reboot du Rpi
	signal(SIGINT, fin);

	MAX7219.test();
	MAX7219.test();
	MAX7219.test();
	MAX7219.test();
	// 2s.
	gpioDelay(2000000); 
	MAX7219.noTest();
	MAX7219.noTest();
	MAX7219.noTest();
	MAX7219.noTest();
	
	MAX7219.noDecode();
	
	MAX7219.setIntensity(0x03);

	MAX7219.scanLimit7();
	
	MAX7219.setDigit0(0x00);
	MAX7219.setDigit1(0x00);
	MAX7219.setDigit2(0x00);
	MAX7219.setDigit3(0x00);
	MAX7219.setDigit4(0x00);
	MAX7219.setDigit5(0x00);
	MAX7219.setDigit6(0x00);
	MAX7219.setDigit7(0x00);
	
	MAX7219.run();
	MAX7219.noOp();
	MAX7219.noOp();
	MAX7219.noOp();

	//Initialise la fonction random.
	srand (time(NULL));
	// Environ 1500s soit 25mn.
	for(int compteur = 0; compteur != 100; compteur++) { 
		char value =  rand() % 256;
		cout << (int)value << endl;
		MAX7219.setDigit0(value);
		// 3s.
		gpioDelay(3000000); 
		value =  rand() % 256;		
		MAX7219.setDigit7(value);
		// 3s.
		gpioDelay(3000000); 
		MAX7219.noOp();
		// 3s.
		gpioDelay(3000000); 
		MAX7219.noOp();
		// 3s.
		gpioDelay(3000000); 
		MAX7219.noOp();
		// 3s.
		gpioDelay(3000000);
	}
}