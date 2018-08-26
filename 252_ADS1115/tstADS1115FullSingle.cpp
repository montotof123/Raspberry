#include "GestionADS1115Full.h"

#include <iostream>
#include <wiringPi.h>

using namespace std;
int main(int argc, char *argv[])
{
    GestionADS1115Full adc;
	cout << adc.init(ADDR_VCC) << endl;;
	adc.setGain(GAIN_4_096);
	adc.setRate(RATE_860SPS);
	adc.setSingleMode();
    for (int i = 0; i < 4; ++i)
    {
	    int count = 5;
        while (count --) {
            cout << "channel:" << i << " mesure:" << count << " value:" << adc.getSingleValue(adc.getChannelByNumber(i)) << endl;
        }
    }

    return 0;
}
