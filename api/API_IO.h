/**
  ******************************************************************************
  * @file    API_IO.h
  * @author  SOFT_ONT groep 7
  * @version V1.0.3
  * @date    29-05-2019
  * @brief   Deze file is de library van de API_IO.c. Hierin
  * 		 staan alle functie die gebruikt worden om de het figuur
  * 		 hardwarematig te putten op het scherm
  ******************************************************************************
  * @attention
  *
  * De volgende figuren kunnen getekend worden:
  * - lijn
  * - rechthoek
  * - clearscreen
  * - tekst
  * - emojie bitmaps (pijl 4 richtingen, smiley blij, smiley boos)
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __API_IO_H
#define __API_IO_H


//--------------------------------------------------------------
// Includes
//--------------------------------------------------------------

/** @addtogroup API
  * @{
  */

/** @defgroup API_IO
 *  @brief I/O functions en colors
 *  @{
 */

//--------------------------------------------------------------
// Defines
//--------------------------------------------------------------
/** @defgroup API_IO_COLORS
  * @{
  */
#define  VGA_COL_BLACK          0  //0x00
#define  VGA_COL_BLUE           3  //0x01
#define  VGA_COL_LIGHTBLUE      0xBB //0x0B
#define  VGA_COL_DEEPSKYBLUE    0x17 //0x0B
#define  VGA_COL_GREEN			0x10
#define  VGA_COL_LIGHTGREEN     0x1C//0x3C
#define  VGA_COL_CYAN           0x1F //0x1F
#define  VGA_COL_LIGHTCYAN      0xEF//0x7F
#define  VGA_COL_RED            0xE0 //0x60
#define  VGA_COL_LIGHTRED       0xED//0xE0
#define  VGA_COL_MAGENTA        0xE3//0x83
#define  VGA_COL_LIGHTMAGENTA   0xF3//0xE3
#define  VGA_COL_BROWN			0xA4//133//137//105//69 //0x45
#define  VGA_COL_YELLOW         0xFC//0xFC
#define  VGA_COL_PINK         	0xEE//0xFC
#define  VGA_COL_PURPLE        	0x82//0xFC
#define  VGA_COL_GREY			0x92//108//112
#define  VGA_COL_WHITE          0xFF
/**
  * @}
  */

/** @defgroup Exported functions
  * @{
  */

/* Exported macro ------------------------------------------------------------*/
/* Functies voor het initializeren van de UART, VGA-scherm en de klok */
extern void  API_io_init		  	(void);
extern void  API_io_UART_INT_init	(void);

/* Functie error detectie. Hier wordt er gekekeken of het figuur buiten het beeld valt */
extern int   API_io_ERROR_inrange	(int startx, int starty, int eindx, int eindy);

/* Functies voor het maken van een delay in het programma */
extern void  API_io_DELAY_us		(unsigned int x);
extern void  API_io_DELAY_ms			(unsigned int x);
extern void  API_io_DELAY_s 		(unsigned int x);

/* Functies voor het ophalen van het commando*/
extern void  API_io_UART_INT_gets	(char* buffer);
extern void  API_io_UART_gets  		(char* buffer);
extern char  API_io_UART_get   		(void);

/* Functies voor het printen op de terminal*/
extern void  API_io_UART_puts  		(char* buffer);
extern void  API_io_UART_putchar	(char  c);
extern void  API_io_UART_putint		(int   num);
extern void  API_io_UART_putnum		(unsigned int num, unsigned char deel);

/* Functies voor het bewerking van strings*/
extern void  API_io_rp_c			(char* buffer, char old_char, char new_char);
extern void  API_io_rm_c_ut			(char* buffer, char c		, char stopc);
extern int 	 API_io_putc 			(int c,    int x, 	   int y,	  int kleur, int achtergrond);
extern int 	 API_io_puts 			(char* zin, int x_lup, int y_lup, int kleur, char* font, int fontgrootte, int fonststyle, int reserved);

/* Functies voor het printen op het VGA-scherm*/
extern void  API_io_bitmap	  		(int x, 	 int y, 	 unsigned char* bitmap, int background);
extern void  API_io_clearscherm		(int kleur);
extern int   API_io_line		  	(int startx, int starty, int eindx, 	 		int eindy, 		char kleur, int dikte);
extern int   API_io_rechthoek  		(int x, 	 int y, 	 int breedte, 			int hoogte, 	int kleur,  int gevuld);
/**
  * @}
  */

//--------------------------------------------------------------
#endif // __API_IO_H

/**
  * @}
  */
/**
  * @}
  */
