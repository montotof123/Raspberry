//====================================
// Name        : ReadIrq.cpp
// Author      : totof
// Version     :
// Copyright   : Free
// Description : lit un module MFRC522
//====================================


#include <iostream>
#include <signal.h>	  // Fin, fonction cyclique
#include <unistd.h>	  // Delais pour les alarmes
#include "GestionPinGPIO.h"
#include "MFRC522.h"

MFRC522 mfrc;
bool mesureOk;

// *************************************
// Fonction de fin déclenchée par CTRL-C
// *************************************
void fin(int sig) {
    cout << "FIN signal: " << sig << endl;
    exit(0);
}

// ************************************
// Lecture d'une carte sur interruption
// ************************************
void irqEnabled(void) {
	// Print UID
	if(mesureOk) {
		for(byte i = 0; i < mfrc.uid.size; ++i) {
			if(mfrc.uid.uidByte[i] < 0x10) {
				cout << " 0";
				cout << hex << (int)mfrc.uid.uidByte[i];
			} else {
				cout << " ";
				cout << hex << (int)mfrc.uid.uidByte[i];
			}      
		}
		cout << endl;
		mesureOk = false;
	}
}

// ***********************************
// Fonction lancée cycliquement
// Demande si une mesure est diponible
// ***********************************
void alarmWakeup(int sig) {
	if(mfrc.PICC_IsNewCardPresent()) {
		mfrc.PICC_ReadCardSerial();
		mesureOk = true;
	}
}

int main(){
	// Broche d'interruption
	GestionPinGPIO irq(GPIO21);

	mfrc.PCD_Init();
	irq.in();
	irq.fctInterrupt(Rising, &irqEnabled);

    // Ecoute du CTRL-C avec fonction à lancer
    signal(SIGINT, fin);

	mesureOk = false;
	
	// Lancement cyclique d'un test de mesure
	// Toutes les milliseconde
	signal(SIGALRM, alarmWakeup);   
    ualarm(50000, 50000);

	while(1) {
	}
}