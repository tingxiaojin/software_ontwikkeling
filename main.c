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

int get_rc(int rc_dif, int noemer, int teller)
{
	int rc = (((float)teller+1)/((float)noemer+1))*100;	//berekening van helling

	if(rc<rc_dif)
		return rc/100;		//afronden naar beneden
	if(rc>=rc_dif)
		return (rc/100)+1;	//afronden naar boven
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
void lijn_hoek(float teller, float noemer, int BP1, int EP1, int BP2, int EP2, int kleur)
{
	int i = BP1;
	int j = EP1;
	int k;
	int rc;

	int rc_dif = (teller/noemer)*100;
	for(i=BP1; i<= BP2; i++)
	{
						//tellery noemerx
		rc = get_rc(rc_dif, EP2-j, EP2-i);
		for(k=0; k<rc; k++)
		{
			UB_VGA_SetPixel(i,j,kleur);
			j++;
		}

	}

	/*rc_dif = ((float)y_dif/(float)x_dif)*100;
				for(x=x_1; x<=x_2; x++)
				{
					rc = get_rc(rc_dif, x_2-x, y_2-y);
					for(i=0; i<rc; i++)
					{
						UB_VGA_SetPixel(x,y,color);
						y++;
					}
				}*/

}

int API_draw_line(int x_1, int y_1, int x_2, int y_2, int color, int weight, int reserved){
	int x_dif = x_2-x_1;
	int y_dif = y_2-y_1;

	char state;
	state = switch_state(x_dif, y_dif);

	int rc;
	int rc_dif;
	int i;
	int x = x_1;
	int y = y_1;

	switch(state){
	case 9://++
		x_dif = x_2-x_1;
		y_dif = y_2-y_1;
		if(x_dif <= y_dif)
		{
			/*rc_dif = ((float)y_dif/(float)x_dif)*100;
			for(x=x_1; x<=x_2; x++)
			{
				rc = get_rc(rc_dif, x_2-x, y_2-y);
				for(i=0; i<rc; i++)
				{
					UB_VGA_SetPixel(x,y,color);
					y++;
				}
			}*/
			//						noemer		teller	noemer	teller
			lijn_hoek(y_dif, x_dif, x_1, y_1, x_2, y_2,color);
		}
		if(x_dif > y_dif)
		{
			/*rc_dif = ((float)x_dif/(float)y_dif)*100;
			for(y=y_1; y<=y_2; y++)
			{
				rc = get_rc(rc_dif, y_2-y, x_2-x);
				for(i=0; i<rc; i++)
				{
					UB_VGA_SetPixel(x,y,color);
					x++;
				}
			}*/
//						noemer		teller	noemer	teller
			lijn_hoek(x_dif, y_dif, y_1, x_1, y_2, x_2,color);
		}
		break;
	default:
		UB_VGA_SetPixel(100,100,VGA_COL_MAGENTA);
		break;
	}

}

//
//parameter: x,y x',y' dikte kleur
//
void lijn(int x, int y, int x1, int y1, int size, int kleur){

	int x_dif;
	int y_dif;
	int buffer;

	//Deze twee if-statements is voor het plaatsen van een lijn van links naar recht
	//buffer zorgt ervoor dat x is gewisseld
	//het verschil tussen x coordinaten is voor het bepalen van welke berekening uitgevoerd moet worden
	if(x1 < x)
	{
		buffer = x;
		x = x1;
		x1 = buffer;
	}
	x_dif = x1 - x;

	if(y1 < y)
	{
		buffer = y;
		y = y1;
		y1 = buffer;
	}
	y_dif = y1 - y;

	int rc;
	int i ;
	int j;

	//berekening voor het maken van 0 tot 45 graden
	if(y_dif<x_dif)
	{
		for(i=y; i<=y1; i++)
		{
	 		rc = (x1-x)/(y1-i+1);

	 		for(j=0; j<=rc; j++)
			{
				UB_VGA_SetPixel((int)x,i,kleur);
				x++;
			}

		}
	}
	//berekening voor het maken van 45 tot 90 graden
	if(y_dif>=x_dif)
	{
		for(i=x; i<=x1; i++)
		{
			rc = (y1-y)/(x1-i+1);
			for(j=0; j<=rc; j++)
			{
				UB_VGA_SetPixel(i,y,kleur);
				y++;
			}

		}
	}
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



	API_draw_line(0,0,0,239,VGA_COL_CYAN,1,0);
	UB_VGA_SetPixel(0,0,VGA_COL_RED);
	UB_VGA_SetPixel(319,239,VGA_COL_RED);
	API_draw_line(0,0,100,239,VGA_COL_GREEN,1,0);
	API_draw_line(0,0,319,239,VGA_COL_YELLOW,1,0);


  while(1)
  {
		//lijn(0,0,10,10,1,VGA_COL_GREEN);
		//lijn(0,10,10,0,1,VGA_COL_MAGENTA);
	  // put the code here
  }
}

