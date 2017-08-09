/*
 * GestionSlave1Wire.h
 *
 *  Created on: 18 march 2017
 *      Author: totof
 * Controle des esclaves 1-wire
 */

#ifndef _GESTION_ESCLAVE_1WIRE_
#define _GESTION_ESCLAVE_1WIRE_

#include <string>
#include <list>

namespace std {

class GestionSlave1Wire {
    public:
		GestionSlave1Wire();
		GestionSlave1Wire(string);
		
		string getNom() const;
		unsigned short getFID() const;
		string getSlaveID() const;
		
		virtual ~GestionSlave1Wire();

    protected:
		string nom;
		unsigned short FID;
		string slaveID;
		virtual list<string> getData() = 0;
};
}

#endif /* _GESTION_ESCLAVE_1WIRE_ */