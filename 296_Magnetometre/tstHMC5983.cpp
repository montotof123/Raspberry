#include <iostream>
#include <wiringPi.h>

#include "GestionHMC5983.h"

using namespace std;

GestionHMC5983 hmc5983;

int main() {
	std::list<int8_t> data;
	hmc5983.init(hmc5983.AddressBase);
	
	cout << hmc5983.getId() << endl;
	cout << hmc5983.isMagnetometre() << endl;
	cout << hmc5983.Config(hmc5983.SensorOn, hmc5983._2, hmc5983._3, hmc5983.Normal, hmc5983._1090, hmc5983.SingleMesureament) << endl;
	for(int compteur = 0; ; compteur++) {
		while(!hmc5983.isReady());
		data = hmc5983.getRawAllAxes();
		
		cout << dec << "X=" << hmc5983.getRawAxeX();
		cout << " Y=" << hmc5983.getRawAxeY();
		cout << " Z=" << hmc5983.getRawAxeZ() << endl;
		cout <<  "X all=" << hmc5983.getRawFromAllAxeX();
		cout << " Y all=" << hmc5983.getRawFromAllAxeY();
		cout << " Z all=" << hmc5983.getRawFromAllAxeZ() << endl;
		cout << "X gauss=" << hmc5983.getGaussAxeX();
		cout << " Y gauss=" << hmc5983.getGaussAxeY();
		cout << " Z gauss=" << hmc5983.getGaussAxeZ() << endl;
		cout << "Temperature=" << hmc5983.getTemperature() << endl;
		
		cout << "cap=" << hmc5983.getCap() << endl << endl;
		
		hmc5983.setModeSelect(hmc5983.SingleMesureament);
		delay(1000);
	}}
