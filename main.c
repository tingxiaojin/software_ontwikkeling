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

void delay(int count){
	while(count)
		count --;
}

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
		if(rc>rc_dif)
			return (rc/100)+1;	//afronden naar boven
		if(rc==100 && rc_dif==100)
			return rc/100;//Voor 45 graden hoek anders worden het stapjes van twee
	}

	if(rc_dif<0)
	{
		rc = (((float)teller+1)/((float)noemer-1))*100;
		if(rc<rc_dif)
			return ((rc*-1)/100)+1;	//afronden naar boven
		if(rc>rc_dif)
			return (rc*-1)/100;
		if(rc==-100 && rc_dif==-100)
			return (rc*-1)/100;//Voor 45 graden hoek anders worden het stapjes van twee
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
	{							//tellery noemerx
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
	for(i=BP1; i>=BP2; i--)
	{					//tellery noemerx
		rc = get_rc(rc_dif, EP2-j, BP2-i);

		for(k=0; k<rc; k++)
		{
			if(graden > 0)
				UB_VGA_SetPixel(i,j,kleur);
			if(graden == 0)
				UB_VGA_SetPixel(j,i,kleur);
			if(j>=VGA_DISPLAY_X-1)
				break;
			j++;
		}

	}

}

void line_decision(char state, int x_1, int y_1, int x_2, int y_2, int color)
{
	int x_dif = x_2-x_1;
	int y_dif = y_2-y_1;
	switch(state){
	case 9://++ lijn'\'
		x_dif = x_2-x_1;
		y_dif = y_2-y_1;

		if(x_dif >= y_dif)//			noemer teller noemer teller
			lijn_hoek(x_dif, y_dif, y_1, x_1, y_2, x_2,color, 0);
		if(x_dif < y_dif)//			noemer teller noemer teller
			lijn_hoek(y_dif, x_dif, x_1, y_1, x_2, y_2,color, 1);
		break;
	case 17://+- switch lijn'/'
		x_dif = x_1-x_2;
		y_dif = y_1-y_2;

		if(make_pos(y_dif)>make_pos(x_dif))
			lijn_hoek_negatief(y_dif, x_dif, x_1, y_1, x_2, y_2,color, 1);
		if(make_pos(y_dif)<=make_pos(x_dif))
			lijn_hoek_negatief(x_dif, y_dif, y_1, x_1, y_2, x_2,color, 0);
		break;
	case 33://+= horizontale lijn
		lijn_hoek(x_dif, y_dif, y_1, x_1, y_2, x_2,color, 0);
		break;
	case 10://-+ lijn'/'
		x_dif = x_2-x_1;
		y_dif = y_2-y_1;

		if(make_pos(y_dif)>make_pos(x_dif))
			lijn_hoek_negatief(y_dif, x_dif, x_1, y_1, x_2, y_2,color, 1);
		if(make_pos(y_dif)<=make_pos(x_dif))
			lijn_hoek_negatief(x_dif, y_dif, y_2, x_2, y_1, x_1,color, 0);
		break;
	case 18://-- switch lijn'\'
		x_dif = x_1-x_2;
		y_dif = y_1-y_2;

		if(x_dif >= y_dif)//			noemer teller noemer teller
			lijn_hoek(x_dif, y_dif, y_2, x_2, y_1, x_1,color, 0);
		if(x_dif < y_dif)//			noemer teller noemer teller
			lijn_hoek(y_dif, x_dif, x_2, y_2, x_1, y_1,color, 1);
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
}

int API_draw_line(int x_1, int y_1, int x_2, int y_2, int color, int weight, int reserved){
	int x_dif = x_2-x_1;
	int y_dif = y_2-y_1;

	char state = switch_state(x_dif, y_dif);
	line_decision(state,x_1,y_1,x_2,y_2,color);



	if(weight>1)
	{
		int i;

		switch(state){
		case 33:// += 319-0 100-100
		//case 34:
			for(i=0; i<weight-1; i++)
			{
				int y1_up_teller = y_1;
				int y1_down_teller = y_1;
				int y2_up_teller = y_2;
				int y2_down_teller = y_2;

				if(i%2)
				{
					y1_up_teller++;
					y2_up_teller++;
					line_decision(state,x_1,y1_up_teller,x_2,y1_up_teller,color);

				}
				else
				{
					y1_down_teller--;
					y2_down_teller--;
					line_decision(state,x_1,y1_down_teller,x_2,y1_down_teller,color);
				}
			}
			break;
		default:
			UB_VGA_SetPixel(160,120,0x13);
			break;
		}

	}
	return 0;
}

int main(void)
{

	//  uint32_t n;

	SystemInit(); // System speed to 168MHz

	UB_VGA_Screen_Init(); // Init VGA-Screen

	UB_VGA_FillScreen(0x83);

	API_draw_line(3,100,319,100,VGA_COL_GREEN,10,0);
	API_draw_line(319,100,0,100,VGA_COL_RED,5,0);
	//API_draw_line(0,0,100,100,VGA_COL_GREEN,1,0);
	// VGA scherm max x=319 max y=239

	int teller=0;
	int tellerbx = 319;
	int tellerby = 0;
	int teller2 = 0;
  while(1)
  {
	  /*// test lijn lo naar rechtsonder
	  API_draw_line(0,0,tellerbx,tellerby,VGA_COL_BLUE,1,0);
	  API_draw_line(0,0,teller2,239,VGA_COL_YELLOW,1,0);
	  API_draw_line(319,0,319-teller2,239,VGA_COL_MAGENTA,1,0);
	  API_draw_line(319,0,0,tellerby,VGA_COL_CYAN,1,0);

	  if(tellerby>239-1)
	  {
		  tellerby=239;
		  if(tellerbx<0)
		  {
			  tellerby=0;
			  tellerbx=319;
		  }
		  else
			  tellerbx--;

	  }
	  else
	  {
		  tellerbx=319;
		  tellerby++;
	  }

	  if(teller2>319-1)
		  teller2=0;
	  else
		  teller2++;
	  delay(1000000);

	  API_draw_line(0,0,tellerbx-1,tellerby-1,VGA_COL_WHITE,1,0);
	  API_draw_line(0,0,teller2-1,239,VGA_COL_WHITE,1,0);
	  API_draw_line(319,0,319-teller2+1,239,VGA_COL_WHITE,1,0);
	  API_draw_line(319,0,0,tellerby-1,VGA_COL_WHITE,1,0);
	  //delay(1000000);
	  // put the code here

		API_draw_line(0,0,319,0,VGA_COL_RED,1,0);
		API_draw_line(0,230,319,230,VGA_COL_RED,1,0);
		API_draw_line(0,0,0,230,VGA_COL_RED,1,0);
		API_draw_line(319,0,319,230,VGA_COL_RED,1,0);



		API_draw_line(319,0,0,239,VGA_COL_GREEN,1,0);
		API_draw_line(319,239,0,0,VGA_COL_GREEN,1,0);

		API_draw_line(319,120,0,120,VGA_COL_BLACK,1,0);
		API_draw_line(160,0,160,239,VGA_COL_BLACK,1,0);*/
  }
}

