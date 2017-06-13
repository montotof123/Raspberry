/* mcp3208.h
 * Controle un MCP3208 avec la librairie wiringPi sur Raspberry Pi */

#define voie_0	0
#define voie_1	1
#define voie_2	2
#define voie_3	3
#define voie_4	4
#define voie_5	5
#define voie_6	6
#define voie_7	7

#define	channel0	0
#define	channel1	1

#define	SPI_SPEED_27 1000000
#define	SPI_SPEED_33 1250000
#define	SPI_SPEED_50 2000000


int conversion_mcp3208(uint8_t adc, uint8_t num_voie);

int conversion_mcp3208(uint8_t adc, uint8_t num_voie){
	int conversion = 0, configuration = 0;
	unsigned char spiData[3] ;
	
	configuration = (num_voie<<6)|0x0600;			// configuration du mumero de voie & bit de start et single mode Ã  1 (voir documentation MCP3208)
	spiData[0] = configuration>>8;				// les 8 bits de msb de configuration sont ranges dans spiData[0]
	spiData[1] = configuration;				// les 8 bits de lsb de configuration sont ranges dans spiData[1]
	spiData[2] = 0x00;					// spiData[2] permet juste de generer la clock pour recuperer le resultat de conversion
	wiringPiSPIDataRW (adc, spiData, 3); 			// envoi des trois octets via le spi
	conversion = (int)(((spiData[1]&0x0F)<<8)|spiData[2]);	// masquage et mise en forme du resultat de conversion (0 a FFF)
	return conversion;
}