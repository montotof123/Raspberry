/*!
 *   \file    Logger.cpp
 *   \brief   Classe de gestion des log
 *   \author  Totof (raspberry.pi123@orange.fr)
 *   \version 1.0
 *   \date    24/07/2019
 */
 
#include <stdlib.h>

#include "Logger.h"

using namespace std;

/**
 *  \brief   Affichage de debug en fonction de variable d'environnement
 *
 *  \details Si la variable existe, le message est affiché
 *
 *  \note    export DEBUG=debug
 *           Logger::log("DEBUG", "ok");
 *           Logger::log("DEBUG", "ok", false);
 *           unset DEBUG pour arreter
 *
 *  \param   pKey La variable d'environnement a tester
 *  \param   pMessage Le message a afficher
 *  \param   pSautLigne Saut de ligne ou non (oui par defaut)
 */
void Logger::log(string pKey, string pMessage, bool pSautLigne)
{
	log(pKey.c_str(), pMessage.c_str(), pSautLigne);
}

/**
 *  \brief   Affichage de debug en fonction de variable d'environnement
 *
 *  \details Si la variable existe, le message est affiché
 *
 *  \note    export DEBUG=debug
 *           Logger::log("DEBUG", "ok");
 *           Logger::log("DEBUG", "ok", false);
 *           unset DEBUG pour arreter
 *
 *  \param   pKey La variable d'environnement a tester
 *  \param   pValeur Le message a afficher
 *  \param   pSautLigne Saut de ligne ou non (oui par defaut)
 */
void Logger::log(const char* pKey, const char* pMessage, bool pSautLigne)
{
    if(const char* env_p = getenv(pKey)) {
 		printf("%s", pMessage);
		if(pSautLigne) {
			 printf("\n");
		}
	}
}

/**
 *  \brief   Affichage de debug en fonction de variable d'environnement
 *
 *  \details Si la variable existe, le message est affiché
 *
 *  \note    export DEBUG=debug
 *           Logger::log("DEBUG", "ok");
 *           Logger::log("DEBUG", "ok", false);
 *           unset DEBUG pour arreter
 *
 *  \param   pKey La variable d'environnement a tester
 *  \param   pValeur La valeur a afficher
 *  \param   pSautLigne Saut de ligne ou non
 */
void Logger::log(string pKey, float pValeur, bool pSautLigne)
{
	log(pKey.c_str(), pValeur, pSautLigne);
}

/**
 *  \brief   Affichage de debug en fonction de variable d'environnement
 *
 *  \details Si la variable existe, le message est affiché
 *
 *  \note    export DEBUG=debug
 *           Logger::log("DEBUG", "ok");
 *           Logger::log("DEBUG", "ok", false);
 *           unset DEBUG pour arreter
 *
 *  \param   pKey La variable d'environnement a tester
 *  \param   pValeur La valeur a afficher
 *  \param   pSautLigne Saut de ligne ou non
 */
void Logger::log(const char* pKey, float pValeur, bool pSautLigne)
{
	if(const char* env_p = std::getenv(pKey)) {
 		printf("%f", pValeur);
		if(pSautLigne) {
			 printf("\n");
		}
	}
}

/**
 *  \brief   Affichage de debug en fonction de variable d'environnement
 *
 *  \details Si la variable existe, le message est affiché
 *
 *  \note    export DEBUG=debug
 *           Logger::log("DEBUG", "ok");
 *           Logger::log("DEBUG", "ok", false);
 *           unset DEBUG pour arreter
 *
 *  \param   pKey La variable d'environnement a tester
 *  \param   pValeur La valeur a afficher
 *  \param   pSautLigne Saut de ligne ou non
 */
void Logger::log(string pKey, int pValeur, bool pSautLigne)
{
	log(pKey.c_str(), pValeur, pSautLigne);
}

