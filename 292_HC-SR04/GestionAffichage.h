/*
 * GestionAffichage.h
 *
 *  Created on: 31 juillet 2017
 *      Author: totof
 * Affichage de valeurs sur 4 afficheurs HP5082-7300
 */

#ifndef GESTIONAFFICHAGE_H_
#define GESTIONAFFICHAGE_H_

#include "GestionHP50827300.h"

namespace std {

class GestionAffichage {
public:
	GestionAffichage();
	
	void eteindre(void);
	bool affiche(float valeur, int nbChVirgule);

	virtual ~GestionAffichage();

private:
	GestionHP50827300 afficheur4;
	GestionHP50827300 afficheur3;
	GestionHP50827300 afficheur2;
	GestionHP50827300 afficheur1;
};

} /* namespace std */

#endif /* GESTIONAFFICHAGE_H_ */
