/*
 * GestionInsecte.cpp
 *
 * Created on 23/10/2017
 * Author Totof
 *
 */

#include <wiringPi.h>
 
#include "GestionInsecte.h"
#include "ListServo.h"

// ***************************
// Constructeur
// Initialisation des circuits
// ***************************
GestionInsecte::GestionInsecte() {
	// Initialisation des PCA9685
	pwmLeft.init(GestionPCA9685::ADDR_40);
	pwmLeft.setPWMFreq(_50HZ);
	pwmLeft.sleep();
	pwmRight.init(GestionPCA9685::ADDR_41);
	pwmRight.setPWMFreq(_50HZ);
	pwmRight.sleep();

	// Initialisation des pattes
	patteFrontLeft.init(&pwmLeft, GestionPCA9685::LED_0, Sg90_PatteFG_Bassin_PCA9685, GestionPCA9685::LED_1, Sg90_PatteFG_Femur_PCA9685, GestionPCA9685::LED_2, Sg90_PatteFG_Rotule_PCA9685);
	patteMiddleLeft.init(&pwmLeft, GestionPCA9685::LED_3, Sg90_PatteMG_Bassin_PCA9685, GestionPCA9685::LED_4, Sg90_PatteMG_Femur_PCA9685, GestionPCA9685::LED_5, Sg90_PatteMG_Rotule_PCA9685);
	patteRearLeft.init(&pwmLeft, GestionPCA9685::LED_6, Sg90_PatteRG_Bassin_PCA9685, GestionPCA9685::LED_7, Sg90_PatteRG_Femur_PCA9685, GestionPCA9685::LED_8, Sg90_PatteRG_Rotule_PCA9685);
	patteFrontRight.init(&pwmRight, GestionPCA9685::LED_0, Sg90_PatteFD_Bassin_PCA9685, GestionPCA9685::LED_1, Sg90_PatteFD_Femur_PCA9685, GestionPCA9685::LED_2, Sg90_PatteFD_Rotule_PCA9685);
	patteMiddleRight.init(&pwmRight, GestionPCA9685::LED_3, Sg90_PatteMD_Bassin_PCA9685, GestionPCA9685::LED_4, Sg90_PatteMD_Femur_PCA9685, GestionPCA9685::LED_5, Sg90_PatteMD_Rotule_PCA9685);
	patteRearRight.init(&pwmRight, GestionPCA9685::LED_6, Sg90_PatteRD_Bassin_PCA9685, GestionPCA9685::LED_7, Sg90_PatteRD_Femur_PCA9685, GestionPCA9685::LED_8, Sg90_PatteRD_Rotule_PCA9685);
	
	// Initialisation des mesureurs
	controlLeft.init(GestionINA219::ADDR_44);
	controlRight.init(GestionINA219::ADDR_45);
		
	// Initialisation de la gestion des LED de controle
	tensionLeft.init(GestionPCA9685::LED_10, GestionPCA9685::LED_11, GestionPCA9685::LED_12, GestionLedRGB::CommonAnode, &pwmLeft);
	currentLeft.init(GestionPCA9685::LED_13, GestionPCA9685::LED_14, GestionPCA9685::LED_15, GestionLedRGB::CommonAnode, &pwmLeft);
	tensionRight.init(GestionPCA9685::LED_10, GestionPCA9685::LED_11, GestionPCA9685::LED_12, GestionLedRGB::CommonAnode, &pwmRight);
	currentRight.init(GestionPCA9685::LED_13, GestionPCA9685::LED_14, GestionPCA9685::LED_15, GestionLedRGB::CommonAnode, &pwmRight);
		
	// Initialisation de la position des pattes
	initPositionPatte(0);
	
	// Active tout
	pwmLeft.unSleep();
	pwmRight.unSleep();

}

// ************************************************************
// Initialisation de la postion des pattes, au centre et droite
// @Param la temporisation entre deux pas des servos
// ************************************************************
void GestionInsecte::initPositionPatte(uint32_t tempo) {
	// Positionne la patte avant gauche
	patteFrontLeft.hausse(ROTULE_HAUT, tempo);
	patteFrontLeft.rotation(BASSIN_MILIEU, tempo);
	patteFrontLeft.translation(GENOUX_CENTRE, tempo);

	// Synchronise les 6 pattes sur la patte avant gauche
	// Leve les 6 pattes
	hausse(ROTULE_HAUT, tempo, patteFrontLeft, patteMiddleLeft, patteRearLeft, patteFrontRight, patteMiddleRight, patteRearRight);
	
	// Positionne les pattes au milieu
	rotation(BASSIN_MILIEU, tempo, patteFrontLeft, patteMiddleLeft, patteRearLeft, patteFrontRight, patteMiddleRight, patteRearRight);

	// Pattes droites
	translation(GENOUX_CENTRE, tempo, patteFrontLeft, patteMiddleLeft, patteRearLeft, patteFrontRight, patteMiddleRight, patteRearRight);

	// baisse les 6 pattes
	hausse(ROTULE_MILIEU, tempo, patteFrontLeft, patteMiddleLeft, patteRearLeft, patteFrontRight, patteMiddleRight, patteRearRight);	
}

