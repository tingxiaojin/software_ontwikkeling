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
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int API_draw_line(int x_1, int y_1, int x_2, int y_2, int color, int weight, int reserved)
{
	int i;
	int x, y;
	float dx, dy, rc;

	dx = x_2 - x_1;
	dy = y_2 - y_1;
	rc  = dy/dx;
	for(i=weight/2; weight>0; i--, weight--)
	{

	if (fabs(rc)<=1)
		if (x_1 < x_2)
		  for (x=x_1; x<x_2; x++)
		  {
			y = (int)(rc*(x-x_1)+y_1+i); // y = ax + b
			UB_VGA_SetPixel(x,y,color);
		  }
		else
		  for (x=x_2; x<x_1; x++)
		  {
			y = (int)(rc*(x-x_1)+y_1+i); // y = ax + b
			UB_VGA_SetPixel(x,y,color);
		  }

	  else
		if (y_1 < y_2)
		  for (y=y_1; y<y_2; y++)
		  {
			x = (int)((1/rc)*(y-y_1)+x_1+i); // x = (y - b)/a
			UB_VGA_SetPixel(x,y,color);
		  } else
		  for (y=y_2; y<y_1; y++)
		  {
			x = (int)((1/rc)*(y-y_1)+x_1+i); // y = ax + b
			UB_VGA_SetPixel(x,y,color);
		  }
	}

	return 0;
}

int API_draw_rectangle(int x, int y, int width, int height, int color, int filled, int reserved, int reserved1)
{
	int i;
	int j;
	int rand;

	for(j=y; j<=y+height; j++)
	{
		if(y<rand || y>y+h-rand)
			continue;
		else
			if(filled == 1)
				continue;
			else
				break;
		for(i=x; i<=x+width; i++)
		{
			if(x<rand || x>x+w-rand)
				UB_VGA_SetPixel(i,j,color);
			else
				if(filled == 1)
					UB_VGA_SetPixel(i,j,color);
				else
					break;
		}
	}

	return 0;
}

int API_clearscreen (int color)
{
	UB_VGA_FillScreen(color);
	return 0;
}


int main(void)
{
\
	//  uint32_t n;

	SystemInit(); // System speed to 168MHz

	UB_VGA_Screen_Init(); // Init VGA-Screen

	UB_VGA_FillScreen(VGA_COL_BLACK);




//	UB_VGA_SetPixel(10,10,10);


	API_draw_line(140, 100, 319, 239, VGA_COL_WHITE, 10, 0);
	API_draw_line(319, 0, 0, 239, VGA_COL_WHITE, 10, 0);
	API_draw_line(0, 0, 319, 239, VGA_COL_RED, 1, 0);
	API_draw_line(319, 0, 0, 239, VGA_COL_RED, 1, 0);

	API_draw_rectangle(10,10,50,100,VGA_COL_CYAN,0,0,0);


  while(1)
  {
	  // put the code here
  }
}
