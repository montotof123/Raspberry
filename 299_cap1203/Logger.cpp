/*
 * Logger.cpp
 *
 * Created on 24/07/2019
 * Author Totof
 *
 */
 
#include <stdlib.h>

#include "Logger.h"

using namespace std;

// **********************************************************
// Affichage de debug en fonction de variable d'environnement
// Si la variable existe, le message est affiché
// ex: export DEBUG=debug
//     Logger::log("DEBUG", "ok");
//     Logger::log("DEBUG", "ok", false);
//     unset DEBUG pour arreter
// @Param la variable d'environnement a tester
// @Param le message a afficher
// @Param saut de ligne ou non (oui par defaut)
// **********************************************************
void Logger::log(string pKey, string pMessage, bool pSautLigne)
{
	log(pKey.c_str(), pMessage.c_str(), pSautLigne);
}

// **********************************************************
// Affichage de debug en fonction de variable d'environnement
// Si la variable existe, le message est affiché
// ex: export DEBUG=debug
//     Logger::log("DEBUG", "ok");
//     Logger::log("DEBUG", "ok", false);
//     unset DEBUG pour arreter
// @Param la variable d'environnement a tester
// @Param le message a afficher
// @Param saut de ligne ou non (oui par defaut)
// **********************************************************
void Logger::log(const char* pKey, const char* pMessage, bool pSautLigne)
{
    if(const char* env_p = getenv(pKey)) {
 		printf("%s", pMessage);
		if(pSautLigne) {
			 printf("\n");
		}
	}
}

// **********************************************************
// Affichage de debug en fonction de variable d'environnement
// Si la variable existe, le message est affiché
// @Param la variable d'environnement a tester
// @Param la valeur a afficher
// @Param saut de ligne ou non
// **********************************************************
void Logger::log(string pKey, float pValeur, bool pSautLigne)
{
	log(pKey.c_str(), pValeur, pSautLigne);
}

// **********************************************************
// Affichage de debug en fonction de variable d'environnement
// Si la variable existe, le message est affiché
// @Param la variable d'environnement a tester
// @Param la valeur a afficher
// @Param saut de ligne ou non
// **********************************************************
void Logger::log(const char* pKey, float pValeur, bool pSautLigne)
{
	if(const char* env_p = std::getenv(pKey)) {
 		printf("%f", pValeur);
		if(pSautLigne) {
			 printf("\n");
		}
	}
}

// **********************************************************
// Affichage de debug en fonction de variable d'environnement
// Si la variable existe, le message est affiché
// @Param la variable d'environnement a tester
// @Param la valeur a afficher
// @Param saut de ligne ou non
// **********************************************************
void Logger::log(string pKey, int pValeur, bool pSautLigne)
{
	log(pKey.c_str(), pValeur, pSautLigne);
}

// **********************************************************
// Affichage de debug en fonction de variable d'environnement
// Si la variable existe, le message est affiché
// @Param la variable d'environnement a tester
// @Param la valeur a afficher
// @Param saut de ligne ou non
// **********************************************************
void Logger::log(const char* pKey, int pValeur, bool pSautLigne)
{
   if(const char* env_p = std::getenv(pKey)) {
		printf("%d", pValeur);
		if(pSautLigne) {
			 printf("\n");
		}
	}
}

// **********************************************************
// Affichage de debug en fonction de variable d'environnement
// Si la variable existe, le message est affiché
// @Param la variable d'environnement a tester
// @Param la valeur a afficher
// @Param saut de ligne ou non
// **********************************************************
void Logger::log(string pKey, uint32_t pValeur, bool pSautLigne)
{
	logFormat(pKey.c_str(), "%u", pValeur, pSautLigne);
}

// **********************************************************
// Affichage de debug en fonction de variable d'environnement
// Si la variable existe, le message est affiché
// @Param la variable d'environnement a tester
// @Param la valeur a afficher
// @Param saut de ligne ou non
// **********************************************************
void Logger::log(const char* pKey, uint32_t pValeur, bool pSautLigne)
{
	logFormat(pKey, "%u", pValeur, pSautLigne);
}
// **********************************************************
// Affichage de debug en fonction de variable d'environnement
// Si la variable existe, le message est affiché
// @Param la variable d'environnement a tester
// @Param la valeur a afficher
// @Param saut de ligne ou non
// **********************************************************
void Logger::logHex(string pKey, uint32_t pValeur, bool pSautLigne)
{
	logFormat(pKey.c_str(), "%#x", pValeur, pSautLigne);
}

// **********************************************************
// Affichage de debug en fonction de variable d'environnement
// Si la variable existe, le message est affiché
// @Param la variable d'environnement a tester
// @Param la valeur a afficher
// @Param saut de ligne ou non
// **********************************************************
void Logger::logHex(const char* pKey, uint32_t pValeur, bool pSautLigne)
{
	logFormat(pKey, "%#x", pValeur, pSautLigne);
}

// **********************************************************
// Affichage de debug en fonction de variable d'environnement
// Si la variable existe, le message est affiché
// @Param la variable d'environnement a tester
// @Param la valeur a afficher
// @Param saut de ligne ou non
// **********************************************************
void Logger::log(string pKey, uint16_t pValeur, bool pSautLigne)
{
	logFormat(pKey.c_str(), "%u", (uint32_t)pValeur, pSautLigne);
}