// ************************************************
// Fait avancer l'insecte d'un nombre de pas
// @Param le nombre de pas
// @Param la tempo entre deux increments des servos
// ************************************************
void GestionInsecte::avance(uint16_t nbPas, uint32_t tempo) {
	for(int compteur = 0; compteur != nbPas; compteur++) {
		// Groupe 1 en haut
		hausse(ROTULE_HAUT, tempo, patteFrontLeft, patteRearLeft, patteMiddleRight);
		// Groupe 1 en avant
		avanceTroisPattes(BASSIN_AVANT, tempo, patteFrontLeft, patteRearLeft, patteMiddleRight);
		// Groupe 1 au sol
		hausse(ROTULE_MILIEU, tempo, patteFrontLeft, patteRearLeft, patteMiddleRight);
		// Groupe 2 en haut
		hausse(ROTULE_HAUT, tempo, patteMiddleLeft, patteFrontRight, patteRearRight);
		// Groupe 1 en arriere
		avanceTroisPattes(BASSIN_ARRIERE, tempo, patteFrontLeft, patteRearLeft, patteMiddleRight);
		// Groupe 2 en avant
		avanceTroisPattes(BASSIN_AVANT, tempo, patteMiddleLeft, patteFrontRight, patteRearRight);
		// Groupe 2 au sol
		hausse(ROTULE_MILIEU, tempo, patteMiddleLeft, patteFrontRight, patteRearRight);
		// Groupe 2 en arriere
		avanceTroisPattes(BASSIN_ARRIERE, tempo, patteMiddleLeft, patteFrontRight, patteRearRight);
	}
}

// ************************************************
// Fait reculer l'insecte d'un nombre de pas
// @Param le nombre de pas
// @Param la tempo entre deux increments des servos
// ************************************************
void GestionInsecte::recule(uint16_t nbPas, uint32_t tempo) {
	for(int compteur = 0; compteur != nbPas; compteur++) {
		// Groupe 1 en haut
		hausse(ROTULE_HAUT, tempo, patteFrontLeft, patteRearLeft, patteMiddleRight);
		// Groupe 1 en avant
		avanceTroisPattes(BASSIN_ARRIERE, tempo, patteFrontLeft, patteRearLeft, patteMiddleRight);
		// Groupe 1 au sol
		hausse(ROTULE_MILIEU, tempo, patteFrontLeft, patteRearLeft, patteMiddleRight);
		// Groupe 2 en haut
		hausse(ROTULE_HAUT, tempo, patteMiddleLeft, patteFrontRight, patteRearRight);
		// Groupe 1 en arriere
		avanceTroisPattes(BASSIN_AVANT, tempo, patteFrontLeft, patteRearLeft, patteMiddleRight);
		// Groupe 2 en avant
		avanceTroisPattes(BASSIN_ARRIERE, tempo, patteMiddleLeft, patteFrontRight, patteRearRight);
		// Groupe 2 au sol
		hausse(ROTULE_MILIEU, tempo, patteMiddleLeft, patteFrontRight, patteRearRight);
		// Groupe 2 en arriere
		avanceTroisPattes(BASSIN_AVANT, tempo, patteMiddleLeft, patteFrontRight, patteRearRight);
	}
}

// **************************************************
// Fait tourner l'insecte a droite d'un nombre de pas
// @Param le nombre de pas
// @Param la tempo entre deux increments des servos
// **************************************************
void GestionInsecte::rotationDroite(uint16_t nbPas, uint32_t tempo) {
	for(int compteur = 0; compteur != nbPas; compteur++) {
		// Groupe 1 en haut
		hausse(ROTULE_HAUT, tempo, patteFrontLeft, patteRearLeft, patteMiddleRight);
		// Groupe 1 en avant
		rotation(BASSIN_ARRIERE, tempo, patteFrontLeft, patteRearLeft, patteMiddleRight);
		// Groupe 1 au sol
		hausse(ROTULE_MILIEU, tempo, patteFrontLeft, patteRearLeft, patteMiddleRight);
		// Groupe 2 en haut
		hausse(ROTULE_HAUT, tempo, patteMiddleLeft, patteFrontRight, patteRearRight);
		// Groupe 1 en arriere
		rotation(BASSIN_AVANT, tempo, patteFrontLeft, patteRearLeft, patteMiddleRight);
		// Groupe 2 en avant
		rotation(BASSIN_ARRIERE, tempo, patteMiddleLeft, patteFrontRight, patteRearRight);
		// Groupe 2 au sol
		hausse(ROTULE_MILIEU, tempo, patteMiddleLeft, patteFrontRight, patteRearRight);
		// Groupe 2 en arriere
		rotation(BASSIN_AVANT, tempo, patteMiddleLeft, patteFrontRight, patteRearRight);
	}
}
		
