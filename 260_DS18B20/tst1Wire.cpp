#include <iostream>
#include <typeinfo>

#include "Gestion1Wire.h"
#include "GestionSlave1Wire.h"
#include "GestionDS18B20.h"

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
		GestionDS18B20* fullSlave = dynamic_cast<GestionDS18B20*>(slave);
		cout << "****************************************" << endl;
		cout << "*     Périphérique: " << fullSlave->getNom() << "    *" << endl;
		cout << "****************************************" << endl;
		cout << "FID: " << fullSlave->getFID() << endl;
		cout << "slaveID: " << fullSlave->getSlaveID() << endl;
		MesureDS18B20 mesure = fullSlave->getMesure();
		if(mesure.isMesureOK()) {
			cout << "Température: " << mesure.getTemperature() << endl;
		}
		cout << endl;
	}
	
	delete oneWire;
	return 0;
}