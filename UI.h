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

#define CR	0x0D

enum
{
	LIJN=0,
	RECHTHOEK,
	TEKST,
	BITMAP,
	CLEARSCHERM,
	WACHT,
	FIGUUR
};

enum
{
	PARAM1 = 0,
	PARAM2,
	PARAM3,
	PARAM4,
	PARAM5,
	PARAM6,
	PARAM7
};
//#define PARAM1		0
//#define PARAM2		1
//#define PARAM3		2
//#define PARAM4		3
//#define PARAM5		4
//#define PARAM6		5
//#define PARAM7		6

#define  VGA_COL_BLACK          0  //0x00
#define  VGA_COL_BLUE           1  //0x01
#define  VGA_COL_LIGHTBLUE      11 //0x0B
#define  VGA_COL_GREEN          28 //0x1C
#define  VGA_COL_LIGHTGREEN     92 //0x3C
#define  VGA_COL_CYAN           31 //0x1F
#define  VGA_COL_LIGHTCYAN      127//0x7F
#define  VGA_COL_RED            96 //0x60
#define  VGA_COL_LIGHTRED       224//0xE0
#define  VGA_COL_MAGENTA        131//0x83
#define  VGA_COL_LIGHTMAGENTA   227//0xE3
#define  VGA_COL_BROWN			101//133//137//105//69 //0x45
#define  VGA_COL_YELLOW         252//0xFC
#define  VGA_COL_GREY			72//108//112
#define  VGA_COL_WHITE          255//0xFF

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

	int starty;
	int starty2;
	int starty3;
	int starty4;
	int starty5;
	int eindx;
	int eindy;
	int breedte;
	int hoogte;
	int nr;
	int achtergrond;
	char* kleur;
	int dikte;
	int gevuld;
	int fontgrootte;
	char* fontstyle;
	char* tekst;
	char* font;
	int ms;
}FUNCTIE;



extern int  LL_exe		(FUNCTIE* input);
extern void UI_ERR_put	(int error);
extern void UI_CH_rm	(char* buffer, char c);
extern void UI_CH_rp	(char* buffer, char old_char, char new_char);


//--------------------------------------------------------------
#endif
