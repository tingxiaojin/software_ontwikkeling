//--------------------------------------------------------------
// File     : main.c
// Datum    : 30.03.2016
// Version  : 1.0
// Autor    : UB
// mods by	: J.F. van der Bent
// CPU      : STM32F4
// IDE      : CooCox CoIDE 1.7.x
// Module   : CMSIS_BOOT, M4_CMSIS_CORE
// Function : VGA_core DMA LIB 320x240, 8bit color
//--------------------------------------------------------------

#include "main.h"
#include "stm32_ub_vga_screen.h"
#include <math.h>
#include <strings.h>

//In deze functie wordt er nagegaan welke write functie gebruikt gaat worden voor het maken van een lijn.
//parameters:
// x,y begin en x,y eind
// return value:
// eerste drie bits of x +, -, =
// tweede drie bits of y +, -, =

int make_pos(signed int getal){
	if(getal<0)
		return getal*-1;
	if(getal>1)
		return getal;
	return 0;
}

int get_rc(signed int rc_dif, int teller, int noemer)
{
	int rc;
	if(rc_dif>=0)
	{
		rc = (((float)teller+1)/((float)noemer+1))*100;	//berekening van helling
		if(rc<rc_dif || rc_dif==0)
			return rc/100;		//afronden naar beneden
		if(rc>=rc_dif)
			return (rc/100)+1;	//afronden naar boven
	}

	if(rc_dif<0)
	{
		if(teller>0 && noemer<0)
		{
			rc = (((float)teller+1)/((float)noemer-1))*100;
			if(rc>=rc_dif)
				return ((rc*-1)/100)+1;	//afronden naar boven
			else
				return (rc*-1)/100;
		}

		if(teller<0 && noemer>0)
		{
			rc = (((float)teller-1)/((float)noemer+1))*100;
			if(rc>=rc_dif)
				return ((rc*-1)/100)+1;	//afronden naar boven
			else
				return (rc*-1)/100;
		}
	}

	return 0;
}

int switch_state(int x_dif, int y_dif){
	char switch_value = 0;

	if(x_dif>0)
		switch_value |= 1;	//1e bit +
	if(x_dif<0)
		switch_value |= 2;	//2e bit -
	if(x_dif==0)
		switch_value |= 4;	//3e bit =
	if(y_dif>0)
		switch_value |= 8;	//4e bit +
	if(y_dif<0)
		switch_value |= 16;	//5e bit -
	if(y_dif==0)
		switch_value |= 32;	//6e bit =

	return switch_value;
}
//											noemer		teller	noemer	teller
void lijn_hoek(float teller, float noemer, int BP1, int EP1, int BP2, int EP2, int kleur, int graden)
{
	int i = BP1;
	int j = EP1;
	int k;
	int rc;

	int rc_dif = (teller/noemer)*100;
	for(i=BP1; i<= BP2; i++)
	{
		if(graden == 2)
			rc = 1;
		else					//tellery noemerx
			rc = get_rc(rc_dif, EP2-j, BP2-i);

		for(k=0; k<rc; k++)
		{
			if(graden > 0)
				UB_VGA_SetPixel(i,j,kleur);
			if(graden == 0)
				UB_VGA_SetPixel(j,i,kleur);
			if(j>=VGA_DISPLAY_X-1 || j>EP2)
				break;
			j++;
		}

	}

}

void lijn_hoek_negatief(float teller, float noemer, int BP1, int EP1, int BP2, int EP2, int kleur, int graden)
{
	int i = BP1;
	int j = EP1;
	int k;
	int rc;

	signed int rc_dif = (teller/noemer)*100;
	for(i=BP1; i>BP2; i--)
	{
		if(graden == 2)
			rc = 1;
		else					//tellery noemerx
			rc = get_rc(rc_dif, EP2-j, BP2-i);

		for(k=0; k<rc; k++)
		{
			if(graden > 0)
				UB_VGA_SetPixel(i,j,kleur);
			if(graden == 0)
				UB_VGA_SetPixel(j,i,kleur);
			if(j>=VGA_DISPLAY_X-1 || j>EP2)
				break;
			j++;
		}

	}

}

