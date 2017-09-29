#include <wiringPi.h>
#include <iostream>

#include "GestionServoPCA9685.h"
#include "ListServo.h"

using namespace std;

GestionServoPCA9685 servo0(LED_0, ADDR_41, Sg90_PatteFG_Bassin_PCA9685);

int main() {
	// Test mouvement servo
	cout << "1:" << servo0.getCycleMin() << endl;
	cout << "1:" << servo0.getCycleMax() << endl;
	for(uint16_t val = servo0.getCycleMin(); val < servo0.getCycleMax(); val++) {
		cout << "1:" << val << endl;
		servo0.write(val);
		delay(50);
	}

	delay(3000);

	for(uint16_t val = servo0.getCycleMax(); val > servo0.getCycleMin(); val--) {
		cout << "2:" << val << endl;
		servo0.write(val);
		delay(50);
	}
	
	delay(3000);

	float angle = 0;
	while(angle < servo0.getAngleDebattement()) {
		cout << "3:" << angle << endl;
		servo0.write(angle);
		angle += 0.1;
		delay(5);
	}

	delay(3000);

	while(angle > 0.0) {
		cout << "4:" << angle << endl;
		servo0.write(angle);
		angle -= 0.1;
		delay(5);
	}
}
