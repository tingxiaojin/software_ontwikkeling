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

<<<<<<< HEAD
#include "main.h"
#include "stm32_ub_vga_screen.h"
#include <math.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

char buffer[]={"lijn, 10, 10, 50, 50, kleur, dikte"};
=======
#include "UI.h"
#include "LL.h"
#include "API_IO.h"
#include "API_DRAW.h"

// replaces a character in a buffer with another character
void UI_rp_char(char* buffer, char old_char, char new_char)
{
	while (*(buffer++) != '\0')
		if(*(buffer)==old_char)
		{
			*buffer = new_char;
			buffer++;
		}
}

char* UI_get_param(char* buffer, int paramnum)
{
	for(;paramnum>0; paramnum--)
	{
		for (; *buffer!='\0'; buffer++);
		buffer++;
	}
	return buffer;
}


void UI_rm_char(char* buffer, char c)
{
	int j=0;
	while (*(buffer++) != '\0')
	{
		for(; *(buffer+j) == c; j++);
		*(buffer) = *(buffer+j);
	}
}
>>>>>>> bbfd2cb6ba4971de39efc3dc1e204fe7cce21de7

int main(void)
{
	API_IO_INIT();
	API_IO_clearscherm(VGA_COL_MAGENTA);
	FUNCTIE input;
	char buffer [50];
	memset(buffer, 0, sizeof(buffer));
	int i;
	API_IO_UART_puts("WELKOM MIJN CODE :D\n\r");
	API_DRAW_line(1, 1, 1, 200, 50, 1);

	while(1)
	{
		API_IO_UART_gets(buffer);// get user input
		UI_rm_char(buffer, ' '); // remove spaces
		UI_rp_char(buffer, ',', '\0'); // replace comma with string terminator

		// to-upper functienaam
		for(i=0;*(buffer+i)!='\0'; i++)
			*(buffer+i) = toupper(*(buffer+i));

		if (!(strncmp(buffer,"LIJN",strlen("LIJN")))==TRUE)
		{
			input.functie = LIJN;
			input.startx  = atoi(UI_get_param(&buffer[0], 1));
			input.starty  = atoi(UI_get_param(&buffer[0], 2));
			input.eindx	  = atoi(UI_get_param(&buffer[0], 3));
			input.eindy   = atoi(UI_get_param(&buffer[0], 4));
			input.kleur   = atoi(UI_get_param(&buffer[0], 5));
			input.dikte   = atoi(UI_get_param(&buffer[0], 6));

<<<<<<< HEAD
	//UB_VGA_FillScreen(VGA_COL_BLACK);
	API_clearscreen(VGA_COL_WHITE);
	API_draw_line(319, 0, 0, 239, VGA_COL_CYAN, 2, 0);
=======
			API_IO_UART_puts("\n\rError: \n\r");
			API_IO_UART_putint(LL_exe(&input));
>>>>>>> bbfd2cb6ba4971de39efc3dc1e204fe7cce21de7


//			API_IO_UART_puts(UI_get_param(&buffer[0], 2));
			API_IO_UART_puts("\n\n\r");
//			API_IO_UART_puts(buffer);
		}
		else if (!(strncmp(buffer,"RECHTHOEK",strlen("RECHTHOEK")))==TRUE)
		{
			input.functie = RECHTHOEK;
			input.startx  = atoi(UI_get_param(&buffer[0], 1));
			input.starty  = atoi(UI_get_param(&buffer[0], 2));
			input.breedte = atoi(UI_get_param(&buffer[0], 3));
			input.hoogte  = atoi(UI_get_param(&buffer[0], 4));
			input.kleur   = atoi(UI_get_param(&buffer[0], 5));
			input.gevuld  = atoi(UI_get_param(&buffer[0], 6));


			API_IO_UART_putint(LL_exe(&input));
		}
		else if (!(strncmp(buffer,"BITMAP",strlen("BITMAP")))==TRUE)
		{
			input.functie= BITMAP;
			input.nr 	 = atoi(UI_get_param(&buffer[0], 1));
			input.startx = atoi(UI_get_param(&buffer[0], 2));
			input.starty = atoi(UI_get_param(&buffer[0], 3));
			input.achtergrond = atoi(UI_get_param(&buffer[0], 4));

			API_IO_UART_putint(LL_exe(&input));
		}
		memset(buffer, 0, sizeof(buffer));

	}
}
<<<<<<< HEAD

=======
>>>>>>> bbfd2cb6ba4971de39efc3dc1e204fe7cce21de7