/**
 *  \brief   Affichage de debug en fonction de variable d'environnement
 *
 *  \details Si la variable existe, le message est affiché
 *
 *  \note    export DEBUG=debug
 *           Logger::log("DEBUG", "ok");
 *           Logger::log("DEBUG", "ok", false);
 *           unset DEBUG pour arreter
 *
 *  \param   pKey La variable d'environnement a tester
 *  \param   pValeur La valeur a afficher
 *  \param   pSautLigne Saut de ligne ou non
 */
void Logger::log(const char* pKey, int pValeur, bool pSautLigne)
{
   if(const char* env_p = std::getenv(pKey)) {
		printf("%d", pValeur);
		if(pSautLigne) {
			 printf("\n");
		}
	}
}

/**
 *  \brief   Affichage de debug en fonction de variable d'environnement
 *
 *  \details Si la variable existe, le message est affiché
 *
 *  \note    export DEBUG=debug
 *           Logger::log("DEBUG", "ok");
 *           Logger::log("DEBUG", "ok", false);
 *           unset DEBUG pour arreter
 *
 *  \param   pKey La variable d'environnement a tester
 *  \param   pValeur La valeur a afficher
 *  \param   pSautLigne Saut de ligne ou non
 */
void Logger::log(string pKey, uint32_t pValeur, bool pSautLigne)
{
	logFormat(pKey.c_str(), "%u", pValeur, pSautLigne);
}

/**
 *  \brief   Affichage de debug en fonction de variable d'environnement
 *
 *  \details Si la variable existe, le message est affiché
 *
 *  \note    export DEBUG=debug
 *           Logger::log("DEBUG", "ok");
 *           Logger::log("DEBUG", "ok", false);
 *           unset DEBUG pour arreter
 *
 *  \param   pKey La variable d'environnement a tester
 *  \param   pValeur La valeur a afficher
 *  \param   pSautLigne Saut de ligne ou non
 */
void Logger::log(const char* pKey, uint32_t pValeur, bool pSautLigne)
{
	logFormat(pKey, "%u", pValeur, pSautLigne);
}

/**
 *  \brief   Affichage de debug au format héxadécimal en fonction de variable d'environnement
 *
 *  \details Si la variable existe, le message est affiché
 *
 *  \note    export DEBUG=debug
 *           Logger::logHex("DEBUG", "ok");
 *           Logger::logHex("DEBUG", "ok", false);
 *           unset DEBUG pour arreter
 *
 *  \param   pKey La variable d'environnement a tester
 *  \param   pValeur La valeur a afficher
 *  \param   pSautLigne Saut de ligne ou non
 */
void Logger::logHex(string pKey, uint32_t pValeur, bool pSautLigne)
{
	logFormat(pKey.c_str(), "%#x", pValeur, pSautLigne);
}

/**
 *  \brief   Affichage de debug au format héxadécimal en fonction de variable d'environnement
 *
 *  \details Si la variable existe, le message est affiché
 *
 *  \note    export DEBUG=debug
 *           Logger::logHex("DEBUG", "ok");
 *           Logger::logHex("DEBUG", "ok", false);
 *           unset DEBUG pour arreter
 *
 *  \param   pKey La variable d'environnement a tester
 *  \param   pValeur La valeur a afficher
 *  \param   pSautLigne Saut de ligne ou non
 */
void Logger::logHex(const char* pKey, uint32_t pValeur, bool pSautLigne)
{
	logFormat(pKey, "%#x", pValeur, pSautLigne);
}

/**
 *  \brief   Affichage de debug en fonction de variable d'environnement
 *
 *  \details Si la variable existe, le message est affiché
 *
 *  \note    export DEBUG=debug
 *           Logger::log("DEBUG", "ok");
 *           Logger::log("DEBUG", "ok", false);
 *           unset DEBUG pour arreter
 *
 *  \param   pKey La variable d'environnement a tester
 *  \param   pValeur La valeur a afficher
 *  \param   pSautLigne Saut de ligne ou non
 */
void Logger::log(string pKey, uint16_t pValeur, bool pSautLigne)
{
	logFormat(pKey.c_str(), "%u", (uint32_t)pValeur, pSautLigne);
}

