/*
 * GestionInsecte.h
 *
 * Created on 23/10/2017
 * Author Totof
 *
 */
 
#ifndef GESTIONINSECTE_H_
#define GESTIONINSECTE_H_

#include "GestionPatte.h"
#include "GestionINA219.h"
#include "GestionPCA9685.h"
#include "GestionLedRGBPCA9685.h"

#define BASSIN_AVANT 280
#define BASSIN_MILIEU 300
#define BASSIN_ARRIERE 350
#define ROTULE_HAUT 520
#define ROTULE_MILIEU 290
#define ROTULE_BAS 170
#define GENOUX_INTERIEUR 120
#define GENOUX_CENTRE 320
#define GENOUX_EXTERIEUR 480

class GestionInsecte {
	public:
		GestionInsecte(void);
		
		void initPositionPatte(uint32_t);
		void avance(uint16_t, uint32_t);
		void recule(uint16_t, uint32_t);
		void rotationDroite(uint16_t, uint32_t);
		void rotationGauche(uint16_t, uint32_t);
		void avanceTroisPattes(uint16_t, uint32_t, GestionPatte&, GestionPatte&, GestionPatte&);
		void hausse(uint16_t, uint32_t, GestionPatte&);
		void hausse(uint16_t, uint32_t, GestionPatte&, GestionPatte&);
		void hausse(uint16_t, uint32_t, GestionPatte&, GestionPatte&, GestionPatte&);
		void hausse(uint16_t, uint32_t, GestionPatte&, GestionPatte&, GestionPatte&, GestionPatte&);
		void hausse(uint16_t, uint32_t, GestionPatte&, GestionPatte&, GestionPatte&, GestionPatte&, GestionPatte&);
		void hausse(uint16_t, uint32_t, GestionPatte&, GestionPatte&, GestionPatte&, GestionPatte&, GestionPatte&, GestionPatte&);
		void translation(uint16_t, uint32_t, GestionPatte&);
		void translation(uint16_t, uint32_t, GestionPatte&, GestionPatte&);
		void translation(uint16_t, uint32_t, GestionPatte&, GestionPatte&, GestionPatte&);
		void translation(uint16_t, uint32_t, GestionPatte&, GestionPatte&, GestionPatte&, GestionPatte&);
		void translation(uint16_t, uint32_t, GestionPatte&, GestionPatte&, GestionPatte&, GestionPatte&, GestionPatte&);
		void translation(uint16_t, uint32_t, GestionPatte&, GestionPatte&, GestionPatte&, GestionPatte&, GestionPatte&, GestionPatte&);
		void rotation(uint16_t, uint32_t, GestionPatte&);
		void rotation(uint16_t, uint32_t, GestionPatte&, GestionPatte&);
		void rotation(uint16_t, uint32_t, GestionPatte&, GestionPatte&, GestionPatte&);
		void rotation(uint16_t, uint32_t, GestionPatte&, GestionPatte&, GestionPatte&, GestionPatte&);
		void rotation(uint16_t, uint32_t, GestionPatte&, GestionPatte&, GestionPatte&, GestionPatte&, GestionPatte&);
		void rotation(uint16_t, uint32_t, GestionPatte&, GestionPatte&, GestionPatte&, GestionPatte&, GestionPatte&, GestionPatte&);
		void synchronisationHausse(GestionPatte&, GestionPatte&, uint32_t);
		void synchronisationTranslation(GestionPatte&, GestionPatte&, uint32_t);
		void synchronisationRotation(GestionPatte&, GestionPatte&, uint32_t);
		GestionINA219& getControlLeft(void);
		GestionINA219& getControlRight(void);
		GestionPatte& getPatteFrontLeft(void);
		GestionPatte& getPatteMiddleLeft(void);
		GestionPatte& getPatteRearLeft(void);
		GestionPatte& getPatteFrontRight(void);
		GestionPatte& getPatteMiddleRight(void);
		GestionPatte& getPatteRearRight(void);
		GestionLedRGBPCA9685& getTensionLeft(void);
		GestionLedRGBPCA9685& getCurrentLeft(void);
		GestionLedRGBPCA9685& getTensionRight(void);
		GestionLedRGBPCA9685& getCurrentRight(void);

		virtual ~GestionInsecte();
	
	private:
		GestionPCA9685 pwmLeft;
		GestionPCA9685 pwmRight;
		GestionPatte patteFrontLeft;
		GestionPatte patteMiddleLeft;
		GestionPatte patteRearLeft;
		GestionPatte patteFrontRight;
		GestionPatte patteMiddleRight;
		GestionPatte patteRearRight;
		GestionINA219 controlLeft;
		GestionINA219 controlRight;
		GestionLedRGBPCA9685 tensionLeft;
		GestionLedRGBPCA9685 currentLeft;
		GestionLedRGBPCA9685 tensionRight;
		GestionLedRGBPCA9685 currentRight;
};

#endif