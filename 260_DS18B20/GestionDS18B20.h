/*
 * GestionDS18B20.h
 *
 *  Created on: 18 march 2017
 *      Author: totof
 * Controle des thermometre 1-wire DALLAS DS18B20
 */

#ifndef _GESTION_DS18B20_H_
#define _GESTION_DS18B20_H_

#include <string>
#include "GestionSlave1Wire.h"
#include "MesureDS18B20.h"

namespace std {

class GestionDS18B20 : public GestionSlave1Wire {
    public:
		GestionDS18B20(string);
		
		MesureDS18B20 getMesure();
		
		virtual ~GestionDS18B20();

    private:
		MesureDS18B20 mesure;
		virtual list<string> getData();
		string adresse;
};
}

#endif /* _GESTION_DS18B20_H_ */