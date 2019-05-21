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
<<<<<<< HEAD

int main(void)
=======
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

<<<<<<< HEAD
uint8_t array[] = {0x9, 0x0, 0x0, 0x0, 0xb, 0x0, 0x0, 0x0,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0x0, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0x0, 0xff, 0x0, 0xff, 0xff, 0xff,
0xff, 0xff, 0x0, 0xff, 0xff, 0xff, 0x0, 0xff, 0xff,
0xff, 0x0, 0xff, 0xff, 0xff, 0xff, 0xff, 0x0, 0xff,
0x0, 0x0, 0x0, 0xff, 0xff, 0xff, 0x0, 0x0, 0x0,
0xff, 0xff, 0x0, 0xff, 0xff, 0xff, 0x0, 0xff, 0xff,
0xff, 0xff, 0x0, 0xff, 0xff, 0xff, 0x0, 0xff, 0xff,
0xff, 0xff, 0x0, 0xff, 0xff, 0xff, 0x0, 0xff, 0xff,
0xff, 0xff, 0x0, 0x0, 0x0, 0x0, 0x0, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};

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

int API_draw_rectangle(int x, int y, int width, int height, int color, int filled, int weight, int border_color)
{
	int flag = 0;
	int i;
	int j;
	int rand = weight;

	for(j=y; j<=y+height; j++)
	{
		if(j<rand+y || j>y+height-rand && filled ==0)
			flag = 0;

		if(j>=rand+y || j<=y+height-rand && filled ==1)
			flag = 1;

		for(i=x; i<=x+width; i++)
		{
			switch(flag){
			case 0:
				if(i<x+rand || i>x+width-rand)
					UB_VGA_SetPixel(i,j,color);
				break;
			case 1:
				if(filled == 1)
					UB_VGA_SetPixel(i,j,color);
				else {
					//if(i>=x+rand || i<=x+width-rand && filled = 0)
						//UB_VGA_SetPixel(i,j,color);
				}
				break;
			}
		}
	}

	return 0;
}

void get_size(char* gbmp, PPIXEL data){
	int i;
	for(i=0; i<sizeof(int); i++)
	{
		&data+i = &gbmp+i;
	}
}

void IO_draw_bitmap(char* gbmp, int x, int y){
	get_size(&gbmp, &data);

}

int API_draw_bitmap(int x_lup, int y_lup, int bm_nr)
>>>>>>> e5b3ed66269ba126d9a02853a9998f068dd1b61e
{
	switch(bm_nr){
	case 0:
		IO_draw_bitmap(BMP, x_lup, y_lup);
		break;
	}

	return 0;
}

int API_clearscreen (int color)
{
	UB_VGA_FillScreen(color);
	return 0;
}

=======
#include "APIdraw.h"
>>>>>>> ac82ea1ed485c60ab685ea7534270d18439bdce5

int main(void)
{
\
	//  uint32_t n;

	SystemInit(); // System speed to 168MHz
	UB_VGA_Screen_Init(); // Init VGA-Screen
<<<<<<< HEAD
	UB_VGA_FillScreen(VGA_COL_BLACK);

=======

	//UB_VGA_FillScreen(VGA_COL_BLACK);
>>>>>>> e5b3ed66269ba126d9a02853a9998f068dd1b61e

	API_clearscreen(VGA_COL_WHITE);
	API_draw_bitmap(0, 0, 0);
	API_draw_bitmap(60, 0, 1);
	API_draw_bitmap(120, 0, 2);
	API_draw_bitmap(0, 60, 3);
	API_draw_bitmap(0, 120, 4);
	API_draw_bitmap(150, 150, 5);
	//API_draw_bitmap(50, 50, 2);

	//UB_VGA_SetPixel(10,10,10);


<<<<<<< HEAD
//	UB_VGA_SetPixel(10,10,10);


<<<<<<< HEAD
	API_draw_line(0, 0, 250, 170, VGA_COL_WHITE, 20, 0);
//	API_draw_line(319, 0, 0, 239, VGA_COL_WHITE, 10, 0);
//	API_draw_line(0, 0, 319, 239, VGA_COL_RED, 1, 0);
//	API_draw_line(319, 0, 0, 239, VGA_COL_RED, 1, 0);
=======
	API_draw_line(140, 100, 319, 239, VGA_COL_WHITE, 10, 0);
	API_draw_line(319, 0, 0, 239, VGA_COL_WHITE, 10, 0);
	API_draw_line(319, 0, 0, 239, VGA_COL_RED, 1, 0);
>>>>>>> e5b3ed66269ba126d9a02853a9998f068dd1b61e
=======
	/*API_draw_line(140, 100, 319, 239, VGA_COL_WHITE, 10, 0);
	API_draw_line(319, 0, 0, 239, VGA_COL_WHITE, 10, 0);
	API_draw_line(319, 0, 0, 239, VGA_COL_RED, 1, 0);
*/
	//API_draw_rectangle(10,10,5,10,VGA_COL_CYAN,0,1,VGA_COL_BLACK);
>>>>>>> ac82ea1ed485c60ab685ea7534270d18439bdce5


  while(1)
  {
	  // put the code here
  }
}
