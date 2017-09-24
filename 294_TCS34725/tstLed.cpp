#include <iostream>

#include "GestionTCS34725.h"
#include "GestionLedRGBPCA9685.h"
#include "GestionLedPCA9685.h"

using namespace std;

GestionTCS34725 tcs = GestionTCS34725(_2_4MS, _60X);
GestionLedRGBPCA9685 ledRGB1(LED_3, LED_2, LED_1, CommonAnode, ADDR_41);
GestionLedRGBPCA9685 ledRGB2(LED_6, LED_5, LED_4, CommonAnode, ADDR_41);
GestionLedRGBPCA9685 ledRGB3(LED_9, LED_8, LED_7, CommonAnode, ADDR_41);
GestionLedRGBPCA9685 ledRGB4(LED_12, LED_11, LED_10, CommonAnode, ADDR_41);
GestionLedRGBPCA9685 ledRGB5(LED_15, LED_14, LED_13, CommonAnode, ADDR_41);
GestionLedPCA9685 led1(LED_0, ADDR_41);

int main() {
	if (tcs.isIdentify()) {
		cout << "Found sensor" << endl;
	} else {
		cout << "No TCS34725 found ... check your connections" << endl;
		exit(-1);
	}
  
	while(1) {
		tcs.getRawData();
		
		ledRGB1.setPercentRGB((float)tcs.getRed() / 65535.0 * 100.0, (float)tcs.getGreen() / 65535.0 * 100.0, (float)tcs.getBlue() / 65535.0 * 100.0);
		ledRGB2.setPercentRGB((float)tcs.getRed() / 65535.0 * 100.0, (float)tcs.getGreen() / 65535.0 * 100.0, (float)tcs.getBlue() / 65535.0 * 100.0);
		ledRGB3.setPercentRGB((float)tcs.getRed() / 65535.0 * 100.0, (float)tcs.getGreen() / 65535.0 * 100.0, (float)tcs.getBlue() / 65535.0 * 100.0);
		ledRGB4.setPercentRGB((float)tcs.getRed() / 65535.0 * 100.0, (float)tcs.getGreen() / 65535.0 * 100.0, (float)tcs.getBlue() / 65535.0 * 100.0);
		ledRGB5.setPercentRGB((float)tcs.getRed() / 65535.0 * 100.0, (float)tcs.getGreen() / 65535.0 * 100.0, (float)tcs.getBlue() / 65535.0 * 100.0);
		led1.setPercent(100.0 - (float)tcs.getClear() / 65535.0 * 100.0);
	}
}