// **********************************************************
// Affichage de debug en fonction de variable d'environnement
// Si la variable existe, le message est affiché
// @Param la variable d'environnement a tester
// @Param la valeur a afficher
// @Param saut de ligne ou non
// **********************************************************
void Logger::log(const char* pKey, uint16_t pValeur, bool pSautLigne)
{
	logFormat(pKey, "%u", (uint32_t)pValeur, pSautLigne);
}

// **********************************************************
// Affichage de debug en fonction de variable d'environnement
// Si la variable existe, le message est affiché
// @Param la variable d'environnement a tester
// @Param la valeur a afficher
// @Param saut de ligne ou non
// **********************************************************
void Logger::logHex(string pKey, uint16_t pValeur, bool pSautLigne)
{
	logFormat(pKey.c_str(), "%#x", (uint32_t)pValeur, pSautLigne);
}

// **********************************************************
// Affichage de debug en fonction de variable d'environnement
// Si la variable existe, le message est affiché
// @Param la variable d'environnement a tester
// @Param la valeur a afficher
// @Param saut de ligne ou non
// **********************************************************
void Logger::logHex(const char* pKey, uint16_t pValeur, bool pSautLigne)
{
	logFormat(pKey, "%#x",  (uint32_t)pValeur, pSautLigne);
}

// **********************************************************
// Affichage de debug en fonction de variable d'environnement
// Si la variable existe, le message est affiché
// @Param la variable d'environnement a tester
// @Param la valeur a afficher
// @Param saut de ligne ou non
// **********************************************************
void Logger::log(string pKey, uint8_t pValeur, bool pSautLigne)
{
	logFormat(pKey.c_str(), "%u", (uint32_t)pValeur, pSautLigne);
}

// **********************************************************
// Affichage de debug en fonction de variable d'environnement
// Si la variable existe, le message est affiché
// @Param la variable d'environnement a tester
// @Param la valeur a afficher
// @Param saut de ligne ou non
// **********************************************************
void Logger::log(const char* pKey, uint8_t pValeur, bool pSautLigne)
{
	logFormat(pKey, "%u", (uint32_t)pValeur, pSautLigne);
}

// **********************************************************
// Affichage de debug en fonction de variable d'environnement
// Si la variable existe, le message est affiché
// @Param la variable d'environnement a tester
// @Param la valeur a afficher
// @Param saut de ligne ou non
// **********************************************************
void Logger::logHex(string pKey, uint8_t pValeur, bool pSautLigne)
{
	logFormat(pKey.c_str(), "%#x", (uint32_t)pValeur, pSautLigne);
}

// **********************************************************
// Affichage de debug en fonction de variable d'environnement
// Si la variable existe, le message est affiché
// @Param la variable d'environnement a tester
// @Param la valeur a afficher
// @Param saut de ligne ou non
// **********************************************************
void Logger::logHex(const char* pKey, uint8_t pValeur, bool pSautLigne)
{
	logFormat(pKey, "%#x",  (uint32_t)pValeur, pSautLigne);
}

// **********************************************************
// Affichage de debug en fonction de variable d'environnement
// Si la variable existe, le message est affiché
// @Param la variable d'environnement a tester
// @Param la valeur a afficher
// @Param saut de ligne ou non
// **********************************************************
void Logger::logFormat(const char* pKey, const char* pFormat, uint32_t pValeur, bool pSautLigne)
{
	if(const char* env_p = std::getenv(pKey)) {
		printf(pFormat, pValeur);
		if(pSautLigne) {
			 printf("\n");
		}
	}
}

// **********************************************************
// Affichage de debug en fonction de variable d'environnement
// Si la variable existe, le message est affiché
// @Param la variable d'environnement a tester
// @Param la valeur a afficher
// @Param saut de ligne ou non
// **********************************************************
void Logger::log(string pKey, bool pValeur, bool pSautLigne)
{
	log(pKey.c_str(), pValeur, pSautLigne);
}

// **********************************************************
// Affichage de debug en fonction de variable d'environnement
// Si la variable existe, le message est affiché
// @Param la variable d'environnement a tester
// @Param la valeur a afficher
// @Param saut de ligne ou non
// **********************************************************
void Logger::log(const char* pKey, bool pValeur, bool pSautLigne)
{
	if(const char* env_p = std::getenv(pKey)) {
		printf("%s", pValeur ? "true" : "false");
		if(pSautLigne) {
			 printf("\n");
		}
	}
}

// *********************************************
// Arret en fonction de variable d'environnement
// Si la variable existe, le message est affiché
// ex: export STOP=stop
//     Logger::stop("STOP");
//     unset STOP pour arreter
// @Param la variable d'environnement a tester
// *********************************************
void Logger::stop(string pKey)
{
	stop(pKey.c_str());
}

// *********************************************
// Arret en fonction de variable d'environnement
// Si la variable existe, le message est affiché
// ex: export STOP=stop
//     Logger::stop("STOP");
//     unset STOP pour arreter
// @Param la variable d'environnement a tester
// *********************************************
void Logger::stop(const char* pKey)
{
	char c;
    if(const char* env_p = std::getenv(pKey)) {
		printf("%s", "Mise en pause, appuyez sur Entrée pour la suite...");
		c = getchar();
	}
}