// **************************************************
// Fait tourner l'insecte a gauche d'un nombre de pas
// @Param le nombre de pas
// @Param la tempo entre deux increments des servos
// **************************************************
void GestionInsecte::rotationGauche(uint16_t nbPas, uint32_t tempo) {
	for(int compteur = 0; compteur != nbPas; compteur++) {
		// Groupe 1 en haut
		hausse(ROTULE_HAUT, tempo, patteFrontLeft, patteRearLeft, patteMiddleRight);
		// Groupe 1 en avant
		rotation(BASSIN_ARRIERE, tempo, patteFrontLeft, patteRearLeft, patteMiddleRight);
		// Groupe 1 au sol
		hausse(ROTULE_MILIEU, tempo, patteFrontLeft, patteRearLeft, patteMiddleRight);
		// Groupe 2 en haut
		hausse(ROTULE_HAUT, tempo, patteMiddleLeft, patteFrontRight, patteRearRight);
		// Groupe 1 en arriere
		rotation(BASSIN_AVANT, tempo, patteFrontLeft, patteRearLeft, patteMiddleRight);
		// Groupe 2 en avant
		rotation(BASSIN_ARRIERE, tempo, patteMiddleLeft, patteFrontRight, patteRearRight);
		// Groupe 2 au sol
		hausse(ROTULE_MILIEU, tempo, patteMiddleLeft, patteFrontRight, patteRearRight);
		// Groupe 2 en arriere
		rotation(BASSIN_AVANT, tempo, patteMiddleLeft, patteFrontRight, patteRearRight);
	}
}

// ************************************************
// avance sur trois pattes		
// @Param le nombre de pas des servos
// @Param la tempo entre deux increments des servos
// @Param la premiere patte (maitre pour synchro)
// @Param la deuxieme patte
// @Param la troisieme patte
// ************************************************
void GestionInsecte::avanceTroisPattes(uint16_t valeur, uint32_t tempo, GestionPatte& patte1, GestionPatte& patte2, GestionPatte& patte3) {
	synchronisationRotation(patte2, patte1, tempo);
	synchronisationRotation(patte3, patte1, tempo);
	if(patte1.getBassin().getValeur() < valeur) {
		for(int compteur = patte1.getBassin().getValeur(); compteur != valeur; compteur++) {
			patte1.rotation(compteur);
			patte2.rotation(-compteur);
			patte3.rotation(compteur);
			delayMicroseconds(tempo);
		}
	} else {
		for(int compteur = valeur; compteur != patte1.getBassin().getValeur(); compteur++) {
			patte1.rotation(compteur);
			patte2.rotation(-compteur);
			patte3.rotation(compteur);
			delayMicroseconds(tempo);
		}
	}
}

// ************************************************
// synchronise en hauteur deux pattes entre elles
// @Param Patte a synchroniser
// @Param patte cible
// @Param la tempo entre deux increments des servos
// ************************************************
void GestionInsecte::synchronisationHausse(GestionPatte& synchro, GestionPatte& cible, uint32_t tempo) {
	hausse(cible.getFemur().getValeur(), tempo, synchro);
}

// **************************************************
// synchronise en translation deux pattes entre elles
// @Param Patte a synchroniser
// @Param patte cible
// @Param la tempo entre deux increments des servos
// **************************************************
void GestionInsecte::synchronisationTranslation(GestionPatte& synchro, GestionPatte& cible, uint32_t tempo) {
	translation(cible.getRotule().getValeur(), tempo, synchro);
}

// ***********************************************
// synchronise en rotation deux pattes entre elles
// @Param Patte a synchroniser
// @Param patte cible
// @Param la tempo entre deux increments des servos
// ************************************************
void GestionInsecte::synchronisationRotation(GestionPatte& synchro, GestionPatte& cible, uint32_t tempo) {
	rotation(cible.getBassin().getValeur(), tempo, synchro);
}

// ************************************************
// Monte une patte		
// @Param le nombre de pas cible du servo
// @Param la tempo entre deux increments des servos
// @Param la premiere patte
// ************************************************
void GestionInsecte::hausse(uint16_t valeur, uint32_t tempo, GestionPatte& patte1) {
	uint16_t valFemur = patte1.getFemur().getValeur();
	if(valFemur < valeur) {
		for(int compteur = valFemur; compteur != valeur; compteur++) {
			patte1.hausse(compteur);
			delayMicroseconds(tempo);
		}
	}
	if(valFemur > valeur) {
		for(int compteur = valFemur; compteur != valeur; compteur--) {
			patte1.hausse(compteur);
			delayMicroseconds(tempo);
		}
	}
}