int API_draw_line(int x_1, int y_1, int x_2, int y_2, int color, int weight, int reserved){
	int x_dif = x_2-x_1;
	int y_dif = y_2-y_1;

	char state;
	state = switch_state(x_dif, y_dif);

	switch(state){
	case 9://++
		x_dif = x_2-x_1;
		y_dif = y_2-y_1;

		if(x_dif > y_dif)//			noemer teller noemer teller
			lijn_hoek(x_dif, y_dif, y_1, x_1, y_2, x_2,color, 0);
		if(x_dif < y_dif)//			noemer teller noemer teller
			lijn_hoek(y_dif, x_dif, x_1, y_1, x_2, y_2,color, 1);
		//if(x_dif == y_dif)
		//	lijn_hoek(y_dif, x_dif, x_1, y_1, x_2, y_2,color, 2);
		break;
	case 17://+-
		x_dif = x_2-x_1;
		y_dif = y_2-y_1;

		if(make_pos(x_dif) > make_pos(y_dif))//			noemer teller noemer teller
			lijn_hoek_negatief(x_dif, y_dif, y_1, x_1, y_2, x_2,color, 0);
		if(make_pos(x_dif) < make_pos(y_dif))//			noemer teller noemer teller
		{
			int i;
			int j;
			int k;
			int rc;

			signed int rc_dif = (teller/noemer)*100;
			for(i=x_2; i>x_1; i--)
			{
				rc = get_rc(rc_dif, EP2-j, x_1-i);

				for(k=0; k<rc; k++)
				{
					if(graden > 0)
						UB_VGA_SetPixel(i,j,kleur);
					if(graden == 0)
						UB_VGA_SetPixel(j,i,kleur);
					if(j>=VGA_DISPLAY_X-1 || j>EP2)
						break;
					j++;
				}

			}
		}

		//if(x_dif == y_dif)
			//lijn_hoek(y_dif, x_dif, x_1, y_1, x_2, y_2,color, 2);*/
		break;
	case 33://+= horizontale lijn
		lijn_hoek(x_dif, y_dif, y_1, x_1, y_2, x_2,color, 0);
		break;
	case 10://-+
		break;
	case 18://--
		x_dif = x_1-x_2;
		y_dif = y_1-y_2;

		if(x_dif > y_dif)//			noemer teller noemer teller
			lijn_hoek(x_dif, y_dif, y_2, x_2, y_1, x_1,color, 0);
		if(x_dif < y_dif)//			noemer teller noemer teller
			lijn_hoek(y_dif, x_dif, x_2, y_2, x_1, y_1,color, 1);
		if(x_dif == y_dif)
			lijn_hoek(y_dif, x_dif, x_2, y_2, x_1, y_1,color, 2);
		break;
	case 34://-= switch hor
		lijn_hoek(x_dif, y_dif, y_2, x_2, y_1, x_1,color, 0);
		break;
	case 12://=+ verticale lijn
		lijn_hoek(x_dif, y_dif, x_1, y_1, x_2, y_2,color, 1);
		break;
	case 20://=- switch ver
		lijn_hoek(x_dif, y_dif, x_2, y_2, x_1, y_1,color, 1);
		break;
	// in deze case is ydif en xdif gelijk dus kan één pixel putten of error?
	/*case 36://==

		break;
	 */
	default:
		UB_VGA_SetPixel(100,100,VGA_COL_MAGENTA);
		break;
	}
	return 0;
}

void rechthoek(int x_lo, int y_lo, int x_rb, int y_rb, int kleur){
	int i;
	int j;

	if(x_lo < x_rb && y_rb < y_lo)
	{
		for(j=y_rb; j<y_lo; j++)
		{
			for(i=x_lo; i<x_rb; i++)
			{
				UB_VGA_SetPixel(i,j,kleur);
			}
		}
	}

}

int main(void)
{

	//  uint32_t n;

	SystemInit(); // System speed to 168MHz

	UB_VGA_Screen_Init(); // Init VGA-Screen

	UB_VGA_FillScreen(VGA_COL_BLUE);




	UB_VGA_SetPixel(0,0,VGA_COL_RED);
	UB_VGA_SetPixel(319,239,VGA_COL_RED);
	//API_draw_line(0,10,319,10,VGA_COL_GREEN,1,0);
	//API_draw_line(0,0,319,239,VGA_COL_YELLOW,1,0);
	//API_draw_line(10,239,10,10,VGA_COL_MAGENTA,1,0);
	//API_draw_line(319,10,10,10,VGA_COL_CYAN,1,0);
	API_draw_line(0,10,5,0,VGA_COL_WHITE,1,0);
	//API_draw_line(0,1,319,0,VGA_COL_GREEN,1,0);

  while(1)
  {
		//lijn(0,0,10,10,1,VGA_COL_GREEN);
		//lijn(0,10,10,0,1,VGA_COL_MAGENTA);
	  // put the code here
  }
}

