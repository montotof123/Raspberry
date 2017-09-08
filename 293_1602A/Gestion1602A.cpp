/*
 * Gestion1602A.cpp
 *
 *  Created on: 5 may 2017
 *      Author: totof
 * Controle un module BH1750
 */

#define nbRows 2
#define nbColumns 16
#define addr4Bits 4
#define addr8Bits 8
#define nbCharDef 16

#include "Gestion1602A.h"
#include <lcd.h>
#include <stdarg.h>
#include <stdio.h>

namespace std {

// *****************
// Constructeur vide
// *****************
Gestion1602A::Gestion1602A() {
}

// *****************************
// Constructeur adressage 4 bits
// @param rs Pin RS
// @param enable Pin E
// @param d4 Pin D4
// @param d5 Pin D5
// @param d6 Pin D6
// @param d7 Pin D7
// *****************************
Gestion1602A::Gestion1602A(PinGPIO rs, PinGPIO enable, PinGPIO d4, PinGPIO d5, PinGPIO d6, PinGPIO d7) {
	init(rs, enable, d4, d5, d6, d7);
}

// *****************************
// Constructeur adressage 8 bits
// @param rs Pin RS
// @param enable Pin E
// @param d0 Pin D0
// @param d1 Pin D1
// @param d2 Pin D2
// @param d3 Pin D3
// @param d4 Pin D4
// @param d5 Pin D5
// @param d6 Pin D6
// @param d7 Pin D7
// *****************************
Gestion1602A::Gestion1602A(PinGPIO rs, PinGPIO enable, PinGPIO d0, PinGPIO d1, PinGPIO d2, PinGPIO d3, PinGPIO d4, PinGPIO d5, PinGPIO d6, PinGPIO d7) {
	init(rs, enable, d0, d1, d2, d3, d4, d5, d6, d7);
}

// **************************
// Initialisation mode 4 bits
// @param rs Pin RS
// @param enable Pin E
// @param d4 Pin D4
// @param d5 Pin D5
// @param d6 Pin D6
// @param d7 Pin D7
// **************************
void Gestion1602A::init(PinGPIO rs, PinGPIO enable, PinGPIO d4, PinGPIO d5, PinGPIO d6, PinGPIO d7) {
	//Initialise LCD
	initOk = true;
    if (handle = lcdInit (nbRows, nbColumns, addr4Bits, rs, enable, d4, d5, d6, d7, 0, 0, 0, 0)){
		initOk = false;
    }
	displayOn();
	clear();
}

// *****************************
// Initialisation mode 8 bits
// @param rs Pin RS
// @param enable Pin E
// @param d0 Pin D0
// @param d1 Pin D1
// @param d2 Pin D2
// @param d3 Pin D3
// @param d4 Pin D4
// @param d5 Pin D5
// @param d6 Pin D6
// @param d7 Pin D7
// *****************************
void Gestion1602A::init(PinGPIO rs, PinGPIO enable, PinGPIO d0, PinGPIO d1, PinGPIO d2, PinGPIO d3, PinGPIO d4, PinGPIO d5, PinGPIO d6, PinGPIO d7) {
	//Initialise LCD
	initOk = true;
    if (handle = lcdInit (nbRows, nbColumns, addr4Bits, rs, enable, d0, d1, d2, d3, d4, d5, d6, d7)){
		initOk = false;
    }
	displayOn();
	clear();
}

// ************************************
// Indique si l'initialisation est ok
// @return bool initialisation ok ou ko
// ************************************
bool Gestion1602A::isInitOk(void) {
	return initOk;
}

// **********************************
// Ramene le curseur en haut a gauche
// **********************************
void Gestion1602A::home(void) {
	lcdHome(handle);
}

// ***************************
// Vide l'ecran de l'afficheur
// ***************************
void Gestion1602A::clear(void) {
	lcdClear(handle);
}

// *******************************************
// Rend les caracteres de l'afficheur visibles
// *******************************************
void Gestion1602A::displayOn(void) {
	display = true;
	lcdDisplay(handle, true);
}

// *********************************************
// Rend les caracteres de l'afficheur invisibles
// *********************************************
void Gestion1602A::displayOff(void) {
	display = false;
	lcdDisplay(handle, false);
}

// ********************************************************
// Indique si les caracteres de l'afficheur sont visibles
// @return true si les caracteres sont visible, sinon false
// ********************************************************
bool Gestion1602A::isDisplayOn(void) {
	return(display);
}

// **********************************************************
// Indique si les caracteres de l'afficheur sont invisibles
// @return true si les caracteres sont invisible, sinon false
// **********************************************************
bool Gestion1602A::isDisplayOff(void) {
	return(!display);
}

// **************************************
// Rend le curseur de l'afficheur visible
// **************************************
void Gestion1602A::cursorOn(void) {
	cursor = true;
	lcdCursor(handle, true);
}

// ****************************************
// Rend le curseur de l'afficheur invisible
// ****************************************
void Gestion1602A::cursorOff(void) {
	cursor = false;
	lcdCursor(handle, false);
}

// ***************************************************
// Indique si le curseur de l'afficheur est visible
// @return true si le curseur est visible, sinon false
// ***************************************************
bool Gestion1602A::isCursorOn(void) {
	return(cursor);
}

// *****************************************************
// Indique si le curseur de l'afficheur est invisible
// @return true si le curseur est invisible, sinon false
// *****************************************************
bool Gestion1602A::isCursorOff(void) {
	return(!cursor);
}

// ****************************************
// Fait clignoter le curseur de l'afficheur
// ****************************************
void Gestion1602A::cursorBlinkOn(void) {
	cursorBlink = true;
	lcdCursorBlink(handle, true);
}

// ************************************************
// Arrete le clignotement du curseur de l'afficheur
// ************************************************
void Gestion1602A::cursorBlinkOff(void) {
	cursorBlink = false;
	lcdCursorBlink(handle, false);
}

// ************************************************
// Indique si le curseur de l'afficheur clignote
// @return true si le curseur clignote, sinon false
// ************************************************
bool Gestion1602A::isCursorBlinkOn(void) {
	return(cursorBlink);
}

// ************************************************
// Indique si le curseur de l'afficheur est fixe
// @return true si le curseur est fixe, sinon false
// ************************************************
bool Gestion1602A::isCursorBlinkOff(void) {
	return(!cursorBlink);
}

// *******************************************************************
// Fixe la position du curseur
// @param la colonne
// @param la ligne
// @return false si la colonne ou la ligne sont hors écran, sinon true
// *******************************************************************
bool Gestion1602A::setPositions(int column, int row) {
	if(column < 0) {
		return false;
	}
	if(row < 0) {
		return false;
	}
	if(column >= nbColumns) {
		return false;
	}
	if(row >= nbRows) {
		return false;
	}
	lcdPosition(handle, column, row);
	positionX = column;
	positionY = row;
	return true;
}

// ******************************************************
// Fixe la colonne du curseur
// @param la colonne
// @return false si la colonne est hors écran, sinon true
// ******************************************************
bool Gestion1602A::setPositionX(int column) {
	if(column < 0) {
		return false;
	}
	if(column >= nbColumns) {
		return false;
	}
	lcdPosition(handle, column, positionY);
	positionX = column;
	return true;
}

// ****************************************************
// Fixe la ligne du curseur
// @param la ligne
// @return false si la ligne est hors écran, sinon true
// ****************************************************
bool Gestion1602A::setPositionY(int row) {
	if(row < 0) {
		return false;
	}
	if(row >= nbRows) {
		return false;
	}
	lcdPosition(handle, positionX, row);
	positionY = row;
	return true;
}

// ******************************************************
// Incremente la colonne du curseur
// @return false si la colonne est hors écran, sinon true
// ******************************************************
bool Gestion1602A::incPositionX(void) {
	if(positionX + 1 == nbColumns) {
		return false;
	}
	positionX++;
	lcdPosition(handle, positionX, positionY);
	return true;
}

// ****************************************************
// Incremente la ligne du curseur
// @return false si la ligne est hors écran, sinon true
// ****************************************************
bool Gestion1602A::incPositionY(void) {
	if(positionY + 1 == nbRows) {
		return false;
	}
	positionY++;
	lcdPosition(handle, positionX, positionY);
	return true;
}

// ******************************************************
// Decremente la colonne du curseur
// @return false si la colonne est hors écran, sinon true
// ******************************************************
bool Gestion1602A::decPositionX(void) {
	if(positionX == 0) {
		return false;
	}
	positionX--;
	lcdPosition(handle, positionX, positionY);
	return true;
}

// ****************************************************
// Decremente la ligne du curseur
// @return false si la ligne est hors écran, sinon true
// ****************************************************
bool Gestion1602A::decPositionY(void) {
	if(positionY == 0) {
		return false;
	}
	positionY--;
	lcdPosition(handle, positionX, positionY);
	return true;
}

// ********************************************************
// Incremente la colonne du curseur d'un nombre de positions
// @return false si la colonne est hors écran, sinon true
// ********************************************************
bool Gestion1602A::incPositionX(int valeur) {
	if(valeur <= 0) {
		return false;
	}
	if(positionX + valeur >= nbColumns) {
		return false;
	}
	positionX += valeur;
	lcdPosition(handle, positionX, positionY);
	return true;
}

// *********************************************************
// Decremente la colonne du curseur d'un nombre de positions
// @return false si la colonne est hors écran, sinon true
// *********************************************************
bool Gestion1602A::decPositionX(int valeur) {
	if(valeur <= 0) {
		return false;
	}
	if(positionX - valeur < 0) {
		return false;
	}
	positionX -= valeur;
	lcdPosition(handle, positionX, positionY);
	return true;
}

// *****************************
// Renvoie la colonne du curseur
// *****************************
int Gestion1602A::getPositionX(void) {
	return positionX;
}

// ***************************
// Renvoie la ligne du curseur
// ***************************
int Gestion1602A::getPositionY(void) {
	return positionY;
}

// *********************************************
// Defini l'un des huit caracteres definissables
// @param l'index du catactere
// @param le caractere
// @return false si l'index est hors perimetre
// *********************************************
bool Gestion1602A::charDef(int index, unsigned char caractere[8]) {
	if(index < 0) {
		return false;
	}
	if(index >= nbCharDef) {
		return false;
	}
	lcdCharDef(handle, index, caractere);
	return true;
}

// ****************************************
// Affiche l'un des caracteres definissable
// @param l'index du caractere
// ****************************************
bool Gestion1602A::putCharDef(int index) {
	if(index < 0) {
		return false;
	}
	if(index >= nbCharDef) {
		return false;
	}
	lcdPutchar(handle, index);
	return true;
}

// ******************
// Affiche un message 
// @param le message
// ******************
void Gestion1602A::puts(const char* message) {
	lcdPuts(handle, message);
}

// ***************************
// Affiche un message formatte
// @param le message
// ***************************
void Gestion1602A::printf(const char* message, ...) {
  va_list argp ;
  char buffer [1024] ;

  va_start (argp, message) ;
    vsnprintf (buffer, 1023, message, argp) ;
  va_end (argp) ;
  
  puts(buffer);
}

// ******************************************
// Demande si le destructeur sera appliqué
// return destroyFlag, le flag de destructeur
// ******************************************
bool Gestion1602A::isToDesactivate(void) {
	return desactivateFlag;
}

// ****************************************
// Indique que le destructeur sera appliqué
// ****************************************
void Gestion1602A::toDesactivate(void) {
	setToDesactivate(true);
}

// ***********************************************
// Indique que le destructeur ne sera pas appliqué
// ***********************************************
void Gestion1602A::noDesactivate(void) {
	setToDesactivate(false);
}

// ************************************
// Positionne le flag de destructeur
// @param pValue le flag de destructeur
// ************************************
void Gestion1602A::setToDesactivate(bool pValue) {
	desactivateFlag = pValue;
}

// **********************************
// Destructeur
// Vide l'affichage et eteint l'ecran
// **********************************
Gestion1602A::~Gestion1602A() {
 	if(isToDesactivate()) {
		clear();
		displayOff();
	}
}

}