// ************************************************
// Monte deux pattes		
// @Param le nombre de pas cible des servos
// @Param la tempo entre deux increments des servos
// @Param la premiere patte (maitre pour synchro)
// @Param la deuxieme patte
// ************************************************
void GestionInsecte::hausse(uint16_t valeur, uint32_t tempo, GestionPatte& patte1, GestionPatte& patte2) {

	synchronisationHausse(patte2, patte1, tempo);
	uint16_t valFemur = patte1.getFemur().getValeur();
	if(valFemur < valeur) {
		for(int compteur = valFemur; compteur != valeur; compteur++) {
			patte1.hausse(compteur);
			patte2.hausse(compteur);
			delayMicroseconds(tempo);
		}
	}
	if(valFemur > valeur) {
		for(int compteur = valFemur; compteur != valeur; compteur--) {
			patte1.hausse(compteur);
			patte2.hausse(compteur);
			delayMicroseconds(tempo);
		}
	}
}

// ************************************************
// Monte trois pattes		
// @Param le nombre de pas cible des servos
// @Param la tempo entre deux increments des servos
// @Param la premiere patte (maitre pour synchro)
// @Param la deuxieme patte
// @Param la troisieme patte
// ************************************************
void GestionInsecte::hausse(uint16_t valeur, uint32_t tempo, GestionPatte& patte1, GestionPatte& patte2, GestionPatte& patte3) {
	synchronisationHausse(patte2, patte1, tempo);
	synchronisationHausse(patte3, patte1, tempo);
	uint16_t valFemur = patte1.getFemur().getValeur();
	if(valFemur < valeur) {
		for(int compteur = valFemur; compteur != valeur; compteur++) {
			patte1.hausse(compteur);
			patte2.hausse(compteur);
			patte3.hausse(compteur);
			delayMicroseconds(tempo);
		}
	}
	if(valFemur > valeur) {
		for(int compteur = valFemur; compteur != valeur; compteur--) {
			patte1.hausse(compteur);
			patte2.hausse(compteur);
			patte3.hausse(compteur);
			delayMicroseconds(tempo);
		}
	}
}

// ************************************************
// Monte quatre pattes		
// @Param le nombre de pas cible des servos
// @Param la tempo entre deux increments des servos
// @Param la premiere patte (maitre pour synchro)
// @Param la deuxieme patte
// @Param la troisieme patte
// @Param la quatrieme patte
// ************************************************
void GestionInsecte::hausse(uint16_t valeur, uint32_t tempo, GestionPatte& patte1, GestionPatte& patte2, GestionPatte& patte3, GestionPatte& patte4) {
	synchronisationHausse(patte2, patte1, tempo);
	synchronisationHausse(patte3, patte1, tempo);
	synchronisationHausse(patte4, patte1, tempo);
	uint16_t valFemur = patte1.getFemur().getValeur();
	if(valFemur < valeur) {
		for(int compteur = valFemur; compteur != valeur; compteur++) {
			patte1.hausse(compteur);
			patte2.hausse(compteur);
			patte3.hausse(compteur);
			patte4.hausse(compteur);
			delayMicroseconds(tempo);
		}
	}
	if(valFemur > valeur) {
		for(int compteur = valFemur; compteur != valeur; compteur--) {
			patte1.hausse(compteur);
			patte2.hausse(compteur);
			patte3.hausse(compteur);
			patte4.hausse(compteur);
			delayMicroseconds(tempo);
		}
	}
}

// ************************************************
// Monte cinq pattes		
// @Param le nombre de pas cible des servos
// @Param la tempo entre deux increments des servos
// @Param la premiere patte (maitre pour synchro)
// @Param la deuxieme patte
// @Param la troisieme patte
// @Param la quatrieme patte
// @Param la cinquieme patte
// ************************************************
void GestionInsecte::hausse(uint16_t valeur, uint32_t tempo, GestionPatte& patte1, GestionPatte& patte2, GestionPatte& patte3, GestionPatte& patte4, GestionPatte& patte5) {
	synchronisationHausse(patte2, patte1, tempo);
	synchronisationHausse(patte3, patte1, tempo);
	synchronisationHausse(patte4, patte1, tempo);
	synchronisationHausse(patte5, patte1, tempo);
	uint16_t valFemur = patte1.getFemur().getValeur();
	if(valFemur < valeur) {
		for(int compteur = valFemur; compteur != valeur; compteur++) {
			patte1.hausse(compteur);
			patte2.hausse(compteur);
			patte3.hausse(compteur);
			patte4.hausse(compteur);
			patte5.hausse(compteur);
			delayMicroseconds(tempo);
		}
	}
	if(valFemur > valeur) {
		for(int compteur = valFemur; compteur != valeur; compteur--) {
			patte1.hausse(compteur);
			patte2.hausse(compteur);
			patte3.hausse(compteur);
			patte4.hausse(compteur);
			patte5.hausse(compteur);
			delayMicroseconds(tempo);
		}
	}
}

