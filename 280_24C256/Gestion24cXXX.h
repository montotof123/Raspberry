/*
 * Gestion24cXXX.h
 *
 *  Created on: 5 may 2017
 *      Author: totof
 */

#ifndef GESTION24CXXX_H_
#define GESTION24CXXX_H_

#include "GestionPinGPIO.h"
#include "24cXX.h"

#define DEVICE "/dev/i2c-1"

// Liste des pin
enum Adresse {
  ADDR0 = 0x50,
  ADDR1 = 0x51,
  ADDR2 = 0x52,
  ADDR3 = 0x53
};

// Liste des directions
enum Direction {
	Read = 1,
	Write = 0
};

// Classe de gestion de l'I2C via le /dev/i2c-1
class Gestion24cXXX {
public:
	Gestion24cXXX(Adresse);
	Gestion24cXXX(Adresse, PinGPIO);
	bool getErrorFlag();
	const char* getErrorMessage();
	void writeProtect(bool);
	bool isWriteProtect();
	bool write(unsigned short, char);
	bool write(unsigned short, char*);
	char* read(unsigned short, int);

	virtual ~Gestion24cXXX();
	
private:
	Adresse adresse;
	bool errorFlag;
	const char* errorMessage;
	bool openI2Cdevice();
	GestionPinGPIO gpioWriteProtect;
	bool useWriteProtect;
	int file_i2c;
	struct eeprom e;
};

#endif /* GESTION24CXXX_H_ */
