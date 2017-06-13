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
#include <fstream>
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
	
	mpu6050.setXGyroOffset(104);
	mpu6050.setYGyroOffset(-50);
	mpu6050.setZGyroOffset(49);	

	mpu6050.setXAccelOffset(-1783);
	mpu6050.setYAccelOffset(1776);
	mpu6050.setZAccelOffset(1939);	
	
	delay(3000);
	
	double accelX;
	double accelY;
	double accelZ;
	
	double vitesseX = 0.0;
	double vitesseY = 0.0;
	double vitesseZ = 0.0;
	double vitesseX0;
	double vitesseY0;
	double vitesseZ0;
	double vitesseXMoyenne;
	double vitesseYMoyenne;
	double vitesseZMoyenne;
	double distanceX = 0.0;
	double distanceY = 0.0;
	double distanceZ = 0.0;
	double tempsTotal = 0.0;
	double angleXZ;
	double angleYZ;
	
	svgHorloge = high_resolution_clock::now();
	
	// nom du fichier
	time_t rawtime;
	struct tm * timeinfo;
	char buffer[80];
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	strftime(buffer,sizeof(buffer),"%Y%m%d%I%M%S",timeinfo);
	string str(buffer);
	string nomFichier = "centrale" + str + ".csv";
	
	// Ouverture du fichier
	ofstream fichier(nomFichier.c_str(), ios::out | ios::trunc);

	// Entete fichier
	fichier << "temps;accelX;accelY;accelZ;angleXZ;angleYZ;accelXG;accelYG;";
	fichier << "vitesseX0;vitesseX;vitesseXMoyenne;distanceX;";
	fichier << "vitesseY0;vitesseY;vitesseYMoyenne;distanceY;tempsTotal" << endl;

	for(int nbBoucle = 0; nbBoucle != 2000; nbBoucle++) {
		// Calcul du temp de la boucle
		horloge = high_resolution_clock::now();
		time_span = duration_cast<chrono::duration<double>>(horloge - svgHorloge);
		svgHorloge = horloge;
		fichier << time_span.count() << ";";
		
		// Mesure acceleration
		accelX = (double)mpu6050.getAccelXMS();
		accelY = (double)mpu6050.getAccelYMS();
		accelZ = (double)mpu6050.getAccelZMS();
		fichier << accelX << ";";
		fichier << accelY << ";";
		fichier << accelZ << ";";
		
		angleXZ = atan2(accelX, accelZ);
		angleYZ = atan2(accelY, accelZ);
		fichier << angleXZ << ";";
		fichier << angleYZ << ";";

		accelX = accelX - EARTH_GRAVITY_0 * sin(angleXZ);
		accelY = accelY - EARTH_GRAVITY_0 * sin(angleYZ);
		fichier << accelX << ";";
		fichier << accelY << ";";
		
		// Calcul des distances
		if(time_span.count() != 0) {
			// Distance X
			vitesseX0 = vitesseX;
			vitesseX += accelX * time_span.count();
			vitesseXMoyenne = (vitesseX0 + vitesseX) / 2.0;
			distanceX += 0.5 * accelX * time_span.count() * time_span.count() + vitesseXMoyenne * time_span.count();
			fichier << vitesseX0 << ";";
			fichier << vitesseX << ";";
			fichier << vitesseXMoyenne << ";";
			fichier << distanceX << ";";
			
			// Distance Y
			vitesseY0 = vitesseY;
			vitesseY += accelY * time_span.count();
			vitesseYMoyenne = (vitesseY0 + vitesseY) / 2.0;
			distanceY += 0.5 * accelY * time_span.count() * time_span.count() + vitesseYMoyenne * time_span.count();			
			fichier << vitesseY0 << ";";
			fichier << vitesseY << ";";
			fichier << vitesseYMoyenne << ";";
			fichier << distanceY << ";";
		}
		
		// Affichage
		system("clear");
		cout << "temps total : " << tempsTotal << " s" << endl;
		cout << "temps : " << time_span.count() << " s" << endl;
		cout << "accelX : " << accelX << " m/s²" << endl;
		cout << "accelY : " << accelY << " m/s²" << endl;
		cout << "vitesseXMoyenne : " << vitesseXMoyenne << " m/s²" << endl;
		cout << "vitesseYMoyenne : " << vitesseYMoyenne << " m/s²" << endl;
		cout << "distanceX : " << round(distanceX * 100) / 100 << " m" << endl;
		cout << "distanceY : " << round(distanceY * 100) / 100 << " m" << endl;
		cout << "angleXZ : " << round(angleXZ * 180.0 / M_PI * 100) / 100 << "°" << endl;
		cout << "angleYZ : " << round(angleYZ * 180.0 / M_PI * 100) / 100 << "°" << endl;

		fichier << tempsTotal << endl;
		
		tempsTotal += time_span.count();
	}
	
	// Fermeture du fichier
	fichier.close();
}
