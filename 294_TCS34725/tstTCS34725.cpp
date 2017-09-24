#include <iostream>
#include <stdlib.h>
#include <wiringPi.h>

#include "GestionTCS34725.h"

using namespace std;

GestionTCS34725 tcs = GestionTCS34725(_700MS, _1X);

int main() {
	if (tcs.isIdentify()) {
		cout << "Found sensor" << endl;
	} else {
		cout << "No TCS34725 found ... check your connections" << endl;
		exit(-1);
	}
  
	while(1) {
		tcs.getRawData();
  
		cout << "Color Temp: " << tcs.calculateColorTemperature() << " K - " << endl;
		cout << "Lux: " << tcs.calculateLux() << " - " << endl;
		cout << "R: " << tcs.getRed() << endl;
		cout << "G: " << tcs.getGreen() << endl;
		cout << "B: " << tcs.getBlue() << endl;
		cout << "C: " << tcs.getClear() << endl;
		delay(5000);
	}
}
