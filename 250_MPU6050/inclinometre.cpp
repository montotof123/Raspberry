//===================================================
// Name        : inclinometre.cpp
// Author      : totof
// Version     :
// Copyright   : Free
// Description : calcul et affichage de l'inclinaison
//===================================================

#include <iostream>	  // impression cout
#include <stdlib.h>   // La librairie standard
#include <wiringPi.h> 
#include <signal.h>
#include <cmath>
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
	
	double angleXZ;
	double angleYZ;
	double accelX;
	double accelY;
	double accelZ;
	int compteur = 0;
	
	for(;;) {
		system("clear");
		accelX = (double)mpu6050.getAccelX();
		accelY = (double)mpu6050.getAccelY();
		accelZ = (double)mpu6050.getAccelZ();
		
		angleXZ = atan2(accelX, accelZ) * 180.0 / M_PI;
		angleYZ = atan2(accelY, accelZ) * 180.0 / M_PI;
		
		cout << "angleXZ : " << round(angleXZ * 100) / 100 << "°" << endl;
		cout << "angleYZ : " << round(angleYZ * 100) / 100 << "°" << endl;
		cout << "compteur: " << compteur << endl;
		compteur++;
		delay(100);
	}
}