/**
 *  \brief   Affichage de debug en fonction de variable d'environnement
 *
 *  \details Si la variable existe, le message est affiché
 *
 *  \note    export DEBUG=debug
 *           Logger::log("DEBUG", "ok");
 *           Logger::log("DEBUG", "ok", false);
 *           unset DEBUG pour arreter
 *
 *  \param   pKey La variable d'environnement a tester
 *  \param   pValeur La valeur a afficher
 *  \param   pSautLigne Saut de ligne ou non
 */
void Logger::log(const char* pKey, uint16_t pValeur, bool pSautLigne)
{
	logFormat(pKey, "%u", (uint32_t)pValeur, pSautLigne);
}

/**
 *  \brief   Affichage de debug au format héxadécimal en fonction de variable d'environnement
 *
 *  \details Si la variable existe, le message est affiché
 *
 *  \note    export DEBUG=debug
 *           Logger::logHex("DEBUG", "ok");
 *           Logger::logHex("DEBUG", "ok", false);
 *           unset DEBUG pour arreter
 *
 *  \param   pKey La variable d'environnement a tester
 *  \param   pValeur La valeur a afficher
 *  \param   pSautLigne Saut de ligne ou non
 */
void Logger::logHex(string pKey, uint16_t pValeur, bool pSautLigne)
{
	logFormat(pKey.c_str(), "%#x", (uint32_t)pValeur, pSautLigne);
}

/**
 *  \brief   Affichage de debug au format héxadécimal en fonction de variable d'environnement
 *
 *  \details Si la variable existe, le message est affiché
 *
 *  \note    export DEBUG=debug
 *           Logger::logHex("DEBUG", "ok");
 *           Logger::logHex("DEBUG", "ok", false);
 *           unset DEBUG pour arreter
 *
 *  \param   pKey La variable d'environnement a tester
 *  \param   pValeur La valeur a afficher
 *  \param   pSautLigne Saut de ligne ou non
 */
void Logger::logHex(const char* pKey, uint16_t pValeur, bool pSautLigne)
{
	logFormat(pKey, "%#x",  (uint32_t)pValeur, pSautLigne);
}

/**
 *  \brief   Affichage de debug en fonction de variable d'environnement
 *
 *  \details Si la variable existe, le message est affiché
 *
 *  \note    export DEBUG=debug
 *           Logger::log("DEBUG", "ok");
 *           Logger::log("DEBUG", "ok", false);
 *           unset DEBUG pour arreter
 *
 *  \param   pKey La variable d'environnement a tester
 *  \param   pValeur La valeur a afficher
 *  \param   pSautLigne Saut de ligne ou non
 */
void Logger::log(string pKey, uint8_t pValeur, bool pSautLigne)
{
	logFormat(pKey.c_str(), "%u", (uint32_t)pValeur, pSautLigne);
}

/**
 *  \brief   Affichage de debug en fonction de variable d'environnement
 *
 *  \details Si la variable existe, le message est affiché
 *
 *  \note    export DEBUG=debug
 *           Logger::log("DEBUG", "ok");
 *           Logger::log("DEBUG", "ok", false);
 *           unset DEBUG pour arreter
 *
 *  \param   pKey La variable d'environnement a tester
 *  \param   pValeur La valeur a afficher
 *  \param   pSautLigne Saut de ligne ou non
 */
void Logger::log(const char* pKey, uint8_t pValeur, bool pSautLigne)
{
	logFormat(pKey, "%u", (uint32_t)pValeur, pSautLigne);
}

/**
 *  \brief   Affichage de debug au format héxadécimal en fonction de variable d'environnement
 *
 *  \details Si la variable existe, le message est affiché
 *
 *  \note    export DEBUG=debug
 *           Logger::logHex("DEBUG", "ok");
 *           Logger::logHex("DEBUG", "ok", false);
 *           unset DEBUG pour arreter
 *
 *  \param   pKey La variable d'environnement a tester
 *  \param   pValeur La valeur a afficher
 *  \param   pSautLigne Saut de ligne ou non
 */
