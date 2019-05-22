//--------------------------------------------------------------
// File     : stm32_ub_vga_320x240.c
// CPU      : STM32F4
// IDE      : CooCox CoIDE 1.7.0
// Module   : GPIO, TIM, MISC, DMA
// Function : VGA out by GPIO (320x240 Pixel, 8bit color)
//
// signals  : PB11      = HSync-Signal
//            PB12      = VSync-Signal
//            PE8+PE9   = color Blue
//            PE10-PE12 = color Green
//            PE13-PE15 = color red
//
// uses     : TIM1, TIM2
//            DMA2, Channel6, Stream5
//--------------------------------------------------------------


//--------------------------------------------------------------
// Includes
//--------------------------------------------------------------
#include "APIdraw.h"
#include "APIbitmap.h"
#include "stm32_ub_vga_screen.h"
#include <math.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

//-------------------------------------------------------------
//functions prototypes
//-------------------------------------------------------------
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
	int flag;
	int i;
	int j;

	for(j=y; j<=y+height; j++)
	{
		if(j<weight+y || j>y+height-weight ||filled ==1)
			flag = 1;
		else
			flag = 0;
		for(i=x; i<=x+width; i++)
		{
			switch(flag){
			case 0:
				if(i<x+weight || i>x+width-weight)
					UB_VGA_SetPixel(i,j,color);
				break;
			case 1:
				UB_VGA_SetPixel(i,j,color);
				break;
			}
		}
	}
	return 0;
}


void IO_draw_bitmap(uint8_t* bmp, int x, int y){
	uint8_t* pchar = bmp;

	int i;
	int j;
	int teller = 8;

	for(j=y; j<y+(int)pchar[4]; j++)
	{
		for(i=x; i<x+(int)pchar[0]; i++)
		{
			UB_VGA_SetPixel(i,j,pchar[teller]);
			teller++;
		}
	}

}

int API_draw_bitmap(int x_lup, int y_lup, int bm_nr)
{
	unsigned char* bmp;
	switch(bm_nr){
	case PL: // pijl links
		bmp = pijl_links;
		break;
	case PR: // pijl rechts
		bmp = pijl_rechts;
		break;
	case POH: // pijl omhoog
		bmp = pijl_omhoog;
		break;
	case POL: // pijl omlaag
		bmp = pijl_omlaag;
		break;
	case SBLIJ: // blij
		bmp = smiley_blij;
		break;
	case SBOOS: // boos
		bmp = smiley_boos;
		break;
	}
	IO_draw_bitmap(bmp, x_lup, y_lup);
	return 0;
}

int API_clearscreen (int color)
{
	UB_VGA_FillScreen(color);
	return 0;
}
