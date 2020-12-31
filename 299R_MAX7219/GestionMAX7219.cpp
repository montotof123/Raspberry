/*********************************************
 *   \file    GestionMAX7219.cpp
 *   \brief   Classe de gestion du MAX7219.
 *   \author  Totof (raspberry.pi123@orange.fr)
 *   \version 1.0
 *   \date    28/12/2020
 ********************************************/

#include "GestionMAX7219.h"
#include "GestionMAX7219Reg.h"
#include "Logger.h"

/**
 * \brief   Constructeur vide. 
 *
 * \details Constructeur vide pour instancier la classe.
 *
 * \note    Si ce constructeur est utilisé,
 *          la méthode d'initialisation (initMAX7219) doit être appelé explicitement.
 */
GestionMAX7219::GestionMAX7219(void)
{
	Logger::log("DEBUG", "--> ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);
	Logger::log("DEBUG", "<-- ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);
	Logger::log("DEBUG", "");
}

/**
 * \brief   Constructeur. 
 *
 * \details Constructeur standard.
 *
 * \note    Appel automatiquement la méthode d'initialisation.
 *
 * \param   pCanal Le canal SPI.
 */
GestionMAX7219::GestionMAX7219(Channel pCanal)
{
	Logger::log("DEBUG", "--> ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);
	Logger::log("DEBUG", " canal = ", false);
	Logger::log("DEBUG", pCanal);	

	initMAX7219(pCanal);

	Logger::log("DEBUG", "<-- ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);
	Logger::log("DEBUG", "");
}

/**
 * \brief   Initialisation. 
 *
 * \details Initialisation du bus SPI.
 *
 * \note    Doit être appelé explicitement si le constructeur vide a été utilisé.
 *
 * \param   pCanal Le canal SPI.
 */
bool GestionMAX7219::initMAX7219(Channel pCanal)
{
	Logger::log("DEBUG", "--> ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);
	Logger::log("DEBUG", " canal = ", false);
	Logger::log("DEBUG", pCanal);	
	
	Logger::log("DEBUG", "<-- ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);
	Logger::log("DEBUG", "");
	
	return initSpi(pCanal, speed_33);
}

/**
 * \brief   Initialisation. 
 *
 * \details Initialisation du bus SPI sur le canal 0.
 *
 * \note    Doit être appelé par une classe qui étendrait cette classe, car l'accès à la classe SPI ne sera pas possible.
 */
bool GestionMAX7219::initMAX7219C0(void)
{
	Logger::log("DEBUG", "--> ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);
	
	Logger::log("DEBUG", "<-- ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);
	Logger::log("DEBUG", "");
	
	return initSpi(Channel::channel_0, speed_33);
}

/**
 * \brief   Initialisation. 
 *
 * \details Initialisation du bus SPI sur le canal 1.
 *
 * \note    Doit être appelé par une classe qui étendrait cette classe, car l'accès à la classe SPI ne sera pas possible.
 */
 bool GestionMAX7219::initMAX7219C1(void)
{
	Logger::log("DEBUG", "--> ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);
	
	Logger::log("DEBUG", "<-- ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);
	Logger::log("DEBUG", "");
	
	return initSpi(Channel::channel_1, speed_33);
}

/**
 * \brief   Pas d'opération sur le MAX7219. 
 *
 * \note    Si des MAX7219 sont chainé, cela permet de pousser la précédente commande au circuit suivant.
 */
void GestionMAX7219::noOp(void)
{
	write8(MAX7219_NO_OP, 0x00);
}

/**
 * \brief   Envoie 4 fois la commande pas d'opération sur le MAX7219. 
 *
 * \note    Si des MAX7219 sont chainés, cela permet de pousser la précédente commande aux circuits suivants.
 */
void GestionMAX7219::noOp4(void)
{
	write32(MAX7219_NO_OP, 0x00, 0x00, 0x00, 0x00);
}

/**
 * \brief   Envoie un octet sur le premier digit ou la première ligne d'une matrice. 
 *
 * \param   pValue La valeur à afficher.
 */
void GestionMAX7219::setDigit0(char pValue)
{
	write8(MAX7219_DIGIT0, pValue);
}

/**
 * \brief   Envoie 4 valeurs sur le premier digit ou la première ligne d'une matrice. 
 *
 * \note    Si des MAX7219 sont chainés, cela permet de pousser les valeurs aux circuits suivants.
 *
 * \param   pValue0 la première valeur à afficher.
 * \param   pValue1 la deuxième valeur à afficher.
 * \param   pValue2 la troisième valeur à afficher.
 * \param   pValue3 la quatrième valeur à afficher.
 */
void GestionMAX7219::setDigit0(char pValue0, char pValue1, char pValue2, char pValue3)
{
	write32(MAX7219_DIGIT0, pValue0, pValue1, pValue2, pValue3);
}

/**
 * \brief   Envoie un octet sur le deuxième digit ou la deuxième ligne d'une matrice. 
 *
 * \param   pValue La valeur à afficher.
 */
void GestionMAX7219::setDigit1(char pValue)
{
	write8(MAX7219_DIGIT1, pValue);
}

/**
 * \brief   Envoie 4 valeurs sur le deuxième digit ou la deuxième ligne d'une matrice. 
 *
 * \note    Si des MAX7219 sont chainés, cela permet de pousser les valeurs aux circuits suivants.
 *
 * \param   pValue0 la première valeur à afficher.
 * \param   pValue1 la deuxième valeur à afficher.
 * \param   pValue2 la troisième valeur à afficher.
 * \param   pValue3 la quatrième valeur à afficher.
 */
 void GestionMAX7219::setDigit1(char pValue0, char pValue1, char pValue2, char pValue3)
{
	write32(MAX7219_DIGIT1, pValue0, pValue1, pValue2, pValue3);
}

/**
 * \brief   Envoie un octet sur le troisième digit ou la troisième ligne d'une matrice. 
 *
 * \param   pValue La valeur à afficher.
 */
void GestionMAX7219::setDigit2(char pValue)
{
	write8(MAX7219_DIGIT2, pValue);
}

/**
 * \brief   Envoie 4 valeurs sur le troisième digit ou la troisième ligne d'une matrice. 
 *
 * \note    Si des MAX7219 sont chainés, cela permet de pousser les valeurs aux circuits suivants.
 *
 * \param   pValue0 la première valeur à afficher.
 * \param   pValue1 la deuxième valeur à afficher.
 * \param   pValue2 la troisième valeur à afficher.
 * \param   pValue3 la quatrième valeur à afficher.
 */
 void GestionMAX7219::setDigit2(char pValue0, char pValue1, char pValue2, char pValue3)
{
	write32(MAX7219_DIGIT2, pValue0, pValue1, pValue2, pValue3);
}

/**
 * \brief   Envoie un octet sur le quatrième digit ou la quatrième ligne d'une matrice. 
 *
 * \param   pValue La valeur à afficher.
 */
void GestionMAX7219::setDigit3(char pValue)
{
	write8(MAX7219_DIGIT3, pValue);
}

/**
 * \brief   Envoie 4 valeurs sur le quatrième digit ou la quatrième ligne d'une matrice. 
 *
 * \note    Si des MAX7219 sont chainés, cela permet de pousser les valeurs aux circuits suivants.
 *
 * \param   pValue0 la première valeur à afficher.
 * \param   pValue1 la deuxième valeur à afficher.
 * \param   pValue2 la troisième valeur à afficher.
 * \param   pValue3 la quatrième valeur à afficher.
 */
void GestionMAX7219::setDigit3(char pValue0, char pValue1, char pValue2, char pValue3)
{
	write32(MAX7219_DIGIT3, pValue0, pValue1, pValue2, pValue3);
}

/**
 * \brief   Envoie un octet sur le cinquième digit ou la cinquième ligne d'une matrice. 
 *
 * \param   pValue La valeur à afficher.
 */
void GestionMAX7219::setDigit4(char pValue)
{
	write8(MAX7219_DIGIT4, pValue);
}

/**
 * \brief   Envoie 4 valeurs sur le cinquième digit ou la cinquième ligne d'une matrice. 
 *
 * \note    Si des MAX7219 sont chainés, cela permet de pousser les valeurs aux circuits suivants.
 *
 * \param   pValue0 la première valeur à afficher.
 * \param   pValue1 la deuxième valeur à afficher.
 * \param   pValue2 la troisième valeur à afficher.
 * \param   pValue3 la quatrième valeur à afficher.
 */
void GestionMAX7219::setDigit4(char pValue0, char pValue1, char pValue2, char pValue3)
{
	write32(MAX7219_DIGIT4, pValue0, pValue1, pValue2, pValue3);
}

/**
 * \brief   Envoie un octet sur le sixième digit ou la sixième ligne d'une matrice. 
 *
 * \param   pValue La valeur à afficher.
 */
void GestionMAX7219::setDigit5(char pValue)
{
	write8(MAX7219_DIGIT5, pValue);
}

/**
 * \brief   Envoie 4 valeurs sur le sixième digit ou la sixième ligne d'une matrice. 
 *
 * \note    Si des MAX7219 sont chainés, cela permet de pousser les valeurs aux circuits suivants.
 *
 * \param   pValue0 la première valeur à afficher.
 * \param   pValue1 la deuxième valeur à afficher.
 * \param   pValue2 la troisième valeur à afficher.
 * \param   pValue3 la quatrième valeur à afficher.
 */
void GestionMAX7219::setDigit5(char pValue0, char pValue1, char pValue2, char pValue3)
{
	write32(MAX7219_DIGIT5, pValue0, pValue1, pValue2, pValue3);
}

/**
 * \brief   Envoie un octet sur le septième digit ou la septième ligne d'une matrice. 
 *
 * \param   pValue La valeur à afficher.
 */
void GestionMAX7219::setDigit6(char pValue)
{
	write8(MAX7219_DIGIT6, pValue);
}

/**
 * \brief   Envoie 4 valeurs sur le septième digit ou la septième ligne d'une matrice. 
 *
 * \note    Si des MAX7219 sont chainés, cela permet de pousser les valeurs aux circuits suivants.
 *
 * \param   pValue0 la première valeur à afficher.
 * \param   pValue1 la deuxième valeur à afficher.
 * \param   pValue2 la troisième valeur à afficher.
 * \param   pValue3 la quatrième valeur à afficher.
 */
void GestionMAX7219::setDigit6(char pValue0, char pValue1, char pValue2, char pValue3)
{
	write32(MAX7219_DIGIT6, pValue0, pValue1, pValue2, pValue3);
}

/**
 * \brief   Envoie un octet sur le huitième digit ou la huitième ligne d'une matrice. 
 *
 * \param   pValue La valeur à afficher.
 */
void GestionMAX7219::setDigit7(char pValue)
{
	write8(MAX7219_DIGIT7, pValue);
}

/**
 * \brief   Envoie 4 valeurs sur le huitième digit ou la huitième ligne d'une matrice. 
 *
 * \note    Si des MAX7219 sont chainés, cela permet de pousser les valeurs aux circuits suivants.
 *
 * \param   pValue0 la première valeur à afficher.
 * \param   pValue1 la deuxième valeur à afficher.
 * \param   pValue2 la troisième valeur à afficher.
 * \param   pValue3 la quatrième valeur à afficher.
 */
void GestionMAX7219::setDigit7(char pValue0, char pValue1, char pValue2, char pValue3)
{
	write32(MAX7219_DIGIT7, pValue0, pValue1, pValue2, pValue3);
}

/**
 * \brief   Régle l'intensité lumineuse. 
 *
 * \param   pValue La valeur de l'intensité.
 */
void GestionMAX7219::setIntensity(char pValue)
{
	write8(MAX7219_INTENSITY, pValue);
}

/**
 * \brief   Envoie 4 intensités lumineuse. 
 *
 * \note    Si des MAX7219 sont chainés, cela permet de pousser les valeurs aux circuits suivants.
 *
 * \param   la première valeur d'intensité.
 * \param   la deuxième valeur d'intensité.
 * \param   la troisième valeur d'intensité.
 * \param   la quatrième valeur d'intensité.
 */
void GestionMAX7219::setIntensity(char pValue0, char pValue1, char pValue2, char pValue3)
{
	write32(MAX7219_INTENSITY, pValue0, pValue1, pValue2, pValue3);
}

/**
 * \brief   Passe le circuit en mode test. 
 */
void GestionMAX7219::test(void)
{
	write8(MAX7219_DISPLAY_TEST, 0x01);
}

/**
 * \brief   Sort le circuit du mode test. 
 */
void GestionMAX7219::noTest(void)
{
	write8(MAX7219_DISPLAY_TEST, 0x00);
}

/**
 * \brief   Passe le circuit en mode d'affichage avec décodage de caractère (liste de caractère dans le datasheet). 
 */
void GestionMAX7219::decode(void)
{
	write8(MAX7219_DECODE_MODE, 0x07);
}

/**
 * \brief   Passe le circuit en mode d'affichage sans décodage de caractère. 
 */
void GestionMAX7219::noDecode(void)
{
	write8(MAX7219_DECODE_MODE, 0x00);
}

/**
 * \brief   Passe le circuit en mode économie d'énergie sans affichage. 
 */
void GestionMAX7219::shutdown(void)
{
	write8(MAX7219_SHUTDOWN, 0x00);
}

/**
 * \brief   Passe le circuit en mode de fonctionnement normal. 
 */
 void GestionMAX7219::run(void)
{
	write8(MAX7219_SHUTDOWN, 0x01);
}

/**
 * \brief   Le circuit ne gère qu'un afficheur ou une ligne de la matrice. 
 */
void GestionMAX7219::scanLimit1(void)
{
	write8(MAX7219_SCAN_LIMIT, 0x00);
}

/**
 * \brief   Le circuit ne gère que deux afficheurs ou deux lignes de la matrice. 
 */
void GestionMAX7219::scanLimit2(void)
{
	write8(MAX7219_SCAN_LIMIT, 0x01);
}

/**
 * \brief   Le circuit ne gère que trois afficheurs ou trois lignes de la matrice. 
 */
void GestionMAX7219::scanLimit3(void)
{
	write8(MAX7219_SCAN_LIMIT, 0x02);
}

/**
 * \brief   Le circuit ne gère que quatre afficheurs ou quatre lignes de la matrice. 
 */
void GestionMAX7219::scanLimit4(void)
{
	write8(MAX7219_SCAN_LIMIT, 0x03);
}

/**
 * \brief   Le circuit ne gère que cinq afficheurs ou cinq lignes de la matrice. 
 */
void GestionMAX7219::scanLimit5(void)
{
	write8(MAX7219_SCAN_LIMIT, 0x04);
}

/**
 * \brief   Le circuit ne gère que six afficheurs ou six lignes de la matrice. 
 */
void GestionMAX7219::scanLimit6(void)
{
	write8(MAX7219_SCAN_LIMIT, 0x05);
}

/**
 * \brief   Le circuit ne gère que sept afficheurs ou sept lignes de la matrice. 
 */
void GestionMAX7219::scanLimit7(void)
{
	write8(MAX7219_SCAN_LIMIT, 0x06);
}

/**
 * \brief   Le circuit gère les huit afficheurs ou huit lignes de la matrice. 
 */
void GestionMAX7219::scanLimit8(void)
{
	write8(MAX7219_SCAN_LIMIT, 0x07);
}

/**
 * \brief  Ecrit une valeur dans un registre
 * \param  pRegistre Le registre
 * \param  pValue La valeur
 * \return Le nombre de valeurs ecrites
 */
uint8_t GestionMAX7219::write8(char pRegistre, char pValue)
{
	Logger::log("DEBUG", "--> ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);

	Logger::log("DEBUG", " pRegistre = ", false);
	Logger::logHex("DEBUG", (uint8_t)pRegistre);	
	Logger::log("DEBUG", " pValue = ", false);
	Logger::logHex("DEBUG", (uint8_t)pValue);	

	spiData8[0] = pRegistre;
	spiData8[1] = pValue;
	
	Logger::log("DEBUG", " spiData8[0] = ", false);
	Logger::logHex("DEBUG", (uint8_t)spiData8[0]);	
	Logger::log("DEBUG", " spiData8[1] = ", false);
	Logger::logHex("DEBUG", (uint8_t)spiData8[1]);	

	Logger::log("DEBUG", "<-- ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);
	Logger::log("DEBUG", "");
	
	return write(spiData8, sizeof(spiData8));
}

/**
 * \brief  Ecrit quatre valeurs dans un registre
 * \param  pRegistre Le registre
 * \param  pValue0 Première valeur
 * \param  pValue1 Deuxième valeur
 * \param  pValue2 Troisième valeur
 * \param  pValue3 Quatrième valeur
 * \note   Si des MAX7219 sont chainés, cela permet de pousser les valeurs aux circuits suivants.
 * \return Le nombre de valeurs ecrites
 */
uint8_t GestionMAX7219::write32(char pRegistre, char pValue0, char pValue1, char pValue2, char pValue3)
{
	Logger::log("DEBUG", "--> ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);

	Logger::log("DEBUG", " pRegistre = ", false);
	Logger::logHex("DEBUG", (uint8_t)pRegistre);	
	Logger::log("DEBUG", " pValue = ", false);
	Logger::logHex("DEBUG", (uint8_t)pValue0);	

	spiData32[0] = pRegistre;
	spiData32[1] = pValue0;
	spiData32[2] = pRegistre;
	spiData32[3] = pValue1;
	spiData32[4] = pRegistre;
	spiData32[5] = pValue2;
	spiData32[6] = pRegistre;
	spiData32[7] = pValue3;
	
	Logger::log("DEBUG", " spiData32[0] = ", false);
	Logger::logHex("DEBUG", (uint8_t)spiData32[0]);	
	Logger::log("DEBUG", " spiData32[1] = ", false);
	Logger::logHex("DEBUG", (uint8_t)spiData32[1]);	
	Logger::log("DEBUG", " spiData32[2] = ", false);
	Logger::logHex("DEBUG", (uint8_t)spiData32[2]);	
	Logger::log("DEBUG", " spiData32[3] = ", false);
	Logger::logHex("DEBUG", (uint8_t)spiData32[3]);	
	Logger::log("DEBUG", " spiData32[4] = ", false);
	Logger::logHex("DEBUG", (uint8_t)spiData32[4]);	
	Logger::log("DEBUG", " spiData32[5] = ", false);
	Logger::logHex("DEBUG", (uint8_t)spiData32[5]);	
	Logger::log("DEBUG", " spiData32[6] = ", false);
	Logger::logHex("DEBUG", (uint8_t)spiData32[6]);	
	Logger::log("DEBUG", " spiData32[7] = ", false);
	Logger::logHex("DEBUG", (uint8_t)spiData32[7]);	

	Logger::log("DEBUG", "<-- ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);
	Logger::log("DEBUG", "");
	
	return write(spiData32, sizeof(spiData32));
}


/**
 * \brief   Destructeur. 
 *
 * \note    Appelé automatiquement à la fin du programme
 */
GestionMAX7219::~GestionMAX7219()
{
	Logger::log("DEBUG", "--> ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);
	Logger::log("DEBUG", "<-- ", false);
	Logger::log("DEBUG", __PRETTY_FUNCTION__);
	Logger::log("DEBUG", "");
};

/*! \class GestionMAX7219 "GestionMAX7219.h"
 *  \brief Class de gestion du MAX7219.
 *
 *  \note https://datasheets.maximintegrated.com/en/ds/MAX7219-MAX7221.pdf
 */