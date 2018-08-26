

#include "GestionADS1115.h"

#include <iostream>
#include <wiringPi.h>

using namespace std;
int main(int argc, char *argv[])
{
    GestionADS1115 adc(ADDR_VCC);

	adc.setGain(GAIN_4_096);
	adc.setRate(RATE_860SPS);
    for (int i = 0; i < 4; ++i)
    {
        int count = 5;
        while (count --) {
            cout << "channel:" << i << " mesure:" << count << " value:" << adc.getValue((Channel)i) << endl;
        }
        delay(500);
    }

    return 0;
}