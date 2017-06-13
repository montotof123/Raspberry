/*
 * GestionDS2431.h
 *
 *  Created on: 02 april 2017
 *      Author: totof
 * Controle des eeprom 1-wire DALLAS DS2431
 */

#ifndef _GESTION_DS2431_H_
#define _GESTION_DS2431_H_

#include <string>
#include "GestionSlave1Wire.h"

namespace std {

class GestionDS2431 : public GestionSlave1Wire {
    public:
		GestionDS2431(string);
		
		string getMessage();
		bool setMessage(string);
		
		virtual ~GestionDS2431();

    private:
		virtual list<string> getData();
		string adresse;
};
}

#endif /* _GESTION_DS2431_H_ */