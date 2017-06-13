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
#include <cmath>
#include <chrono>     // Chronometre
#include "GestionMPU6050.h"

using namespace std;
using namespace std::chrono;

// Objets utilisés
GestionMPU6050 mpu6050(ADDRESS_AD0_HIGH);

// Horloge
high_resolution_clock::time_point horloge;
high_resolution_clock::time_point svgHorloge;
duration<double> time_span;

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
	double angleX = 0.0;
	double angleY = 0.0;
	double angleZ = 0.0;
	svgHorloge = high_resolution_clock::now();

	for(;;) {
		// Calcul du temp de la boucle
		horloge = high_resolution_clock::now();
		time_span = duration_cast<chrono::duration<double>>(horloge - svgHorloge);
		svgHorloge = horloge;
		
		// Mesure rotation
		giroX = 0.0;
		giroY = 0.0;
		giroZ = 0.0;
		int nbBoucle = 10;
		for(int compteur = 0; compteur != nbBoucle; compteur++) {
			giroX += (double)mpu6050.getGyroXDegS();
			giroY += (double)mpu6050.getGyroYDegS();
			giroZ += (double)mpu6050.getGyroZDegS();
		}
		giroX /= nbBoucle;
		giroY /= nbBoucle;
		giroZ /= nbBoucle;
		
		// Calcul des angles
		if(time_span.count() != 0) {
			// Angles
			angleX += giroX * time_span.count();
			angleY += giroY * time_span.count();
			angleZ += giroZ * time_span.count();
		}
		
		// Affichage
		system("clear");
		cout << "temps : " << time_span.count() << " s" << endl;
		cout << "giroX : " << giroX << " °" << endl;
		cout << "giroY : " << giroY << " °" << endl;
		cout << "giroZ : " << giroZ << " °" << endl;
		cout << "angleX : " << angleX << " °" << endl;
		cout << "angleY : " << angleY << " °" << endl;
		cout << "angleZ : " << angleZ << " °" << endl;
	}
}
