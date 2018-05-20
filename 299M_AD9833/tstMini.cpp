#include <iostream>	  // impression cout
#include <wiringPi.h>
#include <wiringPiSPI.h>

int main() {
	unsigned char reset[2];
	reset[1] = 0x00;
	reset[0] = 0x21;
	unsigned char freq[6];
	freq[1] = 0x00;
	freq[0] = 0x21;
	freq[3] = 0x02;
	freq[2] = 0x4F;
	freq[5] = 0x00;
	freq[4] = 0x00;
	unsigned char freqC[2];
	freqC[1] = 0x00;
	freqC[0] = 0x21;
	unsigned char freqL[2];
	freqL[1] = 0xC7;
	freqL[0] = 0x50;
	unsigned char freqM[2];
	freqM[1] = 0x00;
	freqM[0] = 0x40;
	unsigned char phase[2];
	phase[1] = 0x00;
	phase[0] = 0xC0;
	unsigned char run[2];
	run[1] = 0x00;
	run[0] = 0x20;
	
	wiringPiSPISetupMode(0, 1250000, 2);
	wiringPiSPIDataRW (0, reset, 2);
	//wiringPiSPIDataRW (0, freqC, 2);
	wiringPiSPIDataRW (0, freqL, 2);
	wiringPiSPIDataRW (0, freqM, 2);
	wiringPiSPIDataRW (0, phase, 2);
	//wiringPiSPIDataRW (0, freq, 6);
	wiringPiSPIDataRW (0, run, 2);
	for(;;) {
		delay(1000);
	}
}
