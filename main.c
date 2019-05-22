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
#include <stdint.h>

#include "APIdraw.h"

/*int main(void)
{
\
	//  uint32_t n;

	SystemInit(); // System speed to 168MHz

	UB_VGA_Screen_Init(); // Init VGA-Screen

	//UB_VGA_FillScreen(VGA_COL_BLACK);

	API_clearscreen(VGA_COL_WHITE);
	API_draw_bitmap(0, 0, 0);
	API_draw_bitmap(60, 0, 1);
	API_draw_bitmap(120, 0, 2);
	API_draw_bitmap(0, 60, 3);
	API_draw_bitmap(0, 120, 4);
	API_draw_bitmap(150, 150, 5);
	//API_draw_bitmap(50, 50, 2);

	//UB_VGA_SetPixel(10,10,10);


	/*API_draw_line(140, 100, 319, 239, VGA_COL_WHITE, 10, 0);
	API_draw_line(319, 0, 0, 239, VGA_COL_WHITE, 10, 0);
	API_draw_line(319, 0, 0, 239, VGA_COL_RED, 1, 0);

	//API_draw_rectangle(10,10,5,10,VGA_COL_CYAN,0,1,VGA_COL_BLACK);


  while(1)
  {
	  // put the code here
  }
}*/
