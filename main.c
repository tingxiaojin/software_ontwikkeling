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



int API_draw_line(int x_1, int y_1, int x_2, int y_2, int color, int weight, int reserved)
{
  int i;
  int x, y;
  float dx, dy, a;

  dx = x_2 - x_1;
  dy = y_2 - y_1;
  a  = dy/dx;
for(i=weight/2; weight>0; i--, weight--)
{

	if (fabs(a)<=1)
    if (x_1 < x_2)
      for (x=x_1; x<x_2; x++)
      {
        y = (int)(a*(x-x_1)+y_1+i); // y = ax + b
        UB_VGA_SetPixel(x,y,color);
      }
    else
      for (x=x_2; x<x_1; x++)
      {
        y = (int)(a*(x-x_1)+y_1+i); // y = ax + b
        UB_VGA_SetPixel(x,y,color);
      }

  else
    if (y_1 < y_2)
      for (y=y_1; y<y_2; y++)
      {
        x = (int)((1/a)*(y-y_1)+x_1+i); // x = (y - b)/a
        UB_VGA_SetPixel(x,y,color);
      } else
      for (y=y_2; y<y_1; y++)
      {
        x = (int)((1/a)*(y-y_1)+x_1+i); // y = ax + b
        UB_VGA_SetPixel(x,y,color);
      }
}

  return 0;
}

int main(void)
{

	//  uint32_t n;

	SystemInit(); // System speed to 168MHz

	UB_VGA_Screen_Init(); // Init VGA-Screen

	UB_VGA_FillScreen(VGA_COL_BLACK);





//	UB_VGA_SetPixel(10,10,10);


	API_draw_line(0, 0, 319, 239, VGA_COL_WHITE, 10, 0);
	API_draw_line(319, 0, 0, 239, VGA_COL_WHITE, 10, 0);
	API_draw_line(0, 0, 319, 239, VGA_COL_RED, 1, 0);
	API_draw_line(319, 0, 0, 239, VGA_COL_RED, 1, 0);


  while(1)
  {
	  // put the code here
  }
}
