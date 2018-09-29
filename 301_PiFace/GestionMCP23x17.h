/*
 * GESTIONMCP23x17.h
 *
 *  Created on: 13 novembre 2016
 *      Author: totof
 */

#ifndef GESTIONMCP23x17_H_
#define GESTIONMCP23x17_H_

// Liste des type de registres
enum TypeRegistre {
	IODIR = 0,
	IPOL = 1,
	GPINTEN = 2,
	DEFVAL = 3,
	INTCON = 4,
	IOCON = 5,
	GPPU = 6,
	INTF = 7,
	INTCAP = 8,
	GPIO = 9,
	OLAT = 10
};

// Liste des registres
enum Registre {
	IODIRA0 = 0x00,
	IODIRB0 = 0x01,
	IPOLA0 = 0x02,
	IPOLB0 = 0x03,
	GPINTENA0 = 0x04,
	GPINTENB0 = 0x05,
	DEFVALA0 = 0x06,
	DEFVALB0 = 0x07,
	INTCONA0 = 0x08,
	INTCONB0 = 0x09,
	IOCON0 = 0x0A,
	GPPUA0 = 0x0C,
	GPPUB0 = 0x0D,
	INTFA0 = 0x0E,
	INTFB0 = 0x0F,
	INTCAPA0 = 0x10,
	INTCAPB0 = 0x11,
	GPIOA0 = 0x12,
	GPIOB0 = 0x13,
	OLATA0 = 0x14,
	OLATB0 = 0x15,
	IODIRA1 = 0x00,
	IODIRB1 = 0x10,
	IPOLA1 = 0x01,
	IPOLB1 = 0x11,
	GPINTENA1 = 0x02,
	GPINTENB1 = 0x12,
	DEFVALA1 = 0x03,
	DEFVALB1 = 0x13,
	INTCONA1 = 0x04,
	INTCONB1 = 0x14,
	IOCON1 = 0x05,
	GPPUA1 = 0x06,
	GPPUB1 = 0x16,
	INTFA1 = 0x07,
	INTFB1 = 0x17,
	INTCAPA1 = 0x18,
	INTCAPB1 = 0x18,
	GPIOA1 = 0x09,
	GPIOB1 = 0x19,
	OLATA1 = 0x0A,
	OLATB1 = 0x1A
};

// Adresse
enum Adresse {
	Adr0 = 0x00,
	Adr1 = 0x01,
	Adr2 = 0x02,
	Adr3 = 0x03,
	Adr4 = 0x04,
	Adr5 = 0x05,
	Adr6 = 0x06,
	Adr7 = 0x07
};

// Port
enum Port {
	PortA = 0,
	PortB = 1
};

// Bit
enum Bit {
	Bit7 = 0x80,
	Bit6 = 0x40,
	Bit5 = 0x20,
	Bit4 = 0x10,
	Bit3 = 0x08,
	Bit2 = 0x04,
	Bit1 = 0x02,
	Bit0 = 0x01,
	NoBit = 0x00,
	AllBit = 0xFF
};

// Bit IOCON
enum BitIOCON {
	Bank = 0x80,
	Mirror = 0x40,
	SeqOp = 0x20,
	DisSlw = 0x10,
	HaEn = 0x08,
	Odr = 0x04,
	IntPol = 0x02,	
	NoData = 0x00
};

enum BANK {
	Bank0 = 0,
	Bank1 = 1
};

namespace std {

// Classe de gestion des MCP23S17 et MCP23017
class GestionMCP23x17{
public:
	GestionMCP23x17();
	// IODIRA IODIRB
	unsigned char readDirection(Port);
	void writeDirection(Port, unsigned char);
	void allBitInput(Port);
	void allBitOutput(Port);
	// IPOLA IPOLB
	unsigned char readPolarity(Port);
	void writePolarity(Port, unsigned char);
	// GPINTENA GPINTENB
	unsigned char readInterruptOnChange(Port);
	void writeInterruptOnChange(Port, unsigned char);
	// DEFVALA DEFVALB
	unsigned char readDefaultCompare(Port);
	void writeDefaultCompare(Port, unsigned char);
	// INTCONA INTCONB
	unsigned char readInterruptControl(Port);
	void writeInterruptControl(Port, unsigned char);
	// IOCON
	unsigned char readConfiguration();
	void writeConfiguration(unsigned char);
	unsigned char createConfiguration(BitIOCON pBitA, BitIOCON pBitB = NoData, BitIOCON pBitC = NoData, BitIOCON pBitD = NoData, BitIOCON pBitE = NoData, BitIOCON pBitF = NoData, BitIOCON pBitG = NoData);
	// GPPUA GPPUB
	unsigned char readPullUpResistor(Port);
	void writePullUpResistor(Port, unsigned char);
	// INTFA INTFB
	unsigned char readInterruptFlag(Port);
	// INTCAPA INTCAPB
	unsigned char readInterrupCapture(Port);
	// GPIOA GPIOB
	unsigned char readPort(Port);
	void writePort(Port, unsigned char);
	// OLATA OLATB
	unsigned char readOutputLatch(Port);
	void writeOutputLatch(Port, unsigned char);
	
	unsigned char createValue(Bit pBitA, Bit pBitB = NoBit, Bit pBitC = NoBit, Bit pBitD = NoBit, Bit pBitE = NoBit, Bit pBitF = NoBit, Bit pBitG = NoBit, Bit pBitH = NoBit);

	virtual ~GestionMCP23x17();
	
protected:
	BANK bank;
	virtual unsigned char read(Registre) = 0;
	virtual void write(Registre, unsigned char) = 0;
	Registre getRegistre(TypeRegistre, Port);
};

} /* namespace std */

#endif /* GESTIONMCP23x17_H_ */
