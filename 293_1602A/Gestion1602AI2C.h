/*
 * Gestion1602AI2C.h
 *
 *  Created on: 12 aout 2018
 *      Author: totof
 * Controle de l'afficheur LCD 1602A avec module I2C
 */

#ifndef _GESTION_1602AI2C_H_
#define _GESTION_1602AI2C_H_

class Gestion1602AI2C {
    public:
		Gestion1602AI2C(void);
		void home(void);
		void clear(void);
		void display(bool);
		void cursor(bool);
		void blink(bool);
		bool setPositions(int, int);
		void puts(char data[]);
		
		virtual ~Gestion1602AI2C(void);

    private:
		int handle;
		void write_word(int);
		void send_command(int);
		void send_data(int);
		void gestDisplay(bool, bool, bool);
		bool flagDisplay = true;
		bool flagCursor = false;
		bool flagBlink = false;
};

#endif /* _GESTION_1602AI2C_H_ */