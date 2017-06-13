//==================================================
// Name        : readFactoryCalibration.cpp
// Author      : totof
// Version     : 1.0
// Copyright   : Free
// Description : Lecture du réglage usine du MPU6050
//==================================================

#include <iostream>	  // impression cout
#include <stdlib.h>   // La librairie standard
#include <wiringPi.h> 
#include "GestionMPU6050.h"

using namespace std;

// Objets utilisés
GestionMPU6050 mpu6050(ADDRESS_AD0_HIGH);

// ******************
// Fonction pricipale
// ******************
int main() {
	cout << "Réglage usine du MPU6050" << endl;
	mpu6050.defaultInitialize();
	cout << "Who am I: " << hex << (int)mpu6050.whoAmI() << endl;
	cout << "Connection: " << dec << mpu6050.isConnectionOK() << endl;
	
	cout << "getXGyroOffset: " << mpu6050.getXGyroOffset() << endl;
	cout << "getYGyroOffset: " << mpu6050.getYGyroOffset() << endl;
	cout << "getZGyroOffset: " << mpu6050.getZGyroOffset() << endl;

	cout << "getXAccelOffset: " << mpu6050.getXAccelOffset() << endl;
	cout << "getYAccelOffset: " << mpu6050.getYAccelOffset() << endl;
	cout << "getZAccelOffset: " << mpu6050.getZAccelOffset() << endl;
}
