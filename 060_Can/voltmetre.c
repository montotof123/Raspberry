/*voltmetre.c*/

#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <stdint.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>

#include "mcp3208.h"

int resultatBrut = 0;
float resultat = 0;

int main (void)
{
	if(wiringPiSetupGpio() < 0)
		printf("erreur initialisation wiringPi\n");
	
	if(wiringPiSPISetup (channel1, SPI_SPEED_33) < 0)		//initialisation du SPI sur le "channel1" et a 1250kHz
		printf("erreur wiringPi SPI\n"); 
	
	
	int compteur = 0;
	while(1){
		resultatBrut = conversion_mcp3208(channel1, voie_0);
		resultat = (float)resultatBrut * 3.3 / 4096;
		printf("Nb: %d tension = %5.3f V valeur brute = %d\n", compteur, resultat, resultatBrut);
		delay(1);
		compteur++;
	}
	return 0 ;
}