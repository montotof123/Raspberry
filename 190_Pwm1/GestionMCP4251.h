/*
 * GestionMCP4251.h
 *
 *  Created on: 15 octobre 2016
 *      Author: totof
 * Controle un MCP4251 avec la librairie wiringPi sur Raspberry Pi
 */

#ifndef GESTIONMCP4251_H_
#define GESTIONMCP4251_H_

#include "GestionSPI.h"

enum Pot
{
  pot_0 = 0x00,
  pot_1 = 0x10
};

namespace std {

// Classe de gestion du MCP4251
class GestionMCP4251 {
public:
	GestionMCP4251(Channel);
	GestionMCP4251(Channel, Frequence);
	bool reset(void);
	bool increment(Pot);
	bool decrement(Pot);
	bool write(Pot, unsigned short);
	unsigned short read(Pot);
	unsigned char isShutdown(void);
	bool connect(Pot);
	bool unConnect(Pot);
	bool isConnect(Pot);
	bool connectShutdown(Pot);
	bool unConnectShutdown(Pot);
	bool isConnectShutdown(Pot);
	unsigned short getMaxValue(void);
	virtual ~GestionMCP4251();

	// Erreur de mesure
	static const unsigned short ERREUR_MESURE = 0xFFFF;
	// Erreur de status
	static const unsigned char ERREUR_STATUS = 0xFF;
	// shutdown
	static const unsigned char SHUTDOWN = 0x01;
	// no shutdown
	static const unsigned char NO_SHUTDOWN = 0x00;

private:
	union spiData{
		unsigned short uSData;
		unsigned char uCData[2];
	};	
	
	Channel channel;
	unsigned short readTCON(void);
	bool writeTCON(unsigned short);
	void swap(spiData &);
	
	// Erreur de commande
	static const unsigned short ERREUR_COMMANDE = 0x0000;
	// Les opération d'increment et de decrement renvoient 1111 1111 si la commande est OK
	static const unsigned char COMMAND_OK = 0xFF;
	// Operation d'increment xxxx 0100
	static const unsigned char INCREMENT = 0x04;
	// Operation de decrement xxxx 1000
	static const unsigned char DECREMENT = 0x08;
	// Valeur maximum du potentiometre
	static const unsigned short MAX_VALUE = 0x0100;
	// Masque de la commande d'écriture 0000 00nn nnnn nnnn
	static const unsigned short WRITE_MASK = 0x03FF;
	// Masque de la commande de lecture 0000 11nn nnnn nnnn
	static const unsigned short READ_MASK = 0x0FFF;
	// Masque du Bit CMDERR (bit D9 du résultat)
	// Masque du Bit CMDERR xxxx xxnx xxxx xxxx (doc)
	static const unsigned short CMDERR_MASK = 0x0200;
	// Masque des resultats de lecture du potentiometre ou des registres
	static const unsigned short RESULT_MASK = 0x01FF;
	// Commande de lecture du registre STATUS
	static const unsigned short STATUS = 0x5B00;
	// Masque de lecture du bit de SHUTDOWN du registre STATUS
	static const unsigned short MASK_SHUTDOWN = 0x0002;
	// Commande de lecture du registre TCON
	static const unsigned short READ_TCON = 0x4C00;
	// Commande d'ecriture du registre TCON
	static const unsigned short WRITE_TCON = 0x4000;
	// Masque du potentiometre 0 du registre TCON
	static const unsigned short MASK_TCON_POT_0 = 0x0007;
	// Masque du potentiometre 1 du registre TCON
	static const unsigned short MASK_TCON_POT_1 = 0x0070;
	// Masque du shutdown du potentiometre 0 du registre TCON
	static const unsigned short MASK_TCON_SHUTDOWN_POT_0 = 0x0008;
	// Masque du shutdown du potentiometre 1 du registre TCON
	static const unsigned short MASK_TCON_SHUTDOWN_POT_1 = 0x0080;
	// Masque inverse du potentiometre 0 du registre TCON pour deselection
	// Enleve egalement l'entet du resultat de la commande READTCON
	// 1111 111n nnnn nnnn -> 0000 000n nnnn n000
	static const unsigned short NOT_MASK_TCON_POT_0 = 0x01F8;
	// Masque inverse du potentiometre 1 du registre TCON pour deselection
	// Enleve egalement l'entet du resultat de la commande READTCON
	// 1111 111n nnnn nnnn -> 0000 000n n000 nnnn
	static const unsigned short NOT_MASK_TCON_POT_1 = 0x018F;
	// Masque inverse du shutdown du potentiometre 0 du registre TCON pour deselection
	// Enleve egalement l'entet du resultat de la commande READTCON
	// 1111 111n nnnn nnnn -> 0000 000n nnnn 0nnn
	static const unsigned short NOT_MASK_TCON_SHUTDOWN_POT_0 = 0x01F7;
	// Masque inverse du shutdown du potentiometre 1 du registre TCON pour deselection
	// Enleve egalement l'entet du resultat de la commande READTCON
	// 1111 111n nnnn nnnn -> 0000 000n 0nnn nnnn
	static const unsigned short NOT_MASK_TCON_SHUTDOWN_POT_1 = 0x017F;
};

} /* namespace std */

#endif /* GESTIONMCP4251_H_ */
