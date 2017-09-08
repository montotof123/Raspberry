/*
 * Gestion1602A.h
 *
 *  Created on: 08 september 2017
 *      Author: totof
 * Controle de l'afficheur LCD 1602A
 */

#ifndef _GESTION_1602A_H_
#define _GESTION_1602A_H_

#include "GestionPinGPIO.h"

namespace std {

class Gestion1602A : public GestionPin{
    public:
		Gestion1602A();
		Gestion1602A(PinGPIO, PinGPIO, PinGPIO, PinGPIO, PinGPIO, PinGPIO);
		Gestion1602A(PinGPIO, PinGPIO, PinGPIO, PinGPIO, PinGPIO, PinGPIO, PinGPIO, PinGPIO, PinGPIO, PinGPIO);
		void init(PinGPIO, PinGPIO, PinGPIO, PinGPIO, PinGPIO, PinGPIO);
		void init(PinGPIO, PinGPIO, PinGPIO, PinGPIO, PinGPIO, PinGPIO, PinGPIO, PinGPIO, PinGPIO, PinGPIO);
		bool isInitOk(void);
		void home(void);
		void clear(void);
		void displayOn(void);
		void displayOff(void);
		bool isDisplayOn(void);
		bool isDisplayOff(void);
		void cursorOn(void);
		void cursorOff(void);
		bool isCursorOn(void);
		bool isCursorOff(void);
		void cursorBlinkOn(void);
		void cursorBlinkOff(void);
		bool isCursorBlinkOn(void);
		bool isCursorBlinkOff(void);
		bool setPositions(int, int);
		bool setPositionX(int);
		bool setPositionY(int);
		bool incPositionX(void);
		bool incPositionY(void);
		bool decPositionX(void);
		bool decPositionY(void);
		bool incPositionX(int);
		bool decPositionX(int);
		int getPositionX(void);
		int getPositionY(void);
		bool charDef(int, unsigned char[8]);
		bool putCharDef(int);
		void puts(const char*);
		void printf(const char*, ...);
		bool isToDesactivate(void);
		void toDesactivate(void);
		void noDesactivate(void);
		void setToDesactivate(bool);
		
		virtual ~Gestion1602A();

    private:
		int handle;
		bool display = true;
		bool cursor = false;
		bool cursorBlink = false;
		int positionX = 0;
		int positionY = 0;
		bool initOk = false;
		bool desactivateFlag = true;
};
}

#endif /* _GESTION_1602A_H_ */