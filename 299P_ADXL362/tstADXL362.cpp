#include <iostream>
#include <pigpio.h>
#include <signal.h>

#include "GestionADXL362.h"
#include "GestionSPI.h"
#include "GestionBigAffichage.h"

using namespace std;

// *************************************
// Fonction de fin déclenchée par CTRL-C
// *************************************
void fin(int sig) {
	cout << "Fin" << endl;
	exit(0);
}

GestionADXL362 adxl362(GestionSpi::channel_0);
int main(void) {
	// Ecoute du CTRL-C avec fonction à lancer
	// Indispensable car sinon un CTRL-C bloque le bus spi obligeant à un reboot du Rpi
	signal(SIGINT, fin);

	adxl362.softReset();
	cout << "Device ID = " << hex << (int)adxl362.getDevId() << endl;
	cout << "MEMS      = " << hex << (int)adxl362.getMicroElectroMechanicalSystemId() << endl;
	cout << "Part Id   = " << dec << (int)adxl362.getPartId() << endl;
	cout << "Rev Id    = " << hex << (int)adxl362.getRevId() << endl;
	cout << "ADXL362   = " << dec << adxl362.isADXL362Device() << endl << endl;
	
	cout << "8bits X axis = " << hex << (int)adxl362.getXAxis8Msb() << endl;
	cout << "8bits Y axis = " << hex << (int)adxl362.getYAxis8Msb() << endl;
	cout << "8bits Z axis = " << hex << (int)adxl362.getZAxis8Msb() << endl << endl;
	
	cout << "Status          = " << hex << (int)adxl362.getStatus() << endl;
	cout << "  Error         = " << dec << (int)adxl362.isError() << endl;
	cout << "  Awake         = " << dec << (int)adxl362.isAwake() << endl;
	cout << "  Inactif       = " << dec << (int)adxl362.isInactif() << endl;
	cout << "  Actif         = " << dec << (int)adxl362.isActif() << endl;
	cout << "  FifoOverrun   = " << dec << (int)adxl362.isFifoOverrun() << endl;
	cout << "  FifoWatermark = " << dec << (int)adxl362.isFifoWatermark() << endl;
	cout << "  FifoReady     = " << dec << (int)adxl362.isFifoReady() << endl;
	cout << "  DataReady     = " << dec << (int)adxl362.isDataReady() << endl << endl;
	
	cout << "Nombre de mesures dans le Fifo = " << dec << (int)adxl362.getFifoEntries() << endl << endl;
	
	cout << "X axis = " << dec << (int)adxl362.getXAxisData() << endl;
	cout << "Y axis = " << dec << (int)adxl362.getYAxisData() << endl;
	cout << "Z axis = " << dec << (int)adxl362.getZAxisData() << endl;
	cout << "Temperature = " << dec << (int)adxl362.getTemperatureData() << endl << endl;
	
	cout << "Valeur d'activitée  = " << hex << (int)adxl362.getActivityThreshold() << endl;
	cout << "Nombre d'octets     = " << dec << (int)adxl362.setActivityThreshold(0x07FF) << endl;
	cout << "Valeur d'activitée  = " << hex << (int)adxl362.getActivityThreshold() << endl << endl;
	
	cout << "Temps d'activité    = " << hex << (int)adxl362.getActivityTime() << endl;
	cout << "Nombre d'octets     = " << dec << (int)adxl362.setActivityTime(0x59) << endl;
	cout << "Temps d'activité    = " << hex << (int)adxl362.getActivityTime() << endl << endl;
	
	cout << "Valeur d'inactivité = " << hex << (int)adxl362.getInactivityThreshold() << endl;
	cout << "Nombre d'octets     = " << dec << (int)adxl362.setInactivityThreshold(0x7AB) << endl;
	cout << "Valeur d'inactivité = " << hex << (int)adxl362.getInactivityThreshold() << endl << endl;
	
	cout << "Temps d'inactivité  = " << hex << (int)adxl362.getInactivityTime() << endl;
	cout << "Nombre d'octets     = " << dec << (int)adxl362.setInactivityTime(0xFEDC) << endl;
	cout << "Temps d'inactivité  = " << hex << (int)adxl362.getInactivityTime() << endl << endl;
	
	cout << "Activité          = " << hex << (int)adxl362.getActivityInactivity() << endl;
	cout << "Nombre d'octets   = " << dec << (int)adxl362.setActivityInactivity(0b00011111) << endl;
	cout << "Activité          = " << hex << (int)adxl362.getActivityInactivity() << endl;
	cout << "Activité LinkLoop = " << hex << (int)adxl362.getLinkLoopMode() << endl;
	cout << "Activité InactRef = " << hex << (int)adxl362.isInactRef() << endl;
	cout << "Activité InactEn  = " << hex << (int)adxl362.isInactEnable() << endl;
	cout << "Activité ActRef   = " << hex << (int)adxl362.isActRef() << endl;
	cout << "Activité ActEn    = " << hex << (int)adxl362.isActEnable() << endl;
	cout << "Activité          = " << hex << (int)adxl362.getActivityInactivity() << endl << endl;
	cout << "Nombre d'octets   = " << dec << (int)adxl362.setActivityInactivity(0b00000000) << endl;
	cout << "Activité          = " << hex << (int)adxl362.getActivityInactivity() << endl << endl;
	cout << "LinkLoop loop     = " << hex << (int)adxl362.setLinkLoopMode(adxl362.loop) << endl;
	cout << "Activité          = " << hex << (int)adxl362.getActivityInactivity() << endl;
	cout << "unSet InactRef    = " << hex << (int)adxl362.unSetInactRef() << endl;
	cout << "Activité          = " << hex << (int)adxl362.getActivityInactivity() << endl;
	cout << "set InactEn       = " << hex << (int)adxl362.setInactEnable() << endl;
	cout << "Activité          = " << hex << (int)adxl362.getActivityInactivity() << endl;
	cout << "unSet ActRef      = " << hex << (int)adxl362.unSetActRef() << endl;
	cout << "Activité          = " << hex << (int)adxl362.getActivityInactivity() << endl;
	cout << "set ActRef        = " << hex << (int)adxl362.setActEnable() << endl;
	cout << "Activité          = " << hex << (int)adxl362.getActivityInactivity() << endl << endl;
	cout << "Nombre d'octets   = " << dec << (int)adxl362.setActivityInactivity(0b00111111) << endl;
	cout << "Activité          = " << hex << (int)adxl362.getActivityInactivity() << endl;
	cout << "LinkLoop loop     = " << hex << (int)adxl362.setLinkLoopMode(adxl362.linked) << endl;
	cout << "Activité          = " << hex << (int)adxl362.getActivityInactivity() << endl;
	cout << "unSet InactRef    = " << hex << (int)adxl362.unSetInactRef() << endl;
	cout << "Activité          = " << hex << (int)adxl362.getActivityInactivity() << endl;
	cout << "set InactEn       = " << hex << (int)adxl362.setInactEnable() << endl;
	cout << "Activité          = " << hex << (int)adxl362.getActivityInactivity() << endl;
	cout << "unSet ActRef      = " << hex << (int)adxl362.unSetActRef() << endl;
	cout << "Activité          = " << hex << (int)adxl362.getActivityInactivity() << endl;
	cout << "set ActRef        = " << hex << (int)adxl362.setActEnable() << endl;
	cout << "Activité          = " << hex << (int)adxl362.getActivityInactivity() << endl;	
	
	adxl362.sampleInit1();
	
	for(int compteur = 0; compteur != 600; compteur++) { // 1 mn
		GestionBigAffichage::affValue(adxl362.getXAxisG());		
		//cout << "X axis = " << dec << adxl362.getXAxisG() << endl;
		//cout << "Y axis = " << dec << adxl362.getYAxisG() << endl;
		//cout << "Z axis = " << dec << adxl362.getZAxisG() << endl;
		//cout << "Temperature = " << dec << adxl362.getTemperatureCelcius() << endl << endl;
		gpioDelay(100000); // 100ms
	}
}