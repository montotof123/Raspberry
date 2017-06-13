//================================
// Name        : GPIO.cpp
// Author      : totof
// Version     : 30/12/2016
// Copyright   : Free
// Description : Gère un port GPIO
//================================

#include <stdlib.h>
#include <algorithm> 
#include <string>
#include "GestionPinGPIO.h"

using namespace std;

GestionPinGPIO gpio;

// ******************
// Fonction pricipale
// ******************
int main(int argc, char *argv[]) {
	bool argv1ok = false;
	bool argv2ok = false;
	if(argc != 3) {
		exit(EXIT_FAILURE);
	}
	string argv1Str(argv[1]);
	transform(argv1Str.begin(), argv1Str.end(), argv1Str.begin(), ::toupper);
	if(argv1Str == "GPIO02") {
		gpio.init(GPIO02);
		argv1ok = true;
	}
	if(argv1Str == "GPIO03") {
		gpio.init(GPIO03);
		argv1ok = true;
	}
	if(argv1Str == "GPIO04") {
		gpio.init(GPIO04);
		argv1ok = true;
	}
	if(argv1Str == "GPIO17") {
		gpio.init(GPIO17);
		argv1ok = true;
	}
	if(argv1Str == "GPIO27") {
		gpio.init(GPIO27);
		argv1ok = true;
	}
	if(argv1Str == "GPIO22") {
		gpio.init(GPIO22);
		argv1ok = true;
	}
	if(argv1Str == "GPIO10") {
		gpio.init(GPIO10);
		argv1ok = true;
	}
	if(argv1Str == "GPIO09") {
		gpio.init(GPIO09);
		argv1ok = true;
	}
	if(argv1Str == "GPIO11") {
		gpio.init(GPIO11);
		argv1ok = true;
	}
	if(argv1Str == "GPIO05") {
		gpio.init(GPIO05);
		argv1ok = true;
	}
	if(argv1Str == "GPIO06") {
		gpio.init(GPIO06);
		argv1ok = true;
	}
	if(argv1Str == "GPIO13") {
		gpio.init(GPIO13);
		argv1ok = true;
	}
	if(argv1Str == "GPIO19") {
		gpio.init(GPIO19);
		argv1ok = true;
	}
	if(argv1Str == "GPIO26") {
		gpio.init(GPIO26);
		argv1ok = true;
	}
	if(argv1Str == "GPIO14") {
		gpio.init(GPIO14);
		argv1ok = true;
	}
	if(argv1Str == "GPIO15") {
		gpio.init(GPIO15);
		argv1ok = true;
	}
	if(argv1Str == "GPIO18") {
		gpio.init(GPIO18);
		argv1ok = true;
	}
	if(argv1Str == "GPIO23") {
		gpio.init(GPIO23);
		argv1ok = true;
	}
	if(argv1Str == "GPIO24") {
		gpio.init(GPIO24);
		argv1ok = true;
	}
	if(argv1Str == "GPIO25") {
		gpio.init(GPIO25);
		argv1ok = true;
	}
	if(argv1Str == "GPIO08") {
		gpio.init(GPIO08);
		argv1ok = true;
	}
	if(argv1Str == "GPIO07") {
		gpio.init(GPIO07);
		argv1ok = true;
	}
	if(argv1Str == "GPIO12") {
		gpio.init(GPIO12);
		argv1ok = true;
	}
	if(argv1Str == "GPIO16") {
		gpio.init(GPIO16);
		argv1ok = true;
	}
	if(argv1Str == "GPIO20") {
		gpio.init(GPIO20);
		argv1ok = true;
	}
	if(argv1Str == "GPIO21") {
		gpio.init(GPIO21);
		argv1ok = true;
	}

	string argv2Str(argv[2]);
	transform(argv2Str.begin(), argv2Str.end(), argv2Str.begin(), ::toupper);	
	if(argv2Str == "ON") {
		gpio.out();
		gpio.on();
		gpio.noDesactivate();
		argv2ok = true;
	}
	if(argv2Str == "OFF") {
		gpio.out();
		gpio.off();
		gpio.noDesactivate();
		argv2ok = true;
	}
	if(argv2Str == "DESACTIVATE") {
		gpio.toDesactivate();
		argv2ok = true;
	}
	
	if(argv1ok && argv2ok) {
		exit(EXIT_SUCCESS);
	} else {
		exit(EXIT_FAILURE);
	}
}
