#include "Gestion1602AI2C.h"
#include <iostream>
#include <wiringPi.h>

using namespace std;

Gestion1602AI2C afficheur;
  
int main()
{
	cout << "Start" << endl;
	afficheur.setPositions(2, 0);           
	afficheur.puts("Bonjour totof"); 
	cout << "Bonjour totof" << endl;
		
	afficheur.setPositions(0, 1);           
	afficheur.puts("display false"); 
	afficheur.display(false);
	cout << "display false" << endl;
	delay(3000);
		
	afficheur.setPositions(0, 1);           
	afficheur.puts("display true "); 
	afficheur.display(true);
	cout << "display true" << endl;
	delay(5000);
		
	afficheur.setPositions(0, 1);           
	afficheur.puts("cursor true  "); 
	afficheur.cursor(true);
	cout << "cursor true" << endl;
	delay(5000);
		
	afficheur.setPositions(0, 1);           
	afficheur.puts("cursor false "); 
	afficheur.cursor(false);
	cout << "cursor false" << endl;
	delay(5000);
		
	afficheur.setPositions(0, 1);           
	afficheur.puts("blink true   "); 
	afficheur.blink(true);
	cout << "blink true" << endl;
	delay(5000);
		
	afficheur.setPositions(0, 1);           
	afficheur.puts("blink false  "); 
	afficheur.blink(false);
	cout << "blink false" << endl;
	delay(5000);
		
	afficheur.setPositions(0, 1);           
	afficheur.puts("bl / cur true"); 
	afficheur.blink(true);
	afficheur.cursor(true);
	cout << "blink cursor true" << endl;
	delay(5000);

	afficheur.setPositions(0, 0);
	afficheur.clear();
	afficheur.puts("Hello, I'am here");
	cout << "Coucou, je suis là" << endl;
	delay(2000);
		
	afficheur.home();
	afficheur.puts("      Fin       ");
	cout << "Fin" << endl;
	delay(2000);
}