/*
 * GestionPCF8591.h
 *
 * Created on 23/07/2018
 * Author Totof
 * Attention: version tres simplifie de la gestion du circuit PCF8591
 * Une adresse de base a 0x48 et tous les canaux AD en lecture simple
 * Convient pour un module Sunfounder
 *
 */

#ifndef GESTIONPCF8591_H
#define GESTIONPCF8591_H

#include <stdint.h>

#include <wiringPi.h>
#include <pcf8591.h>

enum Canal {	
	Canal0 = 0,	
	Canal1 = 1,
	Canal2 = 2,
	Canal3 = 3	
};

class GestionPCF8591 {
public:
	GestionPCF8591(bool);

	uint8_t read (Canal);
	void write (uint8_t);

	virtual ~GestionPCF8591();
};
#endif