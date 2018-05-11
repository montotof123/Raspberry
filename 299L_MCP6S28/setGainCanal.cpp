#include <iostream>
#include <stdlib.h>   // La librairie standard

#include "GestionMCP6S28.h"

using namespace std;

GestionMCP6S28 mcp6s28(channel_1);

void afficheUsage(void) {
	cout << "Usage: setGainCanal gain canal" << endl;
	cout << "       gain : 1, 2, 4, 5, 8, 10, 16, 32" << endl;
	cout << "       canal: 0, 1, 2, 3, 4, 5, 6, 7" << endl;
}

int main(int argc, char *argv[]) {
	if(argc != 3) {
		cout << "Erreur nombre de paramètres" << endl;
		afficheUsage();
		exit(1);
	}
	switch(atoi(argv[1])) {
		case 1:  mcp6s28.setGain(mcp6s28.Gain_1); break;
		case 2:  mcp6s28.setGain(mcp6s28.Gain_2); break;
		case 4:  mcp6s28.setGain(mcp6s28.Gain_4); break;
		case 5:  mcp6s28.setGain(mcp6s28.Gain_5); break;
		case 8:  mcp6s28.setGain(mcp6s28.Gain_8); break;
		case 10: mcp6s28.setGain(mcp6s28.Gain_10); break;
		case 16: mcp6s28.setGain(mcp6s28.Gain_16); break;
		case 32: mcp6s28.setGain(mcp6s28.Gain_32); break;
		default: cout << "Erreur gain" << endl; afficheUsage(); exit(1);
	}
	switch(atoi(argv[2])) {
		case 0: mcp6s28.setCanal(mcp6s28.In_0); break;
		case 1: mcp6s28.setCanal(mcp6s28.In_1); break;
		case 2: mcp6s28.setCanal(mcp6s28.In_2); break;
		case 3: mcp6s28.setCanal(mcp6s28.In_3); break;
		case 4: mcp6s28.setCanal(mcp6s28.In_4); break;
		case 5: mcp6s28.setCanal(mcp6s28.In_5); break;
		case 6: mcp6s28.setCanal(mcp6s28.In_6); break;
		case 7: mcp6s28.setCanal(mcp6s28.In_7); break;
		default: cout << "Erreur canal d'entrée" << endl; afficheUsage(); exit(1);
	}
	cout << "Commande OK" << endl;
}
