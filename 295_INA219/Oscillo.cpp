#include <iostream>
#include <wiringPi.h>

#include "GestionINA219.h"
#include <chrono>     // Chronometre
#include <stdint.h>

using namespace std;
using namespace std::chrono;

GestionINA219 ina219;

int main() {
	ina219.init(ADDR_45);
	ina219.reset();
	ina219.setCalibration_3_2A(_32V, B_12Bits_1S_532US, S_9Bits_1S_84US, BusVoltageContinuous);
	cout << "temps;Bus voltage V" << endl;
	uint32_t initTime = static_cast<long int>(std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count());
	for(int compteur = 0; compteur != 10000; compteur++) {
		uint32_t time = static_cast<long int>(std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count());
		cout << time - initTime << ";" << ina219.getBusVoltage_V() * 1000 << endl;
	}
}
