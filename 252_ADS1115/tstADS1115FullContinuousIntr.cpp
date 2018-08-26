#include "GestionADS1115Full.h"
#include "GestionPinGPIO.h"

#include <iostream>
#include <wiringPi.h>
#include <signal.h>	  // Fin
#include "GestionBigAffichage.h"

using namespace std;

GestionPinGPIO alerte(GPIO17);
GestionADS1115Full adc(ADDR_VCC);
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
	system("clear");
	float value = adc.getContinuousValue();
	cout << " mesure:" << compteur << " value:" << value << endl;
	GestionBigAffichage::affValue(value);
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
	
	adc.setGain(GAIN_2_048);
	adc.setRate(RATE_8SPS);
	
	// Indispensable pour programmer la broche ALRT/RDY
	adc.setComparator(CMODE_TRAD, CPOL_ACTVLOW, CLAT_NONLAT, CQUE_1CONV);
	
	adc.setContinuousMode(CHANNEL_SINGLE_0);
	
	// Indispensable pour programmer la broche ALRT/RDY
	adc.setHighValueComparator((int16_t)0x8000);
	adc.setLowValueComparator((int16_t)0x7FFF);	
	for(;;) {
		delay(500);
	}
}
