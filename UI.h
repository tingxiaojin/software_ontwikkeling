//--------------------------------------------------------------
// File     : main.h
//--------------------------------------------------------------

//--------------------------------------------------------------
#ifndef __UI_H
#define __UI_H

//--------------------------------------------------------------
// Includes
//--------------------------------------------------------------
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TRUE  1
#define FALSE 0

#define EMPTY 0

#define CR	0x0D
#define ST 	'\0'

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

//#define PARAM1		0
//#define PARAM2		1
//#define PARAM3		2
//#define PARAM4		3
//#define PARAM5		4
//#define PARAM6		5
//#define PARAM7		6

#define STR_EMPTY				0

//--------------------------------------------------------------
// Structures
//--------------------------------------------------------------
typedef struct
{
	int functie;

	int startx;
	int startx2;
	int startx3;
	int startx4;
	int startx5;
	int startx6;

	int starty;
	int starty2;
	int starty3;
	int starty4;
	int starty5;
	int starty6;

	int eindx;
	int eindy;
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



extern int  LL_exe		(FUNCTIE* input);
extern void UI_ERR_put	(int error);
extern void UI_CH_rm	(char* buffer, char c, char rm);
extern void UI_CH_rp	(char* buffer, char old_char, char new_char);
extern int  UI_PARAMCNT (char* buffer, char sep);


//--------------------------------------------------------------
#endif
