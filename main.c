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


int API_draw_line(int startx, int starty, int eindx, int eindy, char kleur)
{
  int x, y;
  float dx, dy, a;

  dx = eindx - startx;
  dy = eindy - starty;
  a  = dy/dx;

  if (fabs(a)<=1)
    if (startx < eindx)
      for (x=startx; x<eindx; x++)
      {
        y = (int)(a*(x-startx)+starty); // y = ax + b
        UB_VGA_SetPixel(x,y,kleur);
      }
    else
      for (x=eindx; x<startx; x++)
      {
        y = (int)(a*(x-startx)+starty); // y = ax + b
        UB_VGA_SetPixel(x,y,kleur);
      }

  else
    if (starty < eindy)
      for (y=starty; y<eindy; y++)
      {
        x = (int)((1/a)*(y-starty)+startx); // x = (y - b)/a
        UB_VGA_SetPixel(x,y,kleur);
      } else
      for (y=eindy; y<starty; y++)
      {
        x = (int)((1/a)*(y-starty)+startx); // y = ax + b
        UB_VGA_SetPixel(x,y,kleur);
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

//	API_draw_line(0, 0, 319, 239, VGA_COL_WHITE);
	API_draw_line(0, 0, 200, 200, VGA_COL_WHITE);



  while(1)
  {
	  // put the code here
  }
}
