/*
 * GestionSPI.h
 *
 * Created on 22/08/2020
 * Author Totof
 *
 */
 
#ifndef GESTIONSPI_H_
#define GESTIONSPI_H_

#include <stdint.h>

class GestionSpi {
	public:
		enum Channel {
			channel_0 = 0,
			channel_1 = 1
		};

		enum Frequence {
			speed_27  = 1000000,
			speed_33  = 1250000,
			speed_50  = 2000000,
			speed_max = 6000000
		};
		
		GestionSpi(void);
		GestionSpi(Channel);
		GestionSpi(Channel, Frequence);
		bool initSpi(Channel, Frequence);
		
		bool isInitialize(void);
 
		uint16_t read(char[], uint16_t);
		uint16_t write(char[], uint16_t);
  
		virtual ~GestionSpi();
		
	private:
		int handle;
		bool initialize = false;
};

#endif // GESTIONSPI_H_