void Logger::logHex(string pKey, uint8_t pValeur, bool pSautLigne)
{
	logFormat(pKey.c_str(), "%#x", (uint32_t)pValeur, pSautLigne);
}

/**
 *  \brief   Affichage de debug au format héxadécimal en fonction de variable d'environnement
 *
 *  \details Si la variable existe, le message est affiché
 *
 *  \note    export DEBUG=debug
 *           Logger::logHex("DEBUG", "ok");
 *           Logger::logHex("DEBUG", "ok", false);
 *           unset DEBUG pour arreter
 *
 *  \param   pKey La variable d'environnement a tester
 *  \param   pValeur La valeur a afficher
 *  \param   pSautLigne Saut de ligne ou non
 */
void Logger::logHex(const char* pKey, uint8_t pValeur, bool pSautLigne)
{
	logFormat(pKey, "%#x",  (uint32_t)pValeur, pSautLigne);
}

/**
 *  \brief   Affichage de debug en fonction de variable d'environnement
 *
 *  \details Si la variable existe, le message est affiché
 *
 *  \note    Ne pas utiliser, utiliser les méthode qui l'appel
 *
 *  \param   pKey La variable d'environnement a tester
 *  \param   pFormat Le format de l'impression (print)
 *  \param   pValeur La valeur a afficher
 *  \param   pSautLigne Saut de ligne ou non
 */
void Logger::logFormat(const char* pKey, const char* pFormat, uint32_t pValeur, bool pSautLigne)
{
	if(const char* env_p = std::getenv(pKey)) {
		printf(pFormat, pValeur);
		if(pSautLigne) {
			 printf("\n");
		}
	}
}

/**
 *  \brief   Affichage de debug en fonction de variable d'environnement
 *
 *  \details Si la variable existe, le message est affiché
 *
 *  \note    export DEBUG=debug
 *           Logger::log("DEBUG", "ok");
 *           Logger::log("DEBUG", "ok", false);
 *           unset DEBUG pour arreter
 *
 *  \param   pKey La variable d'environnement a tester
 *  \param   pValeur La valeur a afficher
 *  \param   pSautLigne Saut de ligne ou non
 */
void Logger::log(string pKey, bool pValeur, bool pSautLigne)
{
	log(pKey.c_str(), pValeur, pSautLigne);
}

/**
 *  \brief   Affichage de debug en fonction de variable d'environnement
 *
 *  \details Si la variable existe, le message est affiché
 *
 *  \note    export DEBUG=debug
 *           Logger::log("DEBUG", "ok");
 *           Logger::log("DEBUG", "ok", false);
 *           unset DEBUG pour arreter
 *
 *  \param   pKey La variable d'environnement a tester
 *  \param   pValeur La valeur a afficher
 *  \param   pSautLigne Saut de ligne ou non
 */
void Logger::log(const char* pKey, bool pValeur, bool pSautLigne)
{
	if(const char* env_p = std::getenv(pKey)) {
		printf("%s", pValeur ? "true" : "false");
		if(pSautLigne) {
			 printf("\n");
		}
	}
}

/**
 *  \brief   Arret en fonction de variable d'environnement
 *
 *  \details Si la variable existe, le message est affiché
 *
 *  \note    export STOP=stop
 *           Logger::stop("STOP");
 *           unset STOP pour arreter
 *
 *  \param   pKey La variable d'environnement a tester
 */
void Logger::stop(string pKey)
{
	stop(pKey.c_str());
}

/**
 *  \brief   Arret en fonction de variable d'environnement
 *
 *  \details Si la variable existe, le message est affiché
 *
 *  \note    export STOP=stop
 *           Logger::stop("STOP");
 *           unset STOP pour arreter
 *
 *  \param   pKey La variable d'environnement a tester
 */
void Logger::stop(const char* pKey)
{
	char c;
    if(const char* env_p = std::getenv(pKey)) {
		printf("%s", "Mise en pause, appuyez sur Entrée pour la suite...");
		c = getchar();
	}
}

/*! \class Logger 
 *  \brief Class de gestion des logs.
 *  \note  Toutes les méthodes sont static
 *
 */