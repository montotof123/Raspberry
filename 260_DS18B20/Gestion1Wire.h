/*
 * Gestion1Wire.h
 *
 *  Created on: 17 march 2017
 *      Author: totof
 * Controle de l'interface 1Wire
 */

#ifndef _GESTION_1WIRE_H_
#define _GESTION_1WIRE_H_

#include <string>
#include <list>
#include "GestionSlave1Wire.h"

namespace std {

class Gestion1Wire {
    public:
		Gestion1Wire(string, string);
		Gestion1Wire();
		
		string getNomMaster() const;
		unsigned short getNombreSlaves() const;
		list<string> getNomSlaves() const;
		bool isSlaveExist(string) const;
		list<GestionSlave1Wire*> getLstSlaves() const;
		
		virtual ~Gestion1Wire();

    private:
		void init(string, string);
		string nomMaster;
		list<string> nomSlaves;
		string getChemin() const;
		string chemin;
		list<GestionSlave1Wire*> lstSlaves;
};
}

#endif /* _GESTION_1WIRE_H_ */