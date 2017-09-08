#include "Gestion1602A.h"
#include "GestionAD5220.h"
#include <iostream>

using namespace std;

Gestion1602A afficheur(GPIO22, GPIO17, GPIO25, GPIO18, GPIO24, GPIO23);
GestionAD5220 ad5220(GPIO19, GPIO26, 100000);
  
int main()
{
	ad5220.reInit();
	ad5220.writeOhm(500);
	if(afficheur.isInitOk()) {
		afficheur.setPositions(2, 0);           
		afficheur.printf("Bonjour %s", "totof"); 
		afficheur.setPositionX(1);
		afficheur.incPositionY();
		cout << "X=" << afficheur.getPositionX() << endl;
		cout << "Y=" << afficheur.getPositionY() << endl;
		afficheur.printf("valeur=%.2f", 52.456789); 
		delay(2000);
		
		afficheur.home();
		afficheur.cursorBlinkOn();
		delay(2000);
		
		afficheur.cursorBlinkOff();
		afficheur.cursorOn();
		delay(2000);
		
		cout << "Erreur position 1: " << afficheur.setPositions(16,0) << endl;
		cout << "Erreur position 2: " << afficheur.setPositions(0,2) << endl;
		cout << "Erreur position 3: " << afficheur.setPositions(-1,0) << endl;
		cout << "Erreur position 4: " << afficheur.setPositions(0,-1) << endl;
		cout << "Erreur position 5: " << afficheur.incPositionX(-1) << endl;
		cout << "Erreur position 7: " << afficheur.incPositionX(0) << endl;
		
		afficheur.setPositions(15,1);
		cout << "Erreur position 9: " << afficheur.incPositionX() << endl;
		cout << "Erreur position 10: " << afficheur.incPositionY() << endl;
		cout << "Position X = " << afficheur.getPositionX() << endl;
		cout << "Position Y = " << afficheur.getPositionY() << endl;
		
		afficheur.setPositions(0, 0);
		cout << "Erreur position 11: " << afficheur.decPositionX() << endl;
		cout << "Erreur position 12: " << afficheur.decPositionY() << endl;
		cout << "Position X = " << afficheur.getPositionX() << endl;
		cout << "Position Y = " << afficheur.getPositionY() << endl;
		
		afficheur.setPositions(0, 0);
		cout << "Position 13: " << afficheur.incPositionX(15) << endl;
		cout << "Position X = " << afficheur.getPositionX() << endl;
		cout << "Position Y = " << afficheur.getPositionY() << endl;

		afficheur.setPositions(0, 0);
		cout << "Erreur position 14: " << afficheur.incPositionX(16) << endl;
		cout << "Position X = " << afficheur.getPositionX() << endl;
		cout << "Position Y = " << afficheur.getPositionY() << endl;

		afficheur.setPositions(15,1);
		cout << "Position 15: " << afficheur.decPositionX(15) << endl;
		cout << "Position X = " << afficheur.getPositionX() << endl;
		cout << "Position Y = " << afficheur.getPositionY() << endl;
		
		afficheur.setPositions(15,1);
		cout << "Erreur position 16: " << afficheur.decPositionX(16) << endl;
		cout << "Position X = " << afficheur.getPositionX() << endl;
		cout << "Position Y = " << afficheur.getPositionY() << endl;
		
		afficheur.setPositions(10, 1);
		afficheur.clear();
		afficheur.puts("Coucou, je suis là");
		delay(2000);
		
		unsigned char omega[8] = { 0b00000,
						  0b01110,
						  0b10001,
						  0b10001,
						  0b10001,
						  0b01010,
						  0b11011,
						  0b00000};

		unsigned char pi[8] = { 0b00000,
					   0b00000,
					   0b11111,
					   0b01010,
					   0b01010,
					   0b01010,
					   0b10011,
					   0b00000};

		unsigned char mu[8] = { 0b00000,
					   0b10010,
					   0b10010,
					   0b10010,
					   0b10010,
					   0b11101,
					   0b10000,
					   0b10000};
					   
		unsigned char drop[8] = { 0b00100,
						 0b00100,
						 0b01010,
						 0b01010,
						 0b10001,
						 0b10001,
						 0b10001,
						 0b01110}; 
				   
		unsigned char temp[8] = { 0b00100,
						 0b01010,
						 0b01010,
						 0b01110,
						 0b01110,
						 0b11111,
						 0b11111,
						 0b01110};

		unsigned char rond[8] = { 0b11111,
						 0b10001,
						 0b10001,
						 0b10001,
						 0b10001,
						 0b10001,
						 0b10001,
						 0b11111};

		afficheur.charDef(11, omega); 
        afficheur.charDef(12, pi);
        afficheur.charDef(13, mu);
        afficheur.charDef(14, drop);
        afficheur.charDef(15, temp);
        afficheur.charDef(10, rond);

        afficheur.clear();

		afficheur.setPositions(0, 0);
        afficheur.putCharDef(11);
        afficheur.putCharDef(12);
        afficheur.putCharDef(13);
        afficheur.putCharDef(14);
        afficheur.putCharDef(15);
        afficheur.putCharDef(10);
		delay(5000);
		
	}
}