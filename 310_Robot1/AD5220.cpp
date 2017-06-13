//============================
// Name        : SERVO.cpp
// Author      : totof
// Version     : 31/12/2016
// Copyright   : Free
// Description : Gère un servo
//============================

#include <stdlib.h>
#include <string>
#include <algorithm> 
#include "GestionAD5220.h"

using namespace std;

// ******************
// Fonction pricipale
// ******************
int main(int argc, char *argv[]) {
	if(argc != 5 && argc != 6) {
		exit(EXIT_FAILURE);
	}

	PinGPIO pinCLK;
	PinGPIO pinUD;
	PinGPIO pinCS;
	
	bool argv1ok;
	bool argv2ok;
	bool argv3ok;
	
	string argv1Str(argv[1]);
	transform(argv1Str.begin(), argv1Str.end(), argv1Str.begin(), ::toupper);
	if(argv1Str == "GPIO02") {
		pinCLK = GPIO02;
		argv1ok = true;
	}
	if(argv1Str == "GPIO03") {
		pinCLK = GPIO03;
		argv1ok = true;
	}
	if(argv1Str == "GPIO04") {
		pinCLK = GPIO04;
		argv1ok = true;
	}
	if(argv1Str == "GPIO17") {
		pinCLK = GPIO17;
		argv1ok = true;
	}
	if(argv1Str == "GPIO27") {
		pinCLK = GPIO27;
		argv1ok = true;
	}
	if(argv1Str == "GPIO22") {
		pinCLK = GPIO22;
		argv1ok = true;
	}
	if(argv1Str == "GPIO10") {
		pinCLK = GPIO10;
		argv1ok = true;
	}
	if(argv1Str == "GPIO09") {
		pinCLK = GPIO09;
		argv1ok = true;
	}
	if(argv1Str == "GPIO11") {
		pinCLK = GPIO11;
		argv1ok = true;
	}
	if(argv1Str == "GPIO05") {
		pinCLK = GPIO05;
		argv1ok = true;
	}
	if(argv1Str == "GPIO06") {
		pinCLK = GPIO06;
		argv1ok = true;
	}
	if(argv1Str == "GPIO13") {
		pinCLK = GPIO13;
		argv1ok = true;
	}
	if(argv1Str == "GPIO19") {
		pinCLK = GPIO19;
		argv1ok = true;
	}
	if(argv1Str == "GPIO26") {
		pinCLK = GPIO26;
		argv1ok = true;
	}
	if(argv1Str == "GPIO14") {
		pinCLK = GPIO14;
		argv1ok = true;
	}
	if(argv1Str == "GPIO15") {
		pinCLK = GPIO15;
		argv1ok = true;
	}
	if(argv1Str == "GPIO18") {
		pinCLK = GPIO18;
		argv1ok = true;
	}
	if(argv1Str == "GPIO23") {
		pinCLK = GPIO23;
		argv1ok = true;
	}
	if(argv1Str == "GPIO24") {
		pinCLK = GPIO24;
		argv1ok = true;
	}
	if(argv1Str == "GPIO25") {
		pinCLK = GPIO25;
		argv1ok = true;
	}
	if(argv1Str == "GPIO08") {
		pinCLK = GPIO08;
		argv1ok = true;
	}
	if(argv1Str == "GPIO07") {
		pinCLK = GPIO07;
		argv1ok = true;
	}
	if(argv1Str == "GPIO12") {
		pinCLK = GPIO12;
		argv1ok = true;
	}
	if(argv1Str == "GPIO16") {
		pinCLK = GPIO16;
		argv1ok = true;
	}
	if(argv1Str == "GPIO20") {
		pinCLK = GPIO20;
		argv1ok = true;
	}
	if(argv1Str == "GPIO21") {
		pinCLK = GPIO21;
		argv1ok = true;
	}
	
	string argv2Str(argv[2]);
	transform(argv2Str.begin(), argv2Str.end(), argv2Str.begin(), ::toupper);
	if(argv2Str == "GPIO02") {
		pinUD = GPIO02;
		argv2ok = true;
	}
	if(argv2Str == "GPIO03") {
		pinUD = GPIO03;
		argv2ok = true;
	}
	if(argv2Str == "GPIO04") {
		pinUD = GPIO04;
		argv2ok = true;
	}
	if(argv2Str == "GPIO17") {
		pinUD = GPIO17;
		argv2ok = true;
	}
	if(argv2Str == "GPIO27") {
		pinUD = GPIO27;
		argv2ok = true;
	}
	if(argv2Str == "GPIO22") {
		pinUD = GPIO22;
		argv2ok = true;
	}
	if(argv2Str == "GPIO10") {
		pinUD = GPIO10;
		argv2ok = true;
	}
	if(argv2Str == "GPIO09") {
		pinUD = GPIO09;
		argv2ok = true;
	}
	if(argv2Str == "GPIO11") {
		pinUD = GPIO11;
		argv2ok = true;
	}
	if(argv2Str == "GPIO05") {
		pinUD = GPIO05;
		argv2ok = true;
	}
	if(argv2Str == "GPIO06") {
		pinUD = GPIO06;
		argv2ok = true;
	}
	if(argv2Str == "GPIO13") {
		pinUD = GPIO13;
		argv2ok = true;
	}
	if(argv2Str == "GPIO19") {
		pinUD = GPIO19;
		argv2ok = true;
	}
	if(argv2Str == "GPIO26") {
		pinUD = GPIO26;
		argv2ok = true;
	}
	if(argv2Str == "GPIO14") {
		pinUD = GPIO14;
		argv2ok = true;
	}
	if(argv2Str == "GPIO15") {
		pinUD = GPIO15;
		argv2ok = true;
	}
	if(argv2Str == "GPIO18") {
		pinUD = GPIO18;
		argv2ok = true;
	}
	if(argv2Str == "GPIO23") {
		pinUD = GPIO23;
		argv2ok = true;
	}
	if(argv2Str == "GPIO24") {
		pinUD = GPIO24;
		argv2ok = true;
	}
	if(argv2Str == "GPIO25") {
		pinUD = GPIO25;
		argv2ok = true;
	}
	if(argv2Str == "GPIO08") {
		pinUD = GPIO08;
		argv2ok = true;
	}
	if(argv2Str == "GPIO07") {
		pinUD = GPIO07;
		argv2ok = true;
	}
	if(argv2Str == "GPIO12") {
		pinUD = GPIO12;
		argv2ok = true;
	}
	if(argv2Str == "GPIO16") {
		pinUD = GPIO16;
		argv2ok = true;
	}
	if(argv2Str == "GPIO20") {
		pinUD = GPIO20;
		argv2ok = true;
	}
	if(argv2Str == "GPIO21") {
		pinUD = GPIO21;
		argv2ok = true;
	}
	
	if(argc == 6) {
		string argv3Str(argv[3]);
		transform(argv3Str.begin(), argv3Str.end(), argv3Str.begin(), ::toupper);
		if(argv3Str == "GPIO02") {
			pinCS = GPIO02;
			argv3ok = true;
		}
		if(argv3Str == "GPIO03") {
			pinCS = GPIO03;
			argv3ok = true;
		}
		if(argv3Str == "GPIO04") {
			pinCS = GPIO04;
			argv3ok = true;
		}
		if(argv3Str == "GPIO17") {
			pinCS = GPIO17;
			argv3ok = true;
		}
		if(argv3Str == "GPIO27") {
			pinCS = GPIO27;
			argv3ok = true;
		}
		if(argv3Str == "GPIO22") {
			pinCS = GPIO22;
			argv3ok = true;
		}
		if(argv3Str == "GPIO10") {
			pinCS = GPIO10;
			argv3ok = true;
		}
		if(argv3Str == "GPIO09") {
			pinCS = GPIO09;
			argv3ok = true;
		}
		if(argv3Str == "GPIO11") {
			pinCS = GPIO11;
			argv3ok = true;
		}
		if(argv3Str == "GPIO05") {
			pinCS = GPIO05;
			argv3ok = true;
		}
		if(argv3Str == "GPIO06") {
			pinCS = GPIO06;
			argv3ok = true;
		}
		if(argv3Str == "GPIO13") {
			pinCS = GPIO13;
			argv3ok = true;
		}
		if(argv3Str == "GPIO19") {
			pinCS = GPIO19;
			argv3ok = true;
		}
		if(argv3Str == "GPIO26") {
			pinCS = GPIO26;
			argv3ok = true;
		}
		if(argv3Str == "GPIO14") {
			pinCS = GPIO14;
			argv3ok = true;
		}
		if(argv3Str == "GPIO15") {
			pinCS = GPIO15;
			argv3ok = true;
		}
		if(argv3Str == "GPIO18") {
			pinCS = GPIO18;
			argv3ok = true;
		}
		if(argv3Str == "GPIO23") {
			pinCS = GPIO23;
			argv3ok = true;
		}
		if(argv3Str == "GPIO24") {
			pinCS = GPIO24;
			argv3ok = true;
		}
		if(argv3Str == "GPIO25") {
			pinCS = GPIO25;
			argv3ok = true;
		}
		if(argv3Str == "GPIO08") {
			pinCS = GPIO08;
			argv3ok = true;
		}
		if(argv3Str == "GPIO07") {
			pinCS = GPIO07;
			argv3ok = true;
		}
		if(argv3Str == "GPIO12") {
			pinCS = GPIO12;
			argv3ok = true;
		}
		if(argv3Str == "GPIO16") {
			pinCS = GPIO16;
			argv3ok = true;
		}
		if(argv3Str == "GPIO20") {
			pinCS = GPIO20;
			argv3ok = true;
		}
		if(argv3Str == "GPIO21") {
			pinCS = GPIO21;
			argv3ok = true;
		}
	}
	
	int valeurPotentiometre;
	int valeurCible;
	if(argc == 5) {
		string argv3Str(argv[3]);
		valeurPotentiometre = stoi(argv3Str);
		string argv4Str(argv[4]);
		valeurCible = stoi(argv4Str);	
		GestionAD5220 ad5220(pinCLK, pinUD, valeurPotentiometre);
		ad5220.reInit();
		ad5220.writeOhm(valeurCible);
		ad5220.noDesactivate();
	}
	if(argc == 6) {
		string argv4Str(argv[4]);
		valeurPotentiometre = stoi(argv4Str);
		string argv5Str(argv[5]);
		valeurCible = stoi(argv5Str);			
		GestionAD5220 ad5220(pinCLK, pinUD, pinCS, valeurPotentiometre);
		ad5220.reInit();
		ad5220.writeOhm(valeurCible);
		ad5220.noDesactivate();
	}
	if(argv1ok && argv2ok && argv3ok) {
		exit(EXIT_SUCCESS);
	} else {
		exit(EXIT_FAILURE);
	}
}
