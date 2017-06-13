#include <iostream>
#include <typeinfo>
#include <time.h>

#include "Gestion1Wire.h"
#include "GestionSlave1Wire.h"
#include "GestionDS18B20.h"
#include "GestionDS2431.h"

using namespace std;

int main(int argc, char ** argv)
{
	Gestion1Wire* oneWire = new Gestion1Wire();
	cout << "****************************************" << endl;
	cout << "*                MASTER                *" << endl;
	cout << "****************************************" << endl;
	cout << "Nom master: " << oneWire->getNomMaster() << endl;
	cout << "Nombre esclave: " << oneWire->getNombreSlaves() << endl;

	list<string> nomSlave = oneWire->getNomSlaves();
	list<GestionSlave1Wire*> lstSlave = oneWire->getLstSlaves();
	
	for (string nom : nomSlave) {
		cout << "Périphérique: " << nom << endl;
	}
	cout << endl;
	
	for (GestionSlave1Wire* slave : lstSlave) {
		cout << "*****************************************" << endl;
		cout << "*     Périphérique: " << slave->getNom() << "     *" << endl;
		cout << "*****************************************" << endl;
		cout << "FID: " << slave->getFID() << "/" << hex << slave->getFID() << "h" << dec << endl;
		cout << "slaveID: " << slave->getSlaveID() << endl;
		if(slave->getFID() == DS18B20) {
			GestionDS18B20* ds18b20Slave = dynamic_cast<GestionDS18B20*>(slave);
			MesureDS18B20 mesure = ds18b20Slave->getMesure();
			if(mesure.isMesureOK()) {
				cout << "Température: " << mesure.getTemperature() << endl;
			}
			cout << endl;
			delete ds18b20Slave; 
		}
		if(slave->getFID() == DS2431) {
			GestionDS2431* ds2431Slave = dynamic_cast<GestionDS2431*>(slave);
			time_t     now = time(0);
			struct tm  tstruct;
			char       buf[80];
			tstruct = *localtime(&now);
			strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);
			string message(buf);
			message += ": Ceci est la date et l'heure insérées dans l'eeprom";
			cout << "setMessage: " << ds2431Slave->setMessage(message) << endl;
			cout << "message: " << ds2431Slave->getMessage() << endl;
			cout << endl;
			delete ds2431Slave;
		}
	}
	
	delete oneWire;
	return 0;
}