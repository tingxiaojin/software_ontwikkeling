/**
  ******************************************************************************
  * @file    API_DRAW.c
  * @author  SOFTONT groep 7
  * @version V1.0.0
  * @date    29-05-2019
  * @brief   Deze file bezit alle drawfuncties die mogelijk zijn in deze .lib
  * 		 Er is een error handling in die aangeeft of de argumenten buiten
  * 		 het scherm zitten.
  *
  ******************************************************************************
  * @attention
  *	De volgende functies komen aanbod:
  *	API_draw_line
  *	API_draw_rectangle
  *	API_draw_clearscreen
  *	API_draw_text
  *	API_draw_bitmap
  *
  *
  * error values:
  * 0: alles verliep zoals gepland
  * 1: verkeerde x-waarde ingevoerd
  * 2: verkeerde y-waarde ingevoerd
  * 3: beide x, als y-waardes zijn verkeerd ingevoerd
  * 4: omvang is te groot
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "includes.h"
#include "API_IO.h"

// Load .bmp files
#include "pijl_links.h"
#include "pijl_rechts.h"
#include "pijl_omhoog.h"
#include "pijl_omlaag.h"
#include "smiley_blij.h"
#include "smiley_boos.h"

/** @addtogroup API
  * @{
  */

/** @addtogroup API_DRAW
  * @brief Tekenfuncties
  * @{
  */

/** @addtogroup DRAW_functies
  * @brief   De functies die iets kunnen tekenen op het scherm
  * @{
  */

/**
  * @brief  Deze functie kan een lijn tekenen.
  * @note   Deze functie is vanuit de LL aangeroepen. Deze functie zal een lijn tekenen
  * 		en kijkt doormiddel van error handling of de lijn in het bereik van het
  * 		scherm zit.
  * @param  x_1: Dit argument geeft de x-waarde van het beginpunt. Als deze buiten het scherm valt
  * 			 zit returnt hij een error.
  * @param  y_1: Dit argument geeft de y-waarde van het beginpunt. Als deze buiten het scherm valt
  * 			 zit returnt hij een error.
  * @param  x_2: Dit argument geeft de x-waarde van het eindpunt. Als deze buiten het scherm valt
  * 			 zit returnt hij een error.
  * @param  y_2: Dit argument geeft de y-waarde van het eindpunt.Als deze buiten het scherm valt
  * 			 zit returnt hij een error.
  * @param  color: Dit argument geeft de kleur van de lijn.
  * @param  weight: Dit argument geeft de dikte van de lijn.
  * @param  reserved: Dit argument mag gebruikt worden voor extra's
  * @retval int error
  */
int API_draw_line (int x_1, int y_1, int x_2, int y_2, int color, int weight, int reserved)
{
	int error=0;
	error = API_io_ERROR_inrange(x_1, y_1, x_2, y_2);		//kijkt of de argumenten binnen het scherm vallen.
	if (error) return error;
	error = API_io_line(x_1, y_1, x_2, y_2, color, weight); //zo niet maak een lijn.
	return error;
}

/**
  * @brief  Deze functie kan een rechthoek tekenen.
  * @note   Deze functie is vanuit de LL aangeroepen. Deze functie zal een rechthoek tekenen
  * 		en kijkt doormiddel van error handling of de rechthoek in het bereik van het
  * 		scherm zit.
  * @param  x: Dit argument geeft de x-waarde van het punt linksboven. Als deze buiten het scherm valt
  * 		zit returnt hij een error.
  * @param  y: Dit argument geeft de y-waarde van het punt linksboven. Als deze buiten het scherm valt
  * 		zit returnt hij een error.
  * @param  width: Dit argument geeft de lengte van de rechthoek. Als deze buiten het scherm valt
  * 		zit returnt hij een error.
  * @param  height: Dit argument geeft de hoogte van de rechthoek.Als deze buiten het scherm valt
  * 		zit returnt hij een error.
  * @param  color: Dit argument geeft de kleur binnen in de rechthoek
  * @param  filled: Dit argument geeft aan of de rechthoek een rand moet hebben of dat die gevuld moet zijn
  * @param  weight: Dit argument geeft de dikte van de lijnen om de rand van de rechthoek aan.
  * @param  bordercolor: Dit argument geeft de kleur van de rand.
  * @retval int error
  */
int API_draw_rectangle	(int x, int y, int width, int height, int color, int filled, int weight, int bordercolor)
{
	int error=0;
	error = API_io_ERROR_inrange(x, y, x+width, y+height);
	if (error) return error;
	error = API_io_rechthoek (x, y, width, height, color, filled);
	return error;
}

