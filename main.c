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
	if(x1 >= x)
		x_dif = x1 - x;
	else
		x_dif = x - x1;

	if(y1 >= y)
		y_dif = y1 - y;
	else
		y_dif = y - y1;

	while(size)
	{
		if(x_dif && y_dif==0)
		{
			int i;
			for(i=x; i<x1; i++)
				UB_VGA_SetPixel(i,y,kleur);
			y++;
		}

		if(y_dif && x_dif==0)
		{
			int i;
			for(i=y; i<y1; i++)
				UB_VGA_SetPixel(x,i,kleur);
			x++;
		}

		size--;
	}
	int rc;
	int i;
	int j;
	int som = y;
	int len_dif;

	rc = y_dif / (x_dif+1);

	for(i=x; i<=x1; i++)
	{
		for(j=0; j<rc; j++)
		{
			UB_VGA_SetPixel(i,y,kleur);
			y++;
		}
		rc = (y1-y)/(x1-x+1);
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

	  //		xklein ygroot xgroot yklein
	  rechthoek(10,150,50,100,VGA_COL_MAGENTA);
	  lijn(10,100,50,100,1,VGA_COL_GREEN);

  while(1)
  {

	  // put the code here
  }
}

