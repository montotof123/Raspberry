//==================================================
// Name        : tstMPU6050.cpp
// Author      : totof
// Version     :
// Copyright   : Free
// Description : test de la librairie GestionMPU6050
//==================================================

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
	
	for(;;) {
		system("clear");
		cout << "Acceleration X: " << mpu6050.getAccelXMS() << endl;
		cout << "Acceleration Y: " << mpu6050.getAccelYMS() << endl;
		cout << "Acceleration Z: " << mpu6050.getAccelZMS() << endl;
		cout << "Temperature   : " << mpu6050.getTempDeg() << endl;
		cout << "Gyroscope    X: " << mpu6050.getGyroX() << endl;
		cout << "Gyroscope    Y: " << mpu6050.getGyroY() << endl;
		cout << "Gyroscope    Z: " << mpu6050.getGyroZ() << endl;
		delay(100);
	}
}
