//============================================================================
// Name        : tstMCP4251.cpp
// Author      : totof
// Version     :
// Copyright   : Free
// Description : test de la librairie MCP4251
//============================================================================

#include <iostream>	  // impression cout
#include <wiringPi.h> // La wiringPi
#include "GestionMCP4251.h"
#include "GestionSPI.h"

using namespace std;

// Objets utilisés
Channel channel = channel_0;
GestionMCP4251 mcp4251(channel);

// ******************
// Fonction pricipale
// ******************
int main() {
	cout << "Test du MCP4251" << endl;

	Pot pot0 = pot_0;
	Pot pot1 = pot_1;

	cout << "reset = " << mcp4251.reset() << endl;
	cout << "Pot0 = " << mcp4251.read(pot0) << endl;
	cout << "Pot1 = " << mcp4251.read(pot1) << endl;
	cout << "isConnect pot0 = " << mcp4251.isConnect(pot0) << endl;
	cout << "isConnect pot1 = " << mcp4251.isConnect(pot1) << endl;
	cout << "isConnectShdn pot0 = " << mcp4251.isConnectShutdown(pot0) << endl;
	cout << "isConnectShdn pot1 = " << mcp4251.isConnectShutdown(pot1) << endl << endl;
	
	cout << "Pot W0 = " << mcp4251.write(pot0, 700) << endl;
	cout << "Pot R0 = " << mcp4251.read(pot0) << endl;
	cout << "Pot W0 = " << mcp4251.write(pot0, 500) << endl;
	cout << "Pot R0 = " << mcp4251.read(pot0) << endl;
	cout << "Pot W0 = " << mcp4251.write(pot0, 400) << endl;
	cout << "Pot R0 = " << mcp4251.read(pot0) << endl;
	cout << "Pot W0 = " << mcp4251.write(pot0, 300) << endl;
	cout << "Pot R0 = " << mcp4251.read(pot0) << endl;
	cout << "Pot W0 = " << mcp4251.write(pot0, 258) << endl;
	cout << "Pot R0 = " << mcp4251.read(pot0) << endl;
	cout << "Pot W0 = " << mcp4251.write(pot0, 257) << endl;
	cout << "Pot R0 = " << mcp4251.read(pot0) << endl;
	cout << "Pot W0 = " << mcp4251.write(pot0, 256) << endl;
	cout << "Pot R0 = " << mcp4251.read(pot0) << endl;
	cout << "Pot W0 = " << mcp4251.write(pot0, 255) << endl;
	cout << "Pot R0 = " << mcp4251.read(pot0) << endl;
	cout << "Pot W0 = " << mcp4251.write(pot0, 250) << endl;
	cout << "Pot R0 = " << mcp4251.read(pot0) << endl;
	cout << "Pot W1 = " << mcp4251.write(pot1, 10) << endl;
	cout << "Pot R1 = " << mcp4251.read(pot1) << endl;
	cout << "Pot W1 = " << mcp4251.write(pot1, -5) << endl;
	cout << "Pot R1 = " << mcp4251.read(pot1) << endl;
	cout << "Pot W1 = " << mcp4251.write(pot1, 15) << endl;
	cout << "Pot R1 = " << mcp4251.read(pot1) << endl;
	for(int compteur = 0; compteur != 10; compteur++) {
		cout << "****************************************************" << endl;
		cout << "Pot I0 = " << mcp4251.increment(pot0) << endl;
		cout << "Pot I1 = " << mcp4251.decrement(pot1) << endl;
		cout << "Pot R0 = " << mcp4251.read(pot0) << endl;
		cout << "Pot R1 = " << mcp4251.read(pot1) << endl;
	}
	
	cout << "Max = " << mcp4251.getMaxValue() << endl;
	cout << "Shutdown = " << short(mcp4251.isShutdown()) << endl << endl;
	
	cout << "isConnect pot0 = " << mcp4251.isConnect(pot0) << endl;
	cout << "isConnect pot1 = " << mcp4251.isConnect(pot1) << endl;
	cout << "isConnectShdn pot0 = " << mcp4251.isConnectShutdown(pot0) << endl;
	cout << "isConnectShdn pot1 = " << mcp4251.isConnectShutdown(pot1) << endl << endl;
	
	cout << "unConnect pot0 = " << mcp4251.unConnect(pot0) << endl;
	cout << "isConnect pot0 = " << mcp4251.isConnect(pot0) << endl;
	cout << "isConnect pot1 = " << mcp4251.isConnect(pot1) << endl;
	cout << "connect pot0 = " << mcp4251.connect(pot0) << endl;
	cout << "isConnect pot0 = " << mcp4251.isConnect(pot0) << endl << endl;
	
	cout << "unConnect pot1 = " << mcp4251.unConnect(pot1) << endl;
	cout << "isConnect pot1 = " << mcp4251.isConnect(pot1) << endl;
	cout << "isConnect pot0 = " << mcp4251.isConnect(pot0) << endl;
	cout << "connect pot1 = " << mcp4251.connect(pot1) << endl;
	cout << "isConnect pot1 = " << mcp4251.isConnect(pot1) << endl << endl;
	
	cout << "unConnectShutdown pot0 = " << mcp4251.unConnectShutdown(pot0) << endl;
	cout << "isConnectShutdown pot0 = " << mcp4251.isConnectShutdown(pot0) << endl;
	cout << "isConnectShutdown pot1 = " << mcp4251.isConnectShutdown(pot1) << endl;
	cout << "connectShutdown pot0 = " << mcp4251.connectShutdown(pot0) << endl;
	cout << "isConnectShutdown pot0 = " << mcp4251.isConnectShutdown(pot0) << endl << endl;
	
	cout << "unConnectShutdown pot1 = " << mcp4251.unConnectShutdown(pot1) << endl;
	cout << "isConnectShutdown pot1 = " << mcp4251.isConnectShutdown(pot1) << endl;
	cout << "isConnectShutdown pot0 = " << mcp4251.isConnectShutdown(pot0) << endl;
	cout << "connectShutdown pot1 = " << mcp4251.connectShutdown(pot1) << endl;
	cout << "isConnectShutdown pot1 = " << mcp4251.isConnectShutdown(pot1) << endl << endl;
	}
