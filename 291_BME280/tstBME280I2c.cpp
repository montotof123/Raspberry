//====================================================
// Name        : tstBME280Spi.cpp
// Author      : totof
// Version     :
// Copyright   : Free
// Description : test de la librairie GestionBME280Spi
//====================================================

#include <iostream>	  // impression cout
#include <stdlib.h>   // La librairie standard
#include <signal.h>
#include <wiringPi.h> 
#include "GestionBME280.h"
#include "GestionBME280I2c.h"

using namespace std;

// Objets utilisés
GestionBME280I2c bme280(Adr_Low);

// *************************************
// Fonction de fin déclenchée par CTRL-C
// *************************************
void fin(int sig)
{
	cout << "Fin" << endl;
	exit(0);
}

// ******************
// Fonction pricipale
// ******************
int main() {
	// Ecoute du CTRL-C avec fonction à lancer
	signal(SIGINT, fin);

	cout << "Id                      = " << hex << (int)bme280.getId() << dec << endl;
	cout << "HumidityOversampling    = " << bme280.getHumidityOversampling() << endl;
	cout << "PressureOversampling    = " << bme280.getPressureOversampling() << endl;
	cout << "TemperatureOversampling = " << bme280.getTemperatureOversampling() << endl;
	cout << "Mode                    = " << bme280.getMode() << endl;
	cout << "Standby                 = " << bme280.getStandby() << endl;
	cout << "Filter                  = " << bme280.getFilter() << endl;
	
	for(;;) {

		bme280.getAllMesures();
		cout << "Temperature       = " << bme280.getTemperature() << " °C" << endl;
		cout << "Pression Pa       = " << bme280.getPressurePa() << " Pa" << endl;
		cout << "Pression hPa      = " << bme280.getPressureHectoPa() << " HPa" << endl;
		cout << "Pression hPa comp = " << bme280.getCompensedPressureHectoPa(108) << " HPa" << endl;
		cout << "Humidité          = " << bme280.getHumidity() << " %" << endl;
		cout << "Altitude          = " << bme280.getAltitude() << " m" << endl;
		cout << "Altitude  comp    = " << bme280.getCompensedAltitude(1012.43) << " m" << endl;
		delay(1000);
	}
}
