/**
  ******************************************************************************
  * @file    API_DRAW.h
  * @author  SOFT_ONT groep 7
  * @version V1.0.2
  * @date    29-05-2019
  * @brief   Deze file is de library van de API_DRAW.c. Hierin staan alle
  * 		 functies die aangeroepen kunnen worden in de API_DRAW.c.
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
#ifndef API_DRAW_H
#define API_DRAW_H

/**
  * @addtogroup  API_DRAW
  * @brief functions and errorhandling
  * @{
  */


/**
  * @ingroup  UI_error
  * @brief functions and errorhandling
  * @{
  */

/**
  * @addtogroup error_waardes
  * @brief functions and errorhandling
  * @{
  */

enum
{
	FOUTX =1,		/*!< x-waarde te groot */
	FOUTY,			/*!< y-waarde te groot */
	FOUTOMVANG,		/*!< Zowel x- als y-waarde te groot*/
	INPUTERROR,		/*!< Input is invalide */
	STR_LEEG,		/*!< Lege string gedetecteerd*/
	TOOLITTLEPARAM	/*!< Te weinig parameters gedetecteerd*/
};


/**
  * @}
  * @}
  * @}
  */

/* Deze functie kan een lijn tekenen op het VGA-scherm*/
extern int API_draw_line		(int x_1, int y_1, int x_2, int y_2, int color, int weight, int reserved);
/* Deze functie kan een rechthoek tekenen op het VGA-scherm*/
extern int API_draw_rectangle	(int x, int y, int width, int height, int color, int filled, int weight, int bordercolor);
/* Deze functie kan de kleur op het VGA-scherm veranderen*/
extern int API_draw_clearscreen (int color);
/* Deze functie kan tekst schrijven op het VGA-scherm*/
extern int API_draw_text		(int x_lup, int y_lup, int color, char* tekst, char* fontname, int fontsize, int fontstytle, int reserved);
/* Deze functie kan een bitmap tekenen op het VGA-scherm*/
extern int API_draw_bitmap		(int x_lup, int y_lup, int bm_nr, int reserved);

#endif/*__API_DRAW_H */

