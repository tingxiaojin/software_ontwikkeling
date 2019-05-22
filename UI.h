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


#define  VGA_COL_BLACK          0x00
#define  VGA_COL_BLUE           0x03
#define  VGA_COL_GREEN          0x1C
#define  VGA_COL_RED            0xE0
#define  VGA_COL_WHITE          0xFF

#define  VGA_COL_CYAN           0x1F
#define  VGA_COL_MAGENTA        0xE3
#define  VGA_COL_YELLOW         0xFC

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
	int kleur;
	int dikte;
	int gevuld;
	int fontgrootte;
	char* fontstyle;
	char* tekst;
	char* font;
}FUNCTIE;

extern void LL_exe(FUNCTIE* input);
extern void UI_rm_char(char* buffer, char c);


//--------------------------------------------------------------
#endif
