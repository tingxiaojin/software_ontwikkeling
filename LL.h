/**
  ******************************************************************************
  * @file    LL.h
  * @author  SOFT_ONT groep 7
  * @version V1.0.3
  * @date    29-5-2019
  * @brief   Dit bestand bevat alle functie-prototypes voor de Logic Layer.
  */

// Voorkom meerdere inclusions
#ifndef __LL_H
#define __LL_H


//--------------------------------------------------------------
// Includes
//--------------------------------------------------------------
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define FALSE 0
#define TRUE  1

//--------------------------------------------------------------
// Structures
//--------------------------------------------------------------
/*
 * @brief: LL sturctiore module
 */
typedef struct
{
	int functie;  	/*!< Functienaam (LIJN, RECHTHOEK, etc.) */

	int startx; 	/*!< Start X-waarde van elk object, functie figuur vereist meerdere start X-waardes*/
	int startx2;
	int startx3;
	int startx4;
	int startx5;
	int startx6;

	int starty;		/*!< Start Y-waarde van elk object, functie figuur vereist meerdere start Y-waardes*/
	int starty2;
	int starty3;
	int starty4;
	int starty5;
	int starty6;

	int eindx;		/*!< Einde X-waardes*/
	int eindy;		/*!< Einde Y-waardes*/
	int breedte;
	int hoogte;
	int nr;
	int achtergrond;

	char* kleur;
	int   dikte;
	int   gevuld;
	int   fontgrootte;
	char  fontstijl;
	char* tekst;
	char* font;
	int   ms;
	int   parameters;
}FUNCTIE;

enum
{
	LIJN=0,
	RECHTHOEK,
	TEKST,
	BITMAP,
	CLEARSCHERM,
	WACHT,
	FIGUUR,
	NLFLAG,
	ITFLAG,
	TOREN
};

enum PARAM
{
	PARAM0 = 0,
	PARAM1,
	PARAM2,
	PARAM3,
	PARAM4,
	PARAM5,
	PARAM6,
	PARAM7,
	PARAM8,
	PARAM9,
	PARAM10,
	PARAM11,
	PARAM12,
	PARAM13
};



extern int 	 LL_FIG_exe		 (FUNCTIE* input);
extern void  LL_FIG_init	 (char* buffer, FUNCTIE* input, int vorm);
extern int 	 LL_STRING_kstoki(char* skleur);
extern int   LL_STRING_check (char* buffer, char* figuur);
extern char* LL_STRING_param (char* buffer, int paramnum);

#endif