// ************************************************
// Monte six pattes		
// @Param le nombre de pas cible des servos
// @Param la tempo entre deux increments des servos
// @Param la premiere patte (maitre pour synchro)
// @Param la deuxieme patte
// @Param la troisieme patte
// @Param la quatrieme patte
// @Param la cinquieme patte
// @Param la sixieme patte
// ************************************************
void GestionInsecte::hausse(uint16_t valeur, uint32_t tempo, GestionPatte& patte1, GestionPatte& patte2, GestionPatte& patte3, GestionPatte& patte4, GestionPatte& patte5, GestionPatte& patte6) {
	synchronisationHausse(patte2, patte1, tempo);
	synchronisationHausse(patte3, patte1, tempo);
	synchronisationHausse(patte4, patte1, tempo);
	synchronisationHausse(patte5, patte1, tempo);
	synchronisationHausse(patte6, patte1, tempo);
	uint16_t valFemur = patte1.getFemur().getValeur();
	if(valFemur < valeur) {
		for(int compteur = valFemur; compteur != valeur; compteur++) {
			patte1.hausse(compteur);
			patte2.hausse(compteur);
			patte3.hausse(compteur);
			patte4.hausse(compteur);
			patte5.hausse(compteur);
			patte6.hausse(compteur);
			delayMicroseconds(tempo);
		}
	}
	if(valFemur > valeur) {
		for(int compteur = valFemur; compteur != valeur; compteur--) {
			patte1.hausse(compteur);
			patte2.hausse(compteur);
			patte3.hausse(compteur);
			patte4.hausse(compteur);
			patte5.hausse(compteur);
			patte6.hausse(compteur);
			delayMicroseconds(tempo);
		}
	}
}

// ************************************************
// Incline une patte		
// @Param le nombre de pas cible du servo
// @Param la tempo entre deux increments des servos
// @Param la premiere patte
// ************************************************
void GestionInsecte::translation(uint16_t valeur, uint32_t tempo, GestionPatte& patte1) {
	uint16_t valRotule = patte1.getRotule().getValeur();
	if(valRotule < valeur) {
		for(int compteur = valRotule; compteur != valeur; compteur++) {
			patte1.translation(compteur);
			delayMicroseconds(tempo);
		}
	}
	if(valRotule > valeur) {
		for(int compteur = valRotule; compteur != valeur; compteur--) {
			patte1.translation(compteur);
			delayMicroseconds(tempo);
		}
	}
}

// ************************************************
// Incline deux pattes		
// @Param le nombre de pas cible des servos
// @Param la tempo entre deux increments des servos
// @Param la premiere patte (maitre pour synchro)
// @Param la deuxieme patte
// ************************************************
void GestionInsecte::translation(uint16_t valeur, uint32_t tempo, GestionPatte& patte1, GestionPatte& patte2) {
	synchronisationTranslation(patte2, patte1, tempo);
	uint16_t valRotule = patte1.getRotule().getValeur();
	if(valRotule < valeur) {
		for(int compteur = valRotule; compteur != valeur; compteur++) {
			patte1.translation(compteur);
			patte2.translation(compteur);
			delayMicroseconds(tempo);
		}
	}
	if(valRotule > valeur) {
		for(int compteur = valRotule; compteur != valeur; compteur--) {
			patte1.translation(compteur);
			patte2.translation(compteur);
			delayMicroseconds(tempo);
		}
	}
}

// ************************************************
// Incline trois pattes		
// @Param le nombre de pas cible des servos
// @Param la tempo entre deux increments des servos
// @Param la premiere patte (maitre pour synchro)
// @Param la deuxieme patte
// @Param la troisieme patte
// ************************************************
void GestionInsecte::translation(uint16_t valeur, uint32_t tempo, GestionPatte& patte1, GestionPatte& patte2, GestionPatte& patte3) {
	synchronisationTranslation(patte2, patte1, tempo);
	synchronisationTranslation(patte3, patte1, tempo);
	uint16_t valRotule = patte1.getRotule().getValeur();
	if(valRotule < valeur) {
		for(int compteur = valRotule; compteur != valeur; compteur++) {
			patte1.translation(compteur);
			patte2.translation(compteur);
			patte3.translation(compteur);
			delayMicroseconds(tempo);
		}
	}
	if(valRotule > valeur) {
		for(int compteur = valRotule; compteur != valeur; compteur--) {
			patte1.translation(compteur);
			patte2.translation(compteur);
			patte3.translation(compteur);
			delayMicroseconds(tempo);
		}
	}
}

