//============================
// Name        : SERVO.cpp
// Author      : totof
// Version     : 31/12/2016
// Copyright   : Free
// Description : Gère un servo
//============================

#include <stdlib.h>
#include <string>
#include <iostream>
#include "GestionServo.h"

using namespace std;

// ******************
// Fonction pricipale
// ******************
int main(int argc, char *argv[]) {
	if(argc != 5) {
		exit(EXIT_FAILURE);
	}
	
	string argv1Str(argv[1]);
	int cycleMin = stoi(argv1Str);
	string argv2Str(argv[2]);
	int cycleMax = stoi(argv2Str);
	string argv3Str(argv[3]);
	int debattement = stoi(argv3Str);
	string argv4Str(argv[4]);
	float angle = stof(argv4Str);

	GestionServo servo(cycleMin, cycleMax, debattement);
	servo.init();
	servo.noDesactivate();

	exit(EXIT_SUCCESS);
}
