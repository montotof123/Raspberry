#include <iostream>

#include "GestionServoPCA9685.h"
#include "ListServo.h"

using namespace std;

GestionServoPCA9685 servo0(LED_0, ADDR_41, Sg90_PatteFG_Bassin_PCA9685);

int main() {
	cout << "Min: " << servo0.getCycleMin() << endl;
	cout << "Max: " << servo0.getCycleMax() << endl;
	cout << "Deb: " << servo0.getAngleDebattement() << endl;
	
	while(1) {
		uint16_t valeur;
		cin >> valeur;
		servo0.write(valeur);
		cout << "Min: " << servo0.getCycleMin() << endl;
		cout << "Max: " << servo0.getCycleMax() << endl;
		cout << "Val: " << servo0.getValeur() << endl;
		cout << "Ang: " << servo0.getAngle() << endl << endl;
	}
}
