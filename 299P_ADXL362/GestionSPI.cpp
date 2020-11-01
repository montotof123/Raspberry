/*
 * GestionSPI.cpp
 *
 * Created on 22/08/2020
 * Author Totof
 * Utilise la librairie PIGPIO
 *
 */

#include <pigpio.h>
#include <unistd.h>

#include "GestionSPI.h"
#include "Logger.h"

// *****************
// Constructeur vide
// *****************
GestionSpi::GestionSpi(void) {
	Logger::log("DEBUG", "--> ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);
	
	Logger::log("DEBUG", "<-- ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);
}

// ****************
// Constructeur
// @param canal 
// ****************
GestionSpi::GestionSpi(Channel canal) {
	Logger::log("DEBUG", "--> ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);
	
	Logger::log("DEBUG", " canal = ", false);
	Logger::log("DEBUG", canal);	

	initSpi(canal, speed_50);

	Logger::log("DEBUG", "<-- ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);
}

// ****************
// Constructeur
// @param canal 
// @param frequence 
// ****************
GestionSpi::GestionSpi(Channel canal, Frequence frequence) {
	Logger::log("DEBUG", "--> ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);
	
	Logger::log("DEBUG", " canal = ", false);
	Logger::log("DEBUG", canal);	
	Logger::log("DEBUG", " frequence = ", false);
	Logger::log("DEBUG", frequence);	

	initSpi(canal, frequence);

	Logger::log("DEBUG", "<-- ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);
}

// ************************************************************
// Initialisation
// Doit etre appelle explicitement si constructeur vide appelle
// @param adresse du circuit 
// @return true si ok, false sinon 
// ************************************************************
bool GestionSpi::initSpi(Channel canal, Frequence frequence) {
	Logger::log("DEBUG", "--> ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);
	
	Logger::log("DEBUG", " canal = ", false);
	Logger::log("DEBUG", canal);	
	Logger::log("DEBUG", " frequence = ", false);
	Logger::log("DEBUG", frequence);	

	gpioInitialise();
	handle = spiOpen(canal, frequence, 0);
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

// ********************************
// Le SPI est t'il initialise
// @return true si oui false si non
// ********************************
bool GestionSpi::isInitialize(void) {
	Logger::log("DEBUG", "--> ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);
	
	Logger::log("DEBUG", " initialize = ", false);
	Logger::log("DEBUG", initialize);
	
	Logger::log("DEBUG", "<-- ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);
	
	return initialize;
}

// ******************************************************************
// Ecriture d'un nombre d'octet puis lecture
// Modifie le buffer passe en parametre
// @return le nombre d'octet transfere
//         sinon erreur http://abyz.me.uk/rpi/pigpio/cif.html#spiXfer
// ******************************************************************
uint16_t GestionSpi::read(char data[], uint16_t dimension) {
	Logger::log("DEBUG", "--> ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);
	
	Logger::log("DEBUG", " dimension = ", false);
	Logger::log("DEBUG", dimension);	
	
	Logger::log("DEBUG", "<-- ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);

	return spiXfer(handle, data, data, dimension);
}

// *******************************************************************
// Ecriture d'un nombre d'octet 
// @return le nombre d'octet transfere
//         sinon erreur http://abyz.me.uk/rpi/pigpio/cif.html#spiWrite
// *******************************************************************
uint16_t GestionSpi::write(char data[], uint16_t dimension) {
	Logger::log("DEBUG", "--> ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);

	Logger::log("DEBUG", " dimension = ", false);
	Logger::log("DEBUG", dimension);	
	
	Logger::log("DEBUG", "<-- ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);

	return spiWrite(handle, data, dimension);
}

// ***********
// Destructeur
// ***********
GestionSpi::~GestionSpi() {
	Logger::log("DEBUG", "--> ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);
	
	spiClose(handle);
	gpioTerminate();
	
	Logger::log("DEBUG", "<-- ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);
}

