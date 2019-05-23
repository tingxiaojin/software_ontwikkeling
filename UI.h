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

#define LIJN 		0
#define RECHTHOEK 	1
#define TEKST	 	2
#define BITMAP		3
#define CLEARSCHERM 4

#define PARAM1		0
#define PARAM2		1
#define PARAM3		2
#define PARAM4		3
#define PARAM5		4
#define PARAM6		5
#define PARAM7		6

#define  VGA_COL_BLACK          0x00
#define  VGA_COL_BLUE           0x03
#define  VGA_COL_GREEN          0x1C
#define  VGA_COL_RED            0xE0
#define  VGA_COL_WHITE          0xFF

#define  VGA_COL_CYAN           0x1F
#define  VGA_COL_MAGENTA        0xE3
#define  VGA_COL_YELLOW         0xFC

#define STR_EMPTY				0

//--------------------------------------------------------------
// Structures
//--------------------------------------------------------------
typedef struct
{
	int functie;
	int startx;
	int starty;
	int eindx;
	int eindy;
	int breedte;
	int hoogte;
	int nr;
	int achtergrond;
	int kleur;
	int dikte;
	int gevuld;
	int fontgrootte;
	char* fontstyle;
	char* tekst;
	char* font;
}FUNCTIE;

extern int  LL_exe		(FUNCTIE* input);
extern void UI_ERR_put	(int error);
extern void UI_CH_rm	(char* buffer, char c);
extern void UI_CH_rp	(char* buffer, char old_char, char new_char);


//--------------------------------------------------------------
#endif
