/*
 * Gestion1602AI2C.cpp
 *
 *  Created on: 12 aout 2018
 *      Author: totof
 * Controle de l'afficheur LCD 1602A avec module I2C
 */
 
#define nbRows 2
#define nbColumns 16
#define LCDAddr 0x27

#include "Gestion1602AI2C.h"
#include <stdarg.h>
#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <stdint.h>
#include <string.h>

// ************
// Constructeur
// ************
Gestion1602AI2C::Gestion1602AI2C(void) {
	handle = wiringPiI2CSetup(LCDAddr);
	send_command(0x33);	// Must initialize to 8-line mode at first
	delay(5);
	send_command(0x32);	// Then initialize to 4-line mode
	delay(5);
	send_command(0x28);	// 2 Lines & 5*7 dots
	delay(5);
	display(true);	// Enable display without cursor
	delay(5);
	clear();	// Clear Screen
	wiringPiI2CWrite(handle, 0x08);
}

// **********************************
// Ramene le curseur en haut a gauche
// **********************************
void Gestion1602AI2C::home(void) {
	send_command(0x02);	// Clear Screen
}

// ***************************
// Vide l'ecran de l'afficheur
// ***************************
void Gestion1602AI2C::clear(void) {
	send_command(0x01);	// Clear Screen
}

// *************************************************************
// Gere l'allumage de l'afficheur, le curseur et le clignotement
// @Param allumage
// @Param l'affichage du curseur
// @Param le cligotement
// *************************************************************
void Gestion1602AI2C::gestDisplay(bool display, bool cursor, bool blink) {
	uint8_t value = 0b00001000;
	if(display){value += 0b00000100;}
	if(cursor) {value += 0b00000010;}
	if(blink)  {value += 0b00000001;}
	send_command(value);
}

// ********************************
// Gere l'affichage
// @Param l'allumage de l'affichage
// ********************************
void Gestion1602AI2C::display(bool param) {
	flagDisplay = param;
	gestDisplay(flagDisplay, flagCursor, flagBlink);
}

// ********************************
// Gere l'affichage
// @Param l'allumage de l'affichage
// ********************************
void Gestion1602AI2C::cursor(bool param) {
	flagCursor = param;
	gestDisplay(flagDisplay, flagCursor, flagBlink);
}
		
// ********************************
// Gere l'affichage
// @Param l'allumage de l'affichage
// ********************************
void Gestion1602AI2C::blink(bool param){
	flagBlink = param;
	gestDisplay(flagDisplay, flagCursor, flagBlink);
}

// *******************************************************************
// Fixe la position du curseur
// @param la colonne
// @param la ligne
// @return false si la colonne ou la ligne sont hors écran, sinon true
// *******************************************************************
bool Gestion1602AI2C::setPositions(int column, int row) {
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
	send_command(0x80 + 0x40 * row + column);
	return true;
}

// ******************
// Affiche un message 
// @param le message
// ******************
void Gestion1602AI2C::puts(char data[]) {
	for (int i = 0; i < strlen(data); i++){
		send_data(data[i]);
	}
}

// ********************
// Ecrit sur le bus I2C
// ********************
void Gestion1602AI2C::write_word(int data){
	int temp = data;
	temp |= 0x08;
	wiringPiI2CWrite(handle, temp);
}

// *********************************
// Envoie une commande a l'afficheur
// *********************************
void Gestion1602AI2C::send_command(int comm){
	int buf;
	// Send bit7-4 firstly
	buf = comm & 0xF0;
	buf |= 0x04;			// RS = 0, RW = 0, EN = 1
	write_word(buf);
	delay(2);
	buf &= 0xFB;			// Make EN = 0
	write_word(buf);

	// Send bit3-0 secondly
	buf = (comm & 0x0F) << 4;
	buf |= 0x04;			// RS = 0, RW = 0, EN = 1
	write_word(buf);
	delay(2);
	buf &= 0xFB;			// Make EN = 0
	write_word(buf);
}

// ********************************
// Envoie des données a l'afficheur
// ********************************
void Gestion1602AI2C::send_data(int data){
	int buf;
	// Send bit7-4 firstly
	buf = data & 0xF0;
	buf |= 0x05;			// RS = 1, RW = 0, EN = 1
	write_word(buf);
	delay(2);
	buf &= 0xFB;			// Make EN = 0
	write_word(buf);

	// Send bit3-0 secondly
	buf = (data & 0x0F) << 4;
	buf |= 0x05;			// RS = 1, RW = 0, EN = 1
	write_word(buf);
	delay(2);
	buf &= 0xFB;			// Make EN = 0
	write_word(buf);
}

// **********************************
// Destructeur
// Vide l'affichage et eteint l'ecran
// **********************************
Gestion1602AI2C::~Gestion1602AI2C(void) {
	clear();
	display(false);
}