/**
  * @brief  Deze functie cleared het scherm met een kleur.
  * @note   Deze functie is vanuit de LL aangeroepen. Deze functie zal het hele scherm vullen met
  * 		meegegeven kleur
  * @param  color: Dit argument geeft de kleur van het scherm
  * @retval int error
  */
int API_draw_clearscreen (int color)
{
	API_io_clearscherm(color);
	return 0;
}

/**
  * @brief  Deze functie kan tekst op het scherm schrijven
  * @note   Deze functie is vanuit de LL aangeroepen. Deze functie zal tekst op het scherm schrijven.
  * 		Als de letters voorbij de schermlengte gaan zal er een regel eronder verder gegaan worden met de tekst
  * @param  x_lup: Dit argument geeft de x-waarde coordinaat van het punt linksboven.
  * 		Als de letters voorbij de schermlengte gaan zal er een regel eronder verder gegaan worden met de tekst
  * @param  y_lup: Dit argument geeft de y-waarde coordinaat van het punt linksboven.
  * 		Als de letters voorbij de schermlengte gaan zal er een regel eronder verder gegaan worden met de tekst
  * @param  color: Dit argument geeft de kleur van de tekst
  * @param  tekst: Dit argument geeft de string van de tekst die geprint moet worden
  * @param  fontname: Dit argument geeft de naam van het font (arial, consolas)
  * @param  fontsize: Dit argument geeft de grootte van de letters(1,2)
  * @param  fontstytle: Dit argument geeft de style van de tekst(standaard, vet, cursief)
  * @param  reserved: Dit argument mag gebruikt worden voor extra's
  * @retval int error
  */
int API_draw_text(int x_lup, int y_lup, int color, char* tekst, char* fontname, int fontsize, int fontstytle, int reserved)
{
	int error;
//						(* zin, x_lup, y_lup, kleur, char* font, int fontgrootte, int fonststyle, int reserved);
	error = API_io_puts(tekst, x_lup, y_lup, color, fontname, fontsize, fontstytle, reserved);
	return error;
}


/**
  * @brief  In deze functie wordt er een bitmap gekozen en geprint op het VGA-scherm.
  * @note   Deze functie is vanuit de LL aangeroepen. Deze functie zal een bitmap op het VGA-scherm printen
  * 		De error handling geeft aan of de bitmap buiten het scherm komt.
  * @param  x_lup: Dit argument geeft de x-waarde van het punt linksboven. Als deze buiten het scherm valt
  * 			   returnt hij een error.
  * @param  y_lup: Dit argument geeft de y-waarde van het punt linksboven. Als deze buiten het scherm valt
  * 			   returnt hij een error.
  * @param  bm_nr: Dit argument geeft het volgnummer van de bitmap.
  * @param  reserved: Dit argument mag gebruikt worden voor extra's
  * @retval int error
  */
