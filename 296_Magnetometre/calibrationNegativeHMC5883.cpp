#include <iostream>
#include <wiringPi.h>

#include "GestionHMC5883.h"

using namespace std;

GestionHMC5883 hmc5883;

int main() {
	
	std::list<int8_t> data;
	hmc5883.init(hmc5883.AddressBase);
	
	cout << hmc5883.getId() << endl;
	cout << hmc5883.isMagnetometre() << endl;
	
	cout << hmc5883.Config(hmc5883._2, hmc5883._75, hmc5883.NegativeBias, hmc5883._1090, hmc5883.SingleMesureament) << endl;
	for(int compteur = 0; ; compteur++) {
		while(!hmc5883.isReady());
		data = hmc5883.getRawAllAxes();
		
		cout << "X=" << hmc5883.getRawAxeX();
		cout << " Y=" << hmc5883.getRawAxeY();
		cout << " Z=" << hmc5883.getRawAxeZ() << endl;
		cout <<  "X all=" << hmc5883.getRawFromAllAxeX();
		cout << " Y all=" << hmc5883.getRawFromAllAxeY();
		cout << " Z all=" << hmc5883.getRawFromAllAxeZ() << endl;
		cout << "X gauss=" << hmc5883.getGaussAxeX();
		cout << " Y gauss=" << hmc5883.getGaussAxeY();
		cout << " Z gauss=" << hmc5883.getGaussAxeZ() << endl << endl;
		
		hmc5883.setModeSelect(hmc5883.SingleMesureament);
		delay(1000);
	}
}
