/**************************************************
 *   \file    GestionSPI.cpp
 *   \brief   Classe de gestion de l'interface SPI
 *   \note    Version utilisant la librairie pigpio
 *   \author  Totof (raspberry.pi123@orange.fr)
 *   \version 1.0
 *   \date    22/08/2020
 **************************************************/
 
#include <pigpio.h>
#include <unistd.h>

#include "GestionSPI.h"
#include "Logger.h"

/**
 * \brief   Constructeur. 
 *
 * \details Constructeur vide.
 *
 * \note    La méthode initSpi devra être appelé explicitement pour initialiser l'interface SPI.
 */
GestionSpi::GestionSpi(void) 
{
	Logger::log("DEBUG", "--> ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);
	
	Logger::log("DEBUG", "<-- ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);
}

/**
 * \brief   Constructeur. 
 *
 * \details Constructeur standard.
 *
 * \note    Appel automatiquement la méthode d'initialisation de l'interface SPI.
 *
 * \param   pCanal Le canal SPI utilisé.
 */
GestionSpi::GestionSpi(Channel pCanal) 
{
	Logger::log("DEBUG", "--> ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);
	
	Logger::log("DEBUG", " pCanal = ", false);
	Logger::log("DEBUG", pCanal);	

	initSpi(pCanal, speed_50);

	Logger::log("DEBUG", "<-- ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);
}

/**
 * \brief   Constructeur. 
 *
 * \details Constructeur standard.
 *
 * \note    Appel automatiquement la méthode d'initialisation de l'interface SPI.
 *
 * \param   pCanal Le canal SPI utilisé.
 * \param   pFrequence La fréquence de l'interface SPI
 */
GestionSpi::GestionSpi(Channel pCanal, Frequence pFrequence) 
{
	Logger::log("DEBUG", "--> ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);
	
	Logger::log("DEBUG", " pCanal = ", false);
	Logger::log("DEBUG", pCanal);	
	Logger::log("DEBUG", " pFrequence = ", false);
	Logger::log("DEBUG", pFrequence);	

	initSpi(pCanal, pFrequence);

	Logger::log("DEBUG", "<-- ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);
}

/**
 * \brief   Initialisation. 
 *
 * \note    Doit etre appellé explicitement si constructeur vide appellé.
 *
 * \param   pCanal Le canal SPI utilisé.
 * \param   pFrequence La fréquence de l'interface SPI
 * \return  true si ok, false sinon 
 */
bool GestionSpi::initSpi(Channel pCanal, Frequence pFrequence) 
{
	Logger::log("DEBUG", "--> ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);
	
	Logger::log("DEBUG", " pCanal = ", false);
	Logger::log("DEBUG", pCanal);	
	Logger::log("DEBUG", " pFrequence = ", false);
	Logger::log("DEBUG", pFrequence);	

	gpioInitialise();
	handle = spiOpen(pCanal, pFrequence, 0);
	if(handle >= 0) {
		initialize = true;
	}
	
	Logger::log("DEBUG", " handle = ", false);
	Logger::log("DEBUG", handle);	
	Logger::log("DEBUG", " initialize = ", false);
	Logger::log("DEBUG", initialize);	
	
	Logger::log("DEBUG", "<-- ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);
	
	return initialize;
}

/**
 * \brief   Demande si le SPI est bien initialisé. 
 *
 * \return  true si oui false si non
 */
bool GestionSpi::isInitialize(void) 
{
	Logger::log("DEBUG", "--> ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);
	
	Logger::log("DEBUG", " initialize = ", false);
	Logger::log("DEBUG", initialize);
	
	Logger::log("DEBUG", "<-- ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);
	
	return initialize;
}

/**
 * \brief   Lecture d'un nombre d'octet. 
 *
 * \details Ecrit d'abord la commande puis lit les résultats.
 *
 * \note    Modifie le buffer passé en parametre.
 *
 * \param   pData Le buffer recevant les résultats.
 * \param   pDimension Le nombre d'octet à lire
 * \return  Le nombre d'octet transfere, en cas d'erreur voir http://abyz.me.uk/rpi/pigpio/cif.html#spiXfer
 */
uint16_t GestionSpi::read(char pData[], uint16_t pDimension) 
{
	Logger::log("DEBUG", "--> ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);
	
	Logger::log("DEBUG", " pDimension = ", false);
	Logger::log("DEBUG", pDimension);	
	
	Logger::log("DEBUG", "<-- ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);

	return spiXfer(handle, pData, pData, pDimension);
}

/**
 * \brief   Ecriture d'un nombre d'octet. 
 *
 * \param   pData Le buffer contenant les octets à écrire.
 * \param   pDimension Le nombre d'octet à écrire
 * \return  Le nombre d'octet transferé, en cas d'erreur voir http://abyz.me.uk/rpi/pigpio/cif.html#spiXfer
 */
 uint16_t GestionSpi::write(char pData[], uint16_t pDimension) 
{
	Logger::log("DEBUG", "--> ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);

	Logger::log("DEBUG", " pDimension = ", false);
	Logger::log("DEBUG", pDimension);	
	
	Logger::log("DEBUG", "<-- ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);

	return spiWrite(handle, pData, pDimension);
}

/**
 * \brief   Destructeur. 
 *
 * \details Fermeture de l'interface SPI et termine la librairie PIGPIO
 *
 * \note    Appelé automatiquement à la fin du programme
 */
GestionSpi::~GestionSpi() 
{
	Logger::log("DEBUG", "--> ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);
	
	spiClose(handle);
	gpioTerminate();
	
	Logger::log("DEBUG", "<-- ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);
}

/*! \class GestionSpi "GestionSPI.h"
 *  \brief Class de gestion de l'interface SPI.
 *
 */