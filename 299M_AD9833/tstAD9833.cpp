//=================================================
// Name        : tstAD9833.cpp
// Author      : totof
// Version     :
// Copyright   : Free
// Description : test de la librairie GestionAD9833
//=================================================

#include <iostream>	  // impression cout
#include <stdlib.h>   // La librairie standard
#include <signal.h>
#include <wiringPi.h>
#include "GestionAD9833.h"

using namespace std;

// Objets utilisés
Channel channel = channel_0;
GestionAD9833 ad9833(channel);

// *************************************
// Fonction de fin déclenchée par CTRL-C
// *************************************
void fin(int sig)
{
	cout << "Fin" << endl;
	exit(0);
}

// *******************
// Fonction principale
// *******************
int main() {
	// Ecoute du CTRL-C avec fonction à lancer
	signal(SIGINT, fin);
	
	cout << "Init Error   = " << ad9833.getInitError() << endl;
	cout << "SetFreq0     = " << ad9833.setFrequency(RegFreq0, 5000) << endl;
	cout << "SetFreq1     = " << ad9833.setFrequency(RegFreq1, 2500) << endl;
	cout << "SetPhase0    = " << ad9833.setPhase(RegPhase0, 100) << endl;
	cout << "SetPhase1    = " << ad9833.setPhase(RegPhase1, 0) << endl;
	cout << "Emit         = " << ad9833.emit(RegFreq0, RegPhase0, Sine) << endl;
	cout << "Freq0        = " << ad9833.getFrequency(RegFreq0) << endl;
	cout << "Freq1        = " << ad9833.getFrequency(RegFreq1) << endl;
	cout << "Phase0       = " << ad9833.getPhase(RegPhase0) << endl;
	cout << "Phase1       = " << ad9833.getPhase(RegPhase1) << endl;
	cout << "EmitRegFreq  = " << ad9833.getEmitRegFreq() << endl;
	cout << "EmitRegPhase = " << ad9833.getEmitRegPhase() << endl;
	cout << "EmitSignal   = " << ad9833.getEmitSignal() << endl;
	
	for(;;) {
		delay(500);
	}
}