// ************************************************
// Incline quatre pattes		
// @Param le nombre de pas cible des servos
// @Param la tempo entre deux increments des servos
// @Param la premiere patte (maitre pour synchro)
// @Param la deuxieme patte
// @Param la troisieme patte
// @Param la quatrieme patte
// ************************************************
void GestionInsecte::translation(uint16_t valeur, uint32_t tempo, GestionPatte& patte1, GestionPatte& patte2, GestionPatte& patte3, GestionPatte& patte4) {
	synchronisationTranslation(patte2, patte1, tempo);
	synchronisationTranslation(patte3, patte1, tempo);
	synchronisationTranslation(patte4, patte1, tempo);
	uint16_t valRotule = patte1.getRotule().getValeur();
	if(valRotule < valeur) {
		for(int compteur = valRotule; compteur != valeur; compteur++) {
			patte1.translation(compteur);
			patte2.translation(compteur);
			patte3.translation(compteur);
			patte4.translation(compteur);
			delayMicroseconds(tempo);
		}
	}
	if(valRotule > valeur) {
		for(int compteur = valRotule; compteur != valeur; compteur--) {
			patte1.translation(compteur);
			patte2.translation(compteur);
			patte3.translation(compteur);
			patte4.translation(compteur);
			delayMicroseconds(tempo);
		}
	}
}

// ************************************************
// Incline cinq pattes		
// @Param le nombre de pas cible des servos
// @Param la tempo entre deux increments des servos
// @Param la premiere patte (maitre pour synchro)
// @Param la deuxieme patte
// @Param la troisieme patte
// @Param la quatrieme patte
// @Param la cinquieme patte
// ************************************************
void GestionInsecte::translation(uint16_t valeur, uint32_t tempo, GestionPatte& patte1, GestionPatte& patte2, GestionPatte& patte3, GestionPatte& patte4, GestionPatte& patte5) {
	synchronisationTranslation(patte2, patte1, tempo);
	synchronisationTranslation(patte3, patte1, tempo);
	synchronisationTranslation(patte4, patte1, tempo);
	synchronisationTranslation(patte5, patte1, tempo);
	uint16_t valRotule = patte1.getRotule().getValeur();
	if(valRotule < valeur) {
		for(int compteur = valRotule; compteur != valeur; compteur++) {
			patte1.translation(compteur);
			patte2.translation(compteur);
			patte3.translation(compteur);
			patte4.translation(compteur);
			patte5.translation(compteur);
			delayMicroseconds(tempo);
		}
	}
	if(valRotule > valeur) {
		for(int compteur = valRotule; compteur != valeur; compteur--) {
			patte1.translation(compteur);
			patte2.translation(compteur);
			patte3.translation(compteur);
			patte4.translation(compteur);
			patte5.translation(compteur);
			delayMicroseconds(tempo);
		}
	}
}

// ************************************************
// Incline six pattes		
// @Param le nombre de pas cible des servos
// @Param la tempo entre deux increments des servos
// @Param la premiere patte (maitre pour synchro)
// @Param la deuxieme patte
// @Param la troisieme patte
// @Param la quatrieme patte
// @Param la cinquieme patte
// @Param la sixieme patte
// ************************************************
void GestionInsecte::translation(uint16_t valeur, uint32_t tempo, GestionPatte& patte1, GestionPatte& patte2, GestionPatte& patte3, GestionPatte& patte4, GestionPatte& patte5, GestionPatte& patte6) {
	synchronisationTranslation(patte2, patte1, tempo);
	synchronisationTranslation(patte3, patte1, tempo);
	synchronisationTranslation(patte4, patte1, tempo);
	synchronisationTranslation(patte5, patte1, tempo);
	synchronisationTranslation(patte6, patte1, tempo);
	uint16_t valRotule = patte1.getRotule().getValeur();
	if(valRotule < valeur) {
		for(int compteur = valRotule; compteur != valeur; compteur++) {
			patte1.translation(compteur);
			patte2.translation(compteur);
			patte3.translation(compteur);
			patte4.translation(compteur);
			patte5.translation(compteur);
			patte6.translation(compteur);
			delayMicroseconds(tempo);
		}
	}
	if(valRotule > valeur) {
		for(int compteur = valRotule; compteur != valeur; compteur--) {
			patte1.translation(compteur);
			patte2.translation(compteur);
			patte3.translation(compteur);
			patte4.translation(compteur);
			patte5.translation(compteur);
			patte6.translation(compteur);
			delayMicroseconds(tempo);
		}
	}
}

// ************************************************
// tourne une pattes		
// @Param le nombre de pas cible du servo
// @Param la tempo entre deux increments des servos
// @Param la premiere patte
// ************************************************
void GestionInsecte::rotation(uint16_t valeur, uint32_t tempo, GestionPatte& patte1) {
	uint16_t valBassin = patte1.getBassin().getValeur();
	if(valBassin < valeur) {
		for(int compteur = valBassin; compteur != valeur; compteur++) {
			patte1.rotation(compteur);
			delayMicroseconds(tempo);
		}
	}
	if(valBassin > valeur) {
		for(int compteur = valBassin; compteur != valeur; compteur--) {
			patte1.rotation(compteur);
			delayMicroseconds(tempo);
		}
	}
}

