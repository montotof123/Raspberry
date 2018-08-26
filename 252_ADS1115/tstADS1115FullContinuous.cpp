#include "GestionADS1115Full.h"

#include <iostream>
#include <wiringPi.h>

using namespace std;
int main(int argc, char *argv[])
{
    GestionADS1115Full adc;
	cout << adc.init(ADDR_VCC) << endl;;
	adc.setGain(GAIN_2_048);
	adc.setRate(RATE_8SPS);
	adc.setContinuousMode(CHANNEL_SINGLE_0);
	for(int compteur = 0; compteur != 200; compteur++) {
           cout << " mesure:" << compteur << " value:" << adc.getContinuousValue() << endl;		
	}
    return 0;
}
