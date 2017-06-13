//===================================================
// Name        : centrale.cpp
// Author      : totof
// Version     :
// Copyright   : Free
// Description : centrale inertielle
//===================================================

#include <iostream>	  // impression cout
#include <stdlib.h>   // La librairie standard
#include <wiringPi.h> 
#include <signal.h>
#include "GestionMPU6050.h"

using namespace std;

// Objets utilisés
GestionMPU6050 mpu6050(ADDRESS_AD0_HIGH);

// *************************************
// Fonction de fin déclenchée par CTRL-C
// *************************************
void fin(int sig)
{
	exit(0);
}

// ******************
// Fonction pricipale
// ******************
int main() {
	// Ecoute du CTRL-C avec fonction à lancer
	signal(SIGINT, fin);

	cout << "Test du MPU6050" << endl;
	mpu6050.defaultInitialize();
	cout << "Who am I: " << hex << (int)mpu6050.whoAmI() << dec << endl;
	if(mpu6050.isConnectionOK()) {
		cout << "Connection: OK" << endl;
	} else {
		cout << "Connection: KO" << endl;
		exit(-1);
	}
	
	mpu6050.setXGyroOffset(102);
	mpu6050.setYGyroOffset(-52);
	mpu6050.setZGyroOffset(52);	

	mpu6050.setXAccelOffset(-1752);
	mpu6050.setYAccelOffset(1776);
	mpu6050.setZAccelOffset(1936);	
	
	delay(3000);
	
	double giroX;
	double giroY;
	double giroZ;
	
	for(;;) {
		// Mesure rotation
		giroX = 0.0;
		giroY = 0.0;
		giroZ = 0.0;
		int nbBoucle = 10;
		for(int compteur = 0; compteur != nbBoucle; compteur++) {
			giroX += mpu6050.getGyroXDegS();
			giroY += mpu6050.getGyroYDegS();
			giroZ += mpu6050.getGyroZDegS();
		}
		giroX /= nbBoucle;
		giroY /= nbBoucle;
		giroZ /= nbBoucle;
		
		// Affichage
		system("clear");
		if (giroX < 0) {
			cout << "Tangage négatif (descendre): " << giroX << endl;
		}
		if (giroX > 0) {
			cout << "Tangage positif (monter): " << giroX << endl;
		}
		if (giroY < 0) {
			cout << "Roulis négatif (baisser à gauche): " << giroY << endl;
		}
		if (giroY > 0) {
			cout << "Roulis positif (baisser à droite): " << giroY << endl;
		}
		if (giroZ < 0) {
			cout << "Lacet négatif (tourner à droite): " << giroZ << endl;
		}
		if (giroZ > 0) {
			cout << "Lacet positif (tourner à gauche): " << giroZ << endl;
		}
	}
}