// ************************************************
// tourne deux pattes		
// @Param le nombre de pas cible des servos
// @Param la tempo entre deux increments des servos
// @Param la premiere patte (maitre pour synchro)
// @Param la deuxieme patte
// ************************************************
void GestionInsecte::rotation(uint16_t valeur, uint32_t tempo, GestionPatte& patte1, GestionPatte& patte2) {
	synchronisationRotation(patte2, patte1, tempo);
	uint16_t valBassin = patte1.getBassin().getValeur();
	if(valBassin < valeur) {
		for(int compteur = valBassin; compteur != valeur; compteur++) {
			patte1.rotation(compteur);
			patte2.rotation(compteur);
			delayMicroseconds(tempo);
		}
	}
	if(valBassin > valeur) {
		for(int compteur = valBassin; compteur != valeur; compteur--) {
			patte1.rotation(compteur);
			patte2.rotation(compteur);
			delayMicroseconds(tempo);
		}
	}
}

// ************************************************
// tourne trois pattes		
// @Param le nombre de pas cible des servos
// @Param la tempo entre deux increments des servos
// @Param la premiere patte (maitre pour synchro)
// @Param la deuxieme patte
// @Param la troisieme patte
// ************************************************
void GestionInsecte::rotation(uint16_t valeur, uint32_t tempo, GestionPatte& patte1, GestionPatte& patte2, GestionPatte& patte3) {
	synchronisationRotation(patte2, patte1, tempo);
	synchronisationRotation(patte3, patte1, tempo);
	uint16_t valBassin = patte1.getBassin().getValeur();
	if(valBassin < valeur) {
		for(int compteur = valBassin; compteur != valeur; compteur++) {
			patte1.rotation(compteur);
			patte2.rotation(compteur);
			patte3.rotation(compteur);
			delayMicroseconds(tempo);
		}
	}
	if(valBassin > valeur) {
		for(int compteur = valBassin; compteur != valeur; compteur--) {
			patte1.rotation(compteur);
			patte2.rotation(compteur);
			patte3.rotation(compteur);
			delayMicroseconds(tempo);
		}
	}
}

// ************************************************
// tourne quatre pattes		
// @Param le nombre de pas cible des servos
// @Param la tempo entre deux increments des servos
// @Param la premiere patte (maitre pour synchro)
// @Param la deuxieme patte
// @Param la troisieme patte
// @Param la quatrieme patte
// ************************************************
void GestionInsecte::rotation(uint16_t valeur, uint32_t tempo, GestionPatte& patte1, GestionPatte& patte2, GestionPatte& patte3, GestionPatte& patte4) {
	synchronisationRotation(patte2, patte1, tempo);
	synchronisationRotation(patte3, patte1, tempo);
	synchronisationRotation(patte4, patte1, tempo);
	uint16_t valBassin = patte1.getBassin().getValeur();
	if(valBassin < valeur) {
		for(int compteur = valBassin; compteur != valeur; compteur++) {
			patte1.rotation(compteur);
			patte2.rotation(compteur);
			patte3.rotation(compteur);
			patte4.rotation(compteur);
			delayMicroseconds(tempo);
		}
	}
	if(valBassin > valeur) {
		for(int compteur = valBassin; compteur != valeur; compteur--) {
			patte1.rotation(compteur);
			patte2.rotation(compteur);
			patte3.rotation(compteur);
			patte4.rotation(compteur);
			delayMicroseconds(tempo);
		}
	}
}

// ************************************************
// tourne cinq pattes		
// @Param le nombre de pas cible des servos
// @Param la tempo entre deux increments des servos
// @Param la premiere patte (maitre pour synchro)
// @Param la deuxieme patte
// @Param la troisieme patte
// @Param la quatrieme patte
// @Param la cinquieme patte
// ************************************************
void GestionInsecte::rotation(uint16_t valeur, uint32_t tempo, GestionPatte& patte1, GestionPatte& patte2, GestionPatte& patte3, GestionPatte& patte4, GestionPatte& patte5) {
	synchronisationRotation(patte2, patte1, tempo);
	synchronisationRotation(patte3, patte1, tempo);
	synchronisationRotation(patte4, patte1, tempo);
	synchronisationRotation(patte5, patte1, tempo);
	uint16_t valBassin = patte1.getBassin().getValeur();
	if(valBassin < valeur) {
		for(int compteur = valBassin; compteur != valeur; compteur++) {
			patte1.rotation(compteur);
			patte2.rotation(compteur);
			patte3.rotation(compteur);
			patte4.rotation(compteur);
			patte5.rotation(compteur);
			delayMicroseconds(tempo);
		}
	}
	if(valBassin > valeur) {
		for(int compteur = valBassin; compteur != valeur; compteur--) {
			patte1.rotation(compteur);
			patte2.rotation(compteur);
			patte3.rotation(compteur);
			patte4.rotation(compteur);
			patte5.rotation(compteur);
			delayMicroseconds(tempo);
		}
	}
}

