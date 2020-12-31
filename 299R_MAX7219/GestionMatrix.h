/**************************************************************************
 *   \file    GestionMatrix.h
 *   \brief   Entete de la classe de gestion des matrices à base de MAX7219.
 *   \author  Totof (raspberry.pi123@orange.fr)
 *   \version 1.0
 *   \date    29/12/2020
 **************************************************************************/
 
#ifndef GESTIONMATRIX_H_
#define GESTIONMATRIX_H_

#include <stdint.h>
#include "GestionMAX7219.h"

class GestionMatrix : GestionMAX7219 {
	public:
		GestionMatrix(bool);
		
		void horloge(uint8_t, uint8_t, uint8_t, uint8_t); 

		virtual ~GestionMatrix();
		
	private:
		void initMatrix(bool);
		
		uint8_t segment(uint8_t, uint8_t);
		uint8_t segmentDp(uint8_t, uint8_t);
		uint8_t segmentDm(uint8_t, uint8_t);
};

#endif