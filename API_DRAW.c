#include "includes.h"
#include "API_DRAW.h"
#include "API_IO.h"

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
 // errors
//////////////////////////////////////////
int API_ERROR_inrange(int startx, int starty, int eindx, int eindy)
{
	int error=0;
	if((startx>VGA_DISPLAY_X)||(startx<0)||(eindx>VGA_DISPLAY_X)||(eindx<0)) error|=FOUTX;
	if((starty>VGA_DISPLAY_Y)||(starty<0)||(eindy>VGA_DISPLAY_Y)||(eindy<0)) error|=FOUTY;
	return error;
}


///////////////////////////////////////////
 // figuren
//////////////////////////////////////////
int API_DRAW_line(int startx, int starty, int eindx, int eindy, char kleur, int dikte)
{
	int error=0;
	error = API_ERROR_inrange(startx, starty, eindx, eindy);
	if (error) return error;
	error = API_IO_line(startx, starty, eindx, eindy, kleur, dikte);
	return error;
}

int API_DRAW_rechthoek(int startx, int starty, int breedte, int hoogte, int kleur, int gevuld)
{
	int error=0;
	error = API_ERROR_inrange(startx, starty, startx+breedte, starty+hoogte);
	if (error) return error;
	error = API_IO_rechthoek(startx, starty, breedte, hoogte, kleur, gevuld);
	return error;
}


///////////////////////////////////////////
 // tekst
//////////////////////////////////////////
int API_DRAW_text(char* zin, int x_lup, int y_lup, int kleur, int achtergrond)
{
	int i, error=0;

	API_IO_putc(zin[0], x_lup, y_lup, kleur,achtergrond);
	for (i=1; i< strlen(zin); i++)
		error=API_IO_putc(zin[i], x_lup+=16/*(8*(arial_16ptDescriptors[(int)(zin[i-1]-' ')][0]))*/, y_lup, kleur, achtergrond);
	return error;
}


///////////////////////////////////////////
 // bitmap
//////////////////////////////////////////
int API_DRAW_bitmap(int nr, int x, int y, int background)
{
	int error=0;
	unsigned int breedte, hoogte;
	switch(nr)
	{
	case API_IO_PIJL_LINKS:
		breedte = (unsigned int)(*(pijl_links+0)|(*(pijl_links+1)<<8)|(*(pijl_links+2)<<16)|(*(pijl_links+3)<<32));
		hoogte  = (unsigned int)(*(pijl_links+4)|(*(pijl_links+5)<<8)|(*(pijl_links+6)<<16)|(*(pijl_links+7)<<32));

		if((x+breedte)>VGA_DISPLAY_X)x=VGA_DISPLAY_X-breedte;
		else if((x+breedte)<0)		 x=0;
		if((y+hoogte)>VGA_DISPLAY_Y) y=VGA_DISPLAY_Y-hoogte;
		else if((y+hoogte)<0)		 y=0;


		API_IO_bitmap(x, y, &pijl_links[0], background);
		break;
	case API_IO_PIJL_RECHTS:
		breedte = (unsigned int)(*(pijl_rechts+0)|(*(pijl_rechts+1)<<8)|(*(pijl_rechts+2)<<16)|(*(pijl_rechts+3)<<32));
		hoogte  = (unsigned int)(*(pijl_rechts+4)|(*(pijl_rechts+5)<<8)|(*(pijl_rechts+6)<<16)|(*(pijl_rechts+7)<<32));

		if((x+breedte)>VGA_DISPLAY_X)x=VGA_DISPLAY_X-breedte;
		else if((x+breedte)<0)		 x=0;
		if((y+hoogte)>VGA_DISPLAY_Y) y=VGA_DISPLAY_Y-hoogte;
		else if((y+hoogte)<0)		 y=0;

		API_IO_bitmap(x, y, &pijl_rechts[0], background);
		break;
	case API_IO_PIJL_OMHOOG:
		breedte = (unsigned int)(*(pijl_omhoog+0)|(*(pijl_omhoog+1)<<8)|(*(pijl_omhoog+2)<<16)|(*(pijl_omhoog+3)<<32));
		hoogte  = (unsigned int)(*(pijl_omhoog+4)|(*(pijl_omhoog+5)<<8)|(*(pijl_omhoog+6)<<16)|(*(pijl_omhoog+7)<<32));

		if((x+breedte)>VGA_DISPLAY_X)x=VGA_DISPLAY_X-breedte;
		else if((x+breedte)<0)		 x=0;
		if((y+hoogte)>VGA_DISPLAY_Y) y=VGA_DISPLAY_Y-hoogte;
		else if((y+hoogte)<0)		 y=0;

		API_IO_bitmap(x, y, &pijl_omhoog[0], background);
		break;
	case API_IO_PIJL_OMLAAG:
		breedte = (unsigned int)(*(pijl_omlaag+0)|(*(pijl_omlaag+1)<<8)|(*(pijl_omlaag+2)<<16)|(*(pijl_omlaag+3)<<32));
		hoogte  = (unsigned int)(*(pijl_omlaag+4)|(*(pijl_omlaag+5)<<8)|(*(pijl_omlaag+6)<<16)|(*(pijl_omlaag+7)<<32));

		if((x+breedte)>VGA_DISPLAY_X)x=VGA_DISPLAY_X-breedte;
		else if((x+breedte)<0)		 x=0;
		if((y+hoogte)>VGA_DISPLAY_Y) y=VGA_DISPLAY_Y-hoogte;
		else if((y+hoogte)<0)		 y=0;

		API_IO_bitmap(x, y, &pijl_omlaag[0], background);
		break;
	case API_IO_SMILY_BLIJ:
		breedte = (unsigned int)(*(smiley_blij+0)|(*(smiley_blij+1)<<8)|(*(smiley_blij+2)<<16)|(*(smiley_blij+3)<<32));
		hoogte  = (unsigned int)(*(smiley_blij+4)|(*(smiley_blij+5)<<8)|(*(smiley_blij+6)<<16)|(*(smiley_blij+7)<<32));

		if((x+breedte)>VGA_DISPLAY_X)x=VGA_DISPLAY_X-breedte;
		else if((x+breedte)<0)		 x=0;
		if((y+hoogte)>VGA_DISPLAY_Y) y=VGA_DISPLAY_Y-hoogte;
		else if((y+hoogte)<0)		 y=0;

		API_IO_bitmap(x, y, &smiley_blij[0], background);
		break;
	case API_IO_SMILY_BOOS:
		breedte = (unsigned int)(*(smiley_boos+0)|(*(smiley_boos+1)<<8)|(*(smiley_boos+2)<<16)|(*(smiley_boos+3)<<32));
		hoogte  = (unsigned int)(*(smiley_boos+4)|(*(smiley_boos+5)<<8)|(*(smiley_boos+6)<<16)|(*(smiley_boos+7)<<32));

		if((x+breedte)>VGA_DISPLAY_X)x=VGA_DISPLAY_X-breedte;
		else if((x+breedte)<0)		 x=0;
		if((y+hoogte)>VGA_DISPLAY_Y) y=VGA_DISPLAY_Y-hoogte;
		else if((y+hoogte)<0)		 y=0;

		API_IO_bitmap(x, y, &smiley_boos[0], background);
		break;

	default: error=INPUTERROR;
	}
	return error;
}
