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

int abs(float getal){
	int abs_getal = getal;

	while(getal>=1)
		getal--;
	int getal2;
	getal2 = getal * 10;

	if(getal2 >= 5){
		return abs_getal+1;
	}
	else {
		return abs_getal;
	}
}

void delay(int time){
	while(time)
		time--;
}

void test(){
	int i;

	for(i=10; i<20; i++)
	{
		UB_VGA_SetPixel(i,i,VGA_COL_MAGENTA);
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
			rc = abs((x1-x)/(y1-i+1));
			for(j=0; j<=rc; j++)
			{
				UB_VGA_SetPixel(x,i,kleur);
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
	UB_VGA_SetPixel(100,100,VGA_COL_YELLOW);
	UB_VGA_SetPixel(150,200,VGA_COL_YELLOW);
	//		xklein ygroot xgroot yklein
	rechthoek(10,150,50,100,VGA_COL_MAGENTA);
	lijn(0,0,319,239,1,VGA_COL_GREEN);
	UB_VGA_SetPixel(0,0,VGA_COL_RED);
		UB_VGA_SetPixel(319,239,VGA_COL_RED);


  while(1)
  {

	  // put the code here
  }
}

