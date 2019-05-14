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
>>>>>>> e807678d2152e1974d42088add79350c1247de45
}

int main(void)
{

	//  uint32_t n;

	SystemInit(); // System speed to 168MHz

	UB_VGA_Screen_Init(); // Init VGA-Screen

<<<<<<< HEAD
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
=======
	UB_VGA_FillScreen(VGA_COL_BLACK);





//	UB_VGA_SetPixel(10,10,10);

//	API_draw_line(0, 0, 319, 239, VGA_COL_WHITE);
	API_draw_line(0, 0, 100, 100, VGA_COL_WHITE);



  while(1)
  {
	  // put the code here
>>>>>>> e807678d2152e1974d42088add79350c1247de45
  }
}

