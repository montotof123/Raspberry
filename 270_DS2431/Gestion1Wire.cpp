/*
 * Gestion1Wire.cpp
 *
 *  Created on: 17 march 2017
 *      Author: totof
 * Controle de l'interface 1Wire
 */

#include <fstream>
#include <string>
#include <list>
#include <dirent.h>
#include "Gestion1Wire.h"
#include "GestionDS18B20.h"
#include "GestionDS2431.h"

#define CHEMIN_DEFAUT "/sys/bus/w1/devices"
#define MASTER_NAME_DEFAUT "w1_master_name"

namespace std {

// ********************************************************************
// Constructeur
// Utilise les paramètres par defaut pour le chemin et le nom du master
// ********************************************************************
Gestion1Wire::Gestion1Wire() {
	chemin = CHEMIN_DEFAUT;
	init(CHEMIN_DEFAUT, MASTER_NAME_DEFAUT);
}

// **********************************
// Constructeur
// @param le chemin des peripheriques
// @param le nom prevu du master
// **********************************
Gestion1Wire::Gestion1Wire(string pChemin, string pMasterName) : chemin(pChemin){
	init(pChemin, pMasterName);
}
// ************************************
// Initialisation
// Initialise la liste des peripherique
// Initialise le nom du master
// @param le chemin des peripheriques
// @param le nom prevu du master
// ************************************
void Gestion1Wire::init(string pChemin, string pMasterName) {
	static const string SLASH = "/";
	struct dirent *entry;
	
	// Recupere toutes les entrees du repertoire
	DIR *dirPrimaire = opendir(pChemin.c_str());
	while(entry = readdir(dirPrimaire))
	{
			nomSlaves.push_back(entry->d_name);
	}
	closedir(dirPrimaire);
	
	// Suppression . et ..
	nomSlaves.remove(".");
	nomSlaves.remove("..");
	
	// Va lire chaque repertoire pour trouver le master
	for (string nom : nomSlaves) {
		// Va lire chaque Item du repertoire
		string chemin = pChemin;
		chemin.append(SLASH).append(nom);
		DIR *dirEntree;
		dirEntree = opendir(chemin.c_str());
		list<string> lstItem;
		while(entry = readdir(dirEntree))
		{
				lstItem.push_back(entry->d_name);
		}
		closedir(dirEntree);
		
		// Recherche si ce repertoire contient le pMasterName pour voir si c'est bien le master
		list<string>::iterator itItem;
		for (itItem = lstItem.begin(); itItem!=lstItem.end(); ++itItem) {
			if(*itItem == pMasterName) {
				string nomFichierMaster = pChemin;
				nomFichierMaster.append(SLASH).append(nom).append(SLASH).append(*itItem);
				ifstream fichierMaster(nomFichierMaster.c_str(), ios::in);
				// Si c'est le master on mémorise son nom
				if(fichierMaster) {
					getline(fichierMaster, nomMaster);
					fichierMaster.close();
				}
			}
		}
	}
	
	// Suppression du master de la liste des repertoires afin de ne garder que les slaves
	nomSlaves.remove(nomMaster);
	
	// Creation des esclaves (un nouveau type est a ajouter ici)
	for (string slave : nomSlaves) {
		string typeSlave = slave.substr(0,2);
		int hexTypeSlave;
		sscanf(typeSlave.c_str(), "%x", &hexTypeSlave);
		switch(hexTypeSlave) {
			case 1: break; //01h  liste des familles https://fr.wikipedia.org/wiki/1-Wire
			case 2: break; //02h
			case 4: break; //04h
			case 5: break; //05h
			case 6: break; //06h
			case 8: break; //08h
			case 9: break; //09h
			case 10: break; //0Ah
			case 11: break; //0Bh
			case 12: break; //0Ch
			case 15: break; //0Fh
			case 16: break; //10h
			case 18: break; //12h
			case 20: break; //14h
			case 24: break; //18h
			case 26: break; //1Ah
			case 28: break; //1Ch
			case 29: break; //1Dh
			case 31: break; //1Fh
			case 33: break; //21h
			case 34: break; //22h
			case 35: break; //23h
			case 36: break; //24h
			case 38: break; //26h
			case 39: break; //27h
			case DS18B20: lstSlaves.push_back(new GestionDS18B20(getChemin() + "/" + slave)); break; //28h
			case 41: break; //29h
			case 44: break; //2Ch
			case DS2431: lstSlaves.push_back(new GestionDS2431(getChemin() + "/" + slave)); break; //2Dh
			case 48: break; //30h
			case 51: break; //33h
			case 55: break; //37h
			case 58: break; //3Ah
			case 65: break; //41h
			case 145: break; //91h
		}
	}	
}

// *********************
// Getter nomMaster
// @return nom du master
// *********************
string Gestion1Wire::getNomMaster() const {
	return(nomMaster);
}

// **************************
// Getter nombre d'esclave
// @return le nombre desclave
// **************************
unsigned short Gestion1Wire::getNombreSlaves() const {
	return(nomSlaves.size());
}

// ****************************
// Getter des noms des esclaves
// @return le nom des esclaves
// ****************************
list<string> Gestion1Wire::getNomSlaves() const {
	return(nomSlaves);
}

// **************************************
// Test l'existance d'un peripherique
// @return true si il existe, sinon false
// **************************************
bool Gestion1Wire::isSlaveExist(string pNom) const {
	bool exist = false;
	for(string nom : nomSlaves) {
		if(nom == pNom) {
			exist = true;
		}
	}
	return(exist);
}

// **************************
// Getter chemin
// @return le chemin des data
// **************************
string Gestion1Wire::getChemin() const {
	return(chemin);
}

// **************************
// Getter chemin
// @return le chemin des data
// **************************
list<GestionSlave1Wire*> Gestion1Wire::getLstSlaves() const {
	return(lstSlaves);
}

// *************************
// Destructeur
// *************************
Gestion1Wire::~Gestion1Wire() {
	for(GestionSlave1Wire* ptr : lstSlaves)
    {
        delete ptr;
    }
}

}

