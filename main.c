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

int main(void)
{

	//  uint32_t n;

	SystemInit(); // System speed to 168MHz
	UB_VGA_Screen_Init(); // Init VGA-Screen
	UB_VGA_FillScreen(VGA_COL_BLACK);





//	UB_VGA_SetPixel(10,10,10);


	API_draw_line(0, 0, 250, 170, VGA_COL_WHITE, 20, 0);
//	API_draw_line(319, 0, 0, 239, VGA_COL_WHITE, 10, 0);
//	API_draw_line(0, 0, 319, 239, VGA_COL_RED, 1, 0);
//	API_draw_line(319, 0, 0, 239, VGA_COL_RED, 1, 0);


  while(1)
  {
	  // put the code here
  }
}