int API_draw_bitmap(int x_lup, int y_lup, int bm_nr, int reserved)
{
	int error=0;
	unsigned int breedte, hoogte;
	switch(bm_nr)
	{
	case API_IO_PIJL_LINKS:
		breedte = (unsigned int)(*(pijl_links+0)|(*(pijl_links+1)<<8)|(*(pijl_links+2)<<16)|(*(pijl_links+3)<<24));
		hoogte  = (unsigned int)(*(pijl_links+4)|(*(pijl_links+5)<<8)|(*(pijl_links+6)<<16)|(*(pijl_links+7)<<24));

		if((x_lup+breedte)>VGA_DISPLAY_X)x_lup=VGA_DISPLAY_X-breedte;
		else if((x_lup+breedte)<0)		 x_lup=0;
		if((y_lup+hoogte)>VGA_DISPLAY_Y) y_lup=VGA_DISPLAY_Y-hoogte;
		else if((y_lup+hoogte)<0)		 y_lup=0;


		API_io_bitmap(x_lup, y_lup, &pijl_links[0], reserved);
		break;
	case API_IO_PIJL_RECHTS:
		breedte = (unsigned int)(*(pijl_rechts+0)|(*(pijl_rechts+1)<<8)|(*(pijl_rechts+2)<<16)|(*(pijl_rechts+3)<<24));
		hoogte  = (unsigned int)(*(pijl_rechts+4)|(*(pijl_rechts+5)<<8)|(*(pijl_rechts+6)<<16)|(*(pijl_rechts+7)<<24));

		if((x_lup+breedte)>VGA_DISPLAY_X)x_lup=VGA_DISPLAY_X-breedte;
		else if((x_lup+breedte)<0)		 x_lup=0;
		if((y_lup+hoogte)>VGA_DISPLAY_Y) y_lup=VGA_DISPLAY_Y-hoogte;
		else if((y_lup+hoogte)<0)		 y_lup=0;

		API_io_bitmap(x_lup, y_lup, &pijl_rechts[0], reserved);
		break;
	case API_IO_PIJL_OMHOOG:
		breedte = (unsigned int)(*(pijl_omhoog+0)|(*(pijl_omhoog+1)<<8)|(*(pijl_omhoog+2)<<16)|(*(pijl_omhoog+3)<<24));
		hoogte  = (unsigned int)(*(pijl_omhoog+4)|(*(pijl_omhoog+5)<<8)|(*(pijl_omhoog+6)<<16)|(*(pijl_omhoog+7)<<24));

		if((x_lup+breedte)>VGA_DISPLAY_X)x_lup=VGA_DISPLAY_X-breedte;
		else if((x_lup+breedte)<0)		 x_lup=0;
		if((y_lup+hoogte)>VGA_DISPLAY_Y) y_lup=VGA_DISPLAY_Y-hoogte;
		else if((y_lup+hoogte)<0)		 y_lup=0;

		API_io_bitmap(x_lup, y_lup, &pijl_omhoog[0], reserved);
		break;
	case API_IO_PIJL_OMLAAG:
		breedte = (unsigned int)(*(pijl_omlaag+0)|(*(pijl_omlaag+1)<<8)|(*(pijl_omlaag+2)<<16)|(*(pijl_omlaag+3)<<24));
		hoogte  = (unsigned int)(*(pijl_omlaag+4)|(*(pijl_omlaag+5)<<8)|(*(pijl_omlaag+6)<<16)|(*(pijl_omlaag+7)<<24));

		if((x_lup+breedte)>VGA_DISPLAY_X)x_lup=VGA_DISPLAY_X-breedte;
		else if((x_lup+breedte)<0)		 x_lup=0;
		if((y_lup+hoogte)>VGA_DISPLAY_Y) y_lup=VGA_DISPLAY_Y-hoogte;
		else if((y_lup+hoogte)<0)		 y_lup=0;

		API_io_bitmap(x_lup, y_lup, &pijl_omlaag[0], reserved);
		break;
	case API_IO_SMILY_BLIJ:
		breedte = (unsigned int)(*(smiley_blij+0)|(*(smiley_blij+1)<<8)|(*(smiley_blij+2)<<16)|(*(smiley_blij+3)<<24));
		hoogte  = (unsigned int)(*(smiley_blij+4)|(*(smiley_blij+5)<<8)|(*(smiley_blij+6)<<16)|(*(smiley_blij+7)<<24));

		if((x_lup+breedte)>VGA_DISPLAY_X)x_lup=VGA_DISPLAY_X-breedte;
		else if((x_lup+breedte)<0)		 x_lup=0;
		if((y_lup+hoogte)>VGA_DISPLAY_Y) y_lup=VGA_DISPLAY_Y-hoogte;
		else if((y_lup+hoogte)<0)		 y_lup=0;

		API_io_bitmap(x_lup, y_lup, &smiley_blij[0], reserved);
		break;
	case API_IO_SMILY_BOOS:
		breedte = (unsigned int)(*(smiley_boos+0)|(*(smiley_boos+1)<<8)|(*(smiley_boos+2)<<16)|(*(smiley_boos+3)<<24));
		hoogte  = (unsigned int)(*(smiley_boos+4)|(*(smiley_boos+5)<<8)|(*(smiley_boos+6)<<16)|(*(smiley_boos+7)<<24));

		if((x_lup+breedte)>VGA_DISPLAY_X)x_lup=VGA_DISPLAY_X-breedte;
		else if((x_lup+breedte)<0)		 x_lup=0;
		if((y_lup+hoogte)>VGA_DISPLAY_Y) y_lup=VGA_DISPLAY_Y-hoogte;
		else if((y_lup+hoogte)<0)		 y_lup=0;

		API_io_bitmap(x_lup, y_lup, &smiley_boos[0], reserved);
		break;

	default: error=INPUTERROR;
	}
	return error;
}
/**
  * @}
  */
/**
  * @}
  */
/**
  * @}
  */
