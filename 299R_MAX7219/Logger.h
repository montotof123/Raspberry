/***************************************************************
 *   \file    Logger.h
 *   \brief   Entete de la classe de gestion des log
 *   \author  Totof (raspberry.pi123@orange.fr)
 *   \version 1.0
 *   \date    24/07/2019
 ***************************************************************/
 
#include <string>
#include <stdint.h>

using namespace std;

#ifndef LOGGER_H_
#define LOGGER_H_

class Logger {
public:
	static void log(string, string, bool pSautLigne = true);
	static void log(const char*, const char*, bool pSautLigne = true);
	static void log(string, float, bool pSautLigne = true);
	static void log(const char*, float, bool pSautLigne = true);
	static void log(string, int, bool pSautLigne = true);
	static void log(const char*, int, bool pSautLigne = true);
	static void log(string, uint32_t, bool pSautLigne = true);
	static void log(const char*, uint32_t, bool pSautLigne = true);
	static void logHex(string, uint32_t, bool pSautLigne = true);
	static void logHex(const char*, uint32_t, bool pSautLigne = true);
	static void log(string, uint16_t, bool pSautLigne = true);
	static void log(const char*, uint16_t, bool pSautLigne = true);
	static void logHex(string, uint16_t, bool pSautLigne = true);
	static void logHex(const char*, uint16_t, bool pSautLigne = true);
	static void log(string, uint8_t, bool pSautLigne = true);
	static void log(const char*, uint8_t, bool pSautLigne = true);
	static void logHex(string, uint8_t, bool pSautLigne = true);
	static void logHex(const char*, uint8_t, bool pSautLigne = true);
	static void log(string, bool, bool pSautLigne = true);
	static void log(const char*, bool, bool pSautLigne = true);
	static void stop(string);
	static void stop(const char*);

private:
	static void logFormat(const char*, const char*, uint32_t, bool pSautLigne = true);
};

#endif