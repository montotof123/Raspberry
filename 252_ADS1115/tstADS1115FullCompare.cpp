#include "GestionADS1115Full.h"
#include "GestionBigAffichage.h"
#include "GestionPinGPIO.h"
#include <wiringPi.h>
#include <signal.h>	  // Fin
#include <iostream>

using namespace std;

GestionADS1115Full adc;
GestionPinGPIO alerte(GPIO17);

int compteur = 0;

// *************************************
// Fonction de fin déclenchée par CTRL-C
// *************************************
void fin(int sig)
{
    // Désactive les circuits
	alerte.~GestionPinGPIO();
    cout << "FIN signal: " << sig << endl;
    exit(0);
}

// -----------------------
// Fonction d'interruption
// -----------------------
void fctInterrupt(void) {
	compteur++;
}

int main(int argc, char *argv[])
{
	// Ecoute du CTRL-C avec fonction à lancer
    signal(SIGINT, fin);
	
	// Interruption broche ALRT
	alerte.pullUp();
	alerte.in();
	alerte.fctInterrupt(Falling, &fctInterrupt);

	adc.init(ADDR_VCC);
	adc.setGain(GAIN_4_096);
	adc.setRate(RATE_8SPS);
	adc.setSingleMode();
	
	// Programmation de la broche ALRT/RDY
	adc.setComparator(CMODE_WINDOW, CPOL_ACTVLOW, CLAT_NONLAT, CQUE_1CONV);
	adc.setHighValueComparator((float)2.0);
	adc.setLowValueComparator((float)1.0);	

    for (;;)
    {
		system("clear");
		cout << "Interruption: " << compteur << endl;
		GestionBigAffichage::affValue(adc.getSingleValue(CHANNEL_SINGLE_0));
		delay(500);
    }
    return 0;
}
