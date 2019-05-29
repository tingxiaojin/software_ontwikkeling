#include "includes.h"
//#include "API_IO.h"

// Load .bmp files
#include "pijl_links.h"
#include "pijl_rechts.h"
#include "pijl_omhoog.h"
#include "pijl_omlaag.h"
#include "smiley_blij.h"
#include "smiley_boos.h"

/*
 * error values:
 * 0: alles verliep zoals gepland
 * 1: verkeerde x-waarde ingevoerd
 * 2: verkeerde y-waarde ingevoerd
 * 3: beide x, als y-waardes zijn verkeerd ingevoerd
 * 4: omvang is te groot
 */




///////////////////////////////////////////
 // figuren
//////////////////////////////////////////
int API_draw_line (int x_1, int y_1, int x_2, int y_2, int color, int weight, int reserved)
{
	int error=0;
	error = API_io_ERROR_inrange(x_1, y_1, x_2, y_2);
	if (error) return error;
	error = API_io_line(x_1, y_1, x_2, y_2, color, weight);
	return error;
}

int API_draw_rectangle	(int x, int y, int width, int height, int color, int filled, int weight, int bordercolor)
{
	int error=0;
	error = API_io_ERROR_inrange(x, y, x+width, y+height);
	if (error) return error;
	error = API_io_rechthoek (x, y, width, height, color, filled);
	return error;
}

int API_draw_clearscreen (int color)
{
	API_io_clearscherm(color);
	return 0;
}


///////////////////////////////////////////
 // tekst
//////////////////////////////////////////
int API_draw_text(int x_lup, int y_lup, int color, char* tekst, char* fontname, int fontsize, int fontstyle, int reserved)
{
	int error;
//						(* zin, x_lup, y_lup, kleur, char* font, int fontgrootte, int fonststyle, int reserved);
	error = API_io_puts(tekst, x_lup, y_lup, color, fontname, fontsize, fontstyle, reserved);
	return error;
}


///////////////////////////////////////////
 // bitmap
//////////////////////////////////////////
int API_draw_bitmap(int x_lup, int y_lup, int bm_nr, int reserved)
{
	int error=0;
	unsigned int breedte, hoogte;
	switch(bm_nr)
	{
	case API_IO_PIJL_LINKS:
		breedte = (unsigned int)(*(pijl_links+0)|(*(pijl_links+1)<<8)|(*(pijl_links+2)<<16)|(*(pijl_links+3)<<32));
		hoogte  = (unsigned int)(*(pijl_links+4)|(*(pijl_links+5)<<8)|(*(pijl_links+6)<<16)|(*(pijl_links+7)<<32));

		if((x_lup+breedte)>VGA_DISPLAY_X)x_lup=VGA_DISPLAY_X-breedte;
		else if((x_lup+breedte)<0)		 x_lup=0;
		if((y_lup+hoogte)>VGA_DISPLAY_Y) y_lup=VGA_DISPLAY_Y-hoogte;
		else if((y_lup+hoogte)<0)		 y_lup=0;


		API_io_bitmap(x_lup, y_lup, &pijl_links[0], reserved);
		break;
	case API_IO_PIJL_RECHTS:
		breedte = (unsigned int)(*(pijl_rechts+0)|(*(pijl_rechts+1)<<8)|(*(pijl_rechts+2)<<16)|(*(pijl_rechts+3)<<32));
		hoogte  = (unsigned int)(*(pijl_rechts+4)|(*(pijl_rechts+5)<<8)|(*(pijl_rechts+6)<<16)|(*(pijl_rechts+7)<<32));

		if((x_lup+breedte)>VGA_DISPLAY_X)x_lup=VGA_DISPLAY_X-breedte;
		else if((x_lup+breedte)<0)		 x_lup=0;
		if((y_lup+hoogte)>VGA_DISPLAY_Y) y_lup=VGA_DISPLAY_Y-hoogte;
		else if((y_lup+hoogte)<0)		 y_lup=0;

		API_io_bitmap(x_lup, y_lup, &pijl_rechts[0], reserved);
		break;
	case API_IO_PIJL_OMHOOG:
		breedte = (unsigned int)(*(pijl_omhoog+0)|(*(pijl_omhoog+1)<<8)|(*(pijl_omhoog+2)<<16)|(*(pijl_omhoog+3)<<32));
		hoogte  = (unsigned int)(*(pijl_omhoog+4)|(*(pijl_omhoog+5)<<8)|(*(pijl_omhoog+6)<<16)|(*(pijl_omhoog+7)<<32));

		if((x_lup+breedte)>VGA_DISPLAY_X)x_lup=VGA_DISPLAY_X-breedte;
		else if((x_lup+breedte)<0)		 x_lup=0;
		if((y_lup+hoogte)>VGA_DISPLAY_Y) y_lup=VGA_DISPLAY_Y-hoogte;
		else if((y_lup+hoogte)<0)		 y_lup=0;

		API_io_bitmap(x_lup, y_lup, &pijl_omhoog[0], reserved);
		break;
	case API_IO_PIJL_OMLAAG:
		breedte = (unsigned int)(*(pijl_omlaag+0)|(*(pijl_omlaag+1)<<8)|(*(pijl_omlaag+2)<<16)|(*(pijl_omlaag+3)<<32));
		hoogte  = (unsigned int)(*(pijl_omlaag+4)|(*(pijl_omlaag+5)<<8)|(*(pijl_omlaag+6)<<16)|(*(pijl_omlaag+7)<<32));

		if((x_lup+breedte)>VGA_DISPLAY_X)x_lup=VGA_DISPLAY_X-breedte;
		else if((x_lup+breedte)<0)		 x_lup=0;
		if((y_lup+hoogte)>VGA_DISPLAY_Y) y_lup=VGA_DISPLAY_Y-hoogte;
		else if((y_lup+hoogte)<0)		 y_lup=0;

		API_io_bitmap(x_lup, y_lup, &pijl_omlaag[0], reserved);
		break;
	case API_IO_SMILY_BLIJ:
		breedte = (unsigned int)(*(smiley_blij+0)|(*(smiley_blij+1)<<8)|(*(smiley_blij+2)<<16)|(*(smiley_blij+3)<<32));
		hoogte  = (unsigned int)(*(smiley_blij+4)|(*(smiley_blij+5)<<8)|(*(smiley_blij+6)<<16)|(*(smiley_blij+7)<<32));

		if((x_lup+breedte)>VGA_DISPLAY_X)x_lup=VGA_DISPLAY_X-breedte;
		else if((x_lup+breedte)<0)		 x_lup=0;
		if((y_lup+hoogte)>VGA_DISPLAY_Y) y_lup=VGA_DISPLAY_Y-hoogte;
		else if((y_lup+hoogte)<0)		 y_lup=0;

		API_io_bitmap(x_lup, y_lup, &smiley_blij[0], reserved);
		break;
	case API_IO_SMILY_BOOS:
		breedte = (unsigned int)(*(smiley_boos+0)|(*(smiley_boos+1)<<8)|(*(smiley_boos+2)<<16)|(*(smiley_boos+3)<<32));
		hoogte  = (unsigned int)(*(smiley_boos+4)|(*(smiley_boos+5)<<8)|(*(smiley_boos+6)<<16)|(*(smiley_boos+7)<<32));

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
