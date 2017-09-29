/*
 * GestionServo.h
 *
 *  Created on: 14 août 2016
 *      Author: totof
 */

#ifndef GESTIONSERVO_H_
#define GESTIONSERVO_H_

#include <stdint.h>

#define ERROR -1
#define DEBATTEMENT_DEFAUT 180.0
#define DEGRES_PAR_TOUR 360
#define _50HZ 50

// Classe de gestion d'un servomoteur
// Classe virtuelle devant etre etendue
// avec les methodes de gestion du circuit PWM

typedef struct Servo Servo ;

struct Servo {
	uint16_t cycleMin;
	uint16_t cycleMax;
	float angleDebattement;
};

class GestionServo {
	public:
		GestionServo(void);
		GestionServo(uint16_t, uint16_t);
		GestionServo(uint16_t, uint16_t, float);
		GestionServo(Servo);
		void init(uint16_t, uint16_t, float);
		void init(Servo);
		uint16_t getCycleMin(void);
		uint16_t getCycleMax(void);
		float getAngleDebattement(void);
		void setAngleDebattement(float);
		void move(uint16_t);
		void move(float);
		uint16_t getValeur(void);
		float getAngle(void);
		bool isError(void);
		bool isFullInit(void);
		virtual ~GestionServo(void);
	
	protected:
		virtual bool initialisation(uint16_t) = 0; // param: full scale du pwm
		bool fullInit = false; // Doit etre gere dans la methode initialisation
		uint16_t cycleMin; // PWM min du servo, blocage si inferieur Doit etre controle dans la methode initialisation si superieur a 0
		uint16_t cycleMax; // PWM max du servo, blocage si superieur Doit etre controle dans la methode initialisation si inferieur au full scale
		
	private:
		virtual bool write(uint16_t) = 0; // return false si erreur true sinon

		float angleDebattement;
		uint16_t valeur = 0;
		float angle = -1.0;
		bool error = false;
		
};

#endif /* GESTIONSERVO_H_ */
