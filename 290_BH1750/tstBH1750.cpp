//=================================================
// Name        : tstBH1750.cpp
// Author      : totof
// Version     : 19/05/2017
// Copyright   : Free
// Description : test de la librairie GestionBH1750
//=================================================

#include <iostream>	  // impression cout
#include <unistd.h>
#include "GestionBH1750.h"

using namespace std;

// Objets utilisés
GestionBH1750 bh1750(ADDRESS_AD0_HIGH);

// ******************
// Fonction pricipale
// ******************
int main() {
	for(int compteur = 0; compteur != 10; compteur++) {
		cout << "STD-BH1750_CONTINUOUS_HIGH_RES_MODE  : " << bh1750.readLightLevel(BH1750_CONTINUOUS_HIGH_RES_MODE) << endl;
		cout << "STD-BH1750_CONTINUOUS_HIGH_RES_MODE_2: " << bh1750.readLightLevel(BH1750_CONTINUOUS_HIGH_RES_MODE_2) << endl;
		cout << "STD-BH1750_CONTINUOUS_LOW_RES_MODE   : " << bh1750.readLightLevel(BH1750_CONTINUOUS_LOW_RES_MODE) << endl;
		cout << "STD-BH1750_ONE_TIME_HIGH_RES_MODE    : " << bh1750.readLightLevel(BH1750_ONE_TIME_HIGH_RES_MODE) << endl;
		cout << "STD-BH1750_ONE_TIME_HIGH_RES_MODE_2  : " << bh1750.readLightLevel(BH1750_ONE_TIME_HIGH_RES_MODE_2) << endl;
		cout << "STD-BH1750_ONE_TIME_LOW_RES_MODE     : " << bh1750.readLightLevel(BH1750_ONE_TIME_LOW_RES_MODE) << endl << endl;
	}
	cout << "BH1750_RESET                     : " <<  endl;
	bh1750.setState(BH1750_RESET);
	for(int compteur = 0; compteur != 10; compteur++) {
		cout << "DBL-BH1750_CONTINUOUS_HIGH_RES_MODE  : " << bh1750.readDoubleResolutionLightLevel(BH1750_CONTINUOUS_HIGH_RES_MODE) << endl;
		cout << "DBL-BH1750_CONTINUOUS_HIGH_RES_MODE_2: " << bh1750.readDoubleResolutionLightLevel(BH1750_CONTINUOUS_HIGH_RES_MODE_2) << endl;
		cout << "DBL-BH1750_CONTINUOUS_LOW_RES_MODE   : " << bh1750.readDoubleResolutionLightLevel(BH1750_CONTINUOUS_LOW_RES_MODE) << endl;
		cout << "DBL-BH1750_ONE_TIME_HIGH_RES_MODE    : " << bh1750.readDoubleResolutionLightLevel(BH1750_ONE_TIME_HIGH_RES_MODE) << endl;
		cout << "DBL-BH1750_ONE_TIME_HIGH_RES_MODE_2  : " << bh1750.readDoubleResolutionLightLevel(BH1750_ONE_TIME_HIGH_RES_MODE_2) << endl;
		cout << "DBL-BH1750_ONE_TIME_LOW_RES_MODE     : " << bh1750.readDoubleResolutionLightLevel(BH1750_ONE_TIME_LOW_RES_MODE) << endl << endl;
	}
	cout << "BH1750_RESET                     : " <<  endl;
	bh1750.setState(BH1750_RESET);
	for(int compteur = 0; compteur != 10; compteur++) {
		cout << "MAX-BH1750_CONTINUOUS_HIGH_RES_MODE  : " << bh1750.readMaxResolutionLightLevel(BH1750_CONTINUOUS_HIGH_RES_MODE) << endl;
		cout << "MAX-BH1750_CONTINUOUS_HIGH_RES_MODE_2: " << bh1750.readMaxResolutionLightLevel(BH1750_CONTINUOUS_HIGH_RES_MODE_2) << endl;
		cout << "MAX-BH1750_CONTINUOUS_LOW_RES_MODE   : " << bh1750.readMaxResolutionLightLevel(BH1750_CONTINUOUS_LOW_RES_MODE) << endl;
		cout << "MAX-BH1750_ONE_TIME_HIGH_RES_MODE    : " << bh1750.readMaxResolutionLightLevel(BH1750_ONE_TIME_HIGH_RES_MODE) << endl;
		cout << "MAX-BH1750_ONE_TIME_HIGH_RES_MODE_2  : " << bh1750.readMaxResolutionLightLevel(BH1750_ONE_TIME_HIGH_RES_MODE_2) << endl;
		cout << "MAX-BH1750_ONE_TIME_LOW_RES_MODE     : " << bh1750.readMaxResolutionLightLevel(BH1750_ONE_TIME_LOW_RES_MODE) << endl << endl;
	}
	cout << "BH1750_RESET                     : " <<  endl;
	bh1750.setState(BH1750_RESET);
	for(int compteur = 0; compteur != 10; compteur++) {
		cout << "MIN-BH1750_CONTINUOUS_HIGH_RES_MODE  : " << bh1750.readMinResolutionLightLevel(BH1750_CONTINUOUS_HIGH_RES_MODE) << endl;
		cout << "MIN-BH1750_CONTINUOUS_HIGH_RES_MODE_2: " << bh1750.readMinResolutionLightLevel(BH1750_CONTINUOUS_HIGH_RES_MODE_2) << endl;
		cout << "MIN-BH1750_CONTINUOUS_LOW_RES_MODE   : " << bh1750.readMinResolutionLightLevel(BH1750_CONTINUOUS_LOW_RES_MODE) << endl;
		cout << "MIN-BH1750_ONE_TIME_HIGH_RES_MODE    : " << bh1750.readMinResolutionLightLevel(BH1750_ONE_TIME_HIGH_RES_MODE) << endl;
		cout << "MIN-BH1750_ONE_TIME_HIGH_RES_MODE_2  : " << bh1750.readMinResolutionLightLevel(BH1750_ONE_TIME_HIGH_RES_MODE_2) << endl;
		cout << "MIN-BH1750_ONE_TIME_LOW_RES_MODE     : " << bh1750.readMinResolutionLightLevel(BH1750_ONE_TIME_LOW_RES_MODE) << endl << endl;
	}
}
