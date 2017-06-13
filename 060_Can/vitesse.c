/*vitesse.c*/

#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <stdint.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <time.h>
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
		printf("Nb: %d valeur brute = %d temps = %f\n", compteur, resultatBrut, (float)clock()/CLOCKS_PER_SEC);
		compteur++;
	}
	return 0 ;
}