// ************************************************
// tourne six pattes		
// @Param le nombre de pas cible des servos
// @Param la tempo entre deux increments des servos
// @Param la premiere patte (maitre pour synchro)
// @Param la deuxieme patte
// @Param la troisieme patte
// @Param la quatrieme patte
// @Param la cinquieme patte
// @Param la sixieme patte
// ************************************************
void GestionInsecte::rotation(uint16_t valeur, uint32_t tempo, GestionPatte& patte1, GestionPatte& patte2, GestionPatte& patte3, GestionPatte& patte4, GestionPatte& patte5, GestionPatte& patte6) {
	synchronisationRotation(patte2, patte1, tempo);
	synchronisationRotation(patte3, patte1, tempo);
	synchronisationRotation(patte4, patte1, tempo);
	synchronisationRotation(patte5, patte1, tempo);
	synchronisationRotation(patte6, patte1, tempo);
	uint16_t valBassin = patte1.getBassin().getValeur();
	if(valBassin < valeur) {
		for(int compteur = valBassin; compteur != valeur; compteur++) {
			patte1.rotation(compteur);
			patte2.rotation(compteur);
			patte3.rotation(compteur);
			patte4.rotation(compteur);
			patte5.rotation(compteur);
			patte6.rotation(compteur);
			delayMicroseconds(tempo);
		}
	}
	if(valBassin > valeur) {
		for(int compteur = valBassin; compteur != valeur; compteur--) {
			patte1.rotation(compteur);
			patte2.rotation(compteur);
			patte3.rotation(compteur);
			patte4.rotation(compteur);
			patte5.rotation(compteur);
			patte6.rotation(compteur);
			delayMicroseconds(tempo);
		}
	}
}

// ************************************
// Getter du controleur gauche
// @Return reference sur control gauche
// ************************************
GestionINA219& GestionInsecte::getControlLeft(void){
	return controlLeft;
}
		
// ***********************************
// Getter du controleur droit
// @Return reference sur control droit
// ***********************************
GestionINA219& GestionInsecte::getControlRight(void) {
	return controlRight;
}
	
// ****************************************
// Getter de la patte avant gauche
// @Return reference sur patte avant gauche
// ****************************************
GestionPatte& GestionInsecte::getPatteFrontLeft(void) {
	return patteFrontLeft;
}
		
// *****************************************
// Getter de la patte milieu gauche
// @Return reference sur patte milieu gauche
// *****************************************
GestionPatte& GestionInsecte::getPatteMiddleLeft(void) {
	return patteMiddleLeft;
}
		
// ******************************************
// Getter de la patte arriere gauche
// @Return reference sur patte arriere gauche
// ******************************************
GestionPatte& GestionInsecte::getPatteRearLeft(void) {
	return patteRearLeft;
}
		
// ****************************************
// Getter de la patte avant droite
// @Return reference sur patte avant droite
// ****************************************
GestionPatte& GestionInsecte::getPatteFrontRight(void) {
	return patteFrontRight;
}
		
// *****************************************
// Getter de la patte milieu droite
// @Return reference sur patte milieu droite
// *****************************************
GestionPatte& GestionInsecte::getPatteMiddleRight(void) {
	return patteMiddleRight;
}
		
// ******************************************
// Getter de la patte arriere droite
// @Return reference sur patte arriere droite
// ******************************************
GestionPatte& GestionInsecte::getPatteRearRight(void) {
	return patteRearRight;
}

// ************************************************************
// Getter de la LED RGB d'indication de tension gauche
// @Return reference sur LED RGB d'indication de tension gauche
// ************************************************************
GestionLedRGBPCA9685& GestionInsecte::getTensionLeft(void) {
	return tensionLeft;
}

// ************************************************************
// Getter de la LED RGB d'indication de courant gauche
// @Return reference sur LED RGB d'indication de courant gauche
// ************************************************************
GestionLedRGBPCA9685& GestionInsecte::getCurrentLeft(void) {
	return currentLeft;
}

// ************************************************************
// Getter de la LED RGB d'indication de tension droite
// @Return reference sur LED RGB d'indication de tension droite
// ************************************************************
GestionLedRGBPCA9685& GestionInsecte::getTensionRight(void) {
	return tensionRight;
}

// ***********************************************************
// Getter de la LED RGB d'indication de courant droit
// @Return reference sur LED RGB d'indication de courant droit
// ***********************************************************
GestionLedRGBPCA9685& GestionInsecte::getCurrentRight(void) {
	return currentRight;
}

// ***********
// Destructeur
// ***********
GestionInsecte::~GestionInsecte() {
}
