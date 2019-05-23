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

#include "UI.h"
#include "LL.h"
#include "API_IO.h"
#include "API_DRAW.h"


void UI_ERR_put(int error)
{
	if (!error) return;
	API_IO_UART_puts("\n\rError: \n\r");
	switch(error)
	{
//	case 0: break; 	// alles verliep goed
	case FOUTX:
		API_IO_UART_puts("\tX VALUE OVERSIZED!\n\rErrorcode: ");
		API_IO_UART_putint(error);
		break;
	case FOUTY:
		API_IO_UART_puts("\tY VALUE OVERSIZED!\n\rErrorcode: ");
		API_IO_UART_putint(error);
		break;
	case FOUTOMVANG:
		API_IO_UART_puts("\tBOTH X AND Y VALUE OVERSIZED!\n\rErrorcode: ");
		API_IO_UART_putint(error);
		break;
	case INPUTERROR:
		API_IO_UART_puts("\tINPUT UNRECOGNIZED!\n\rErrorcode: ");
		API_IO_UART_putint(error);
		break;
	case STR_LEEG:
		API_IO_UART_puts("\tINPUT EMPTY!\n\rErrorcode: ");
		API_IO_UART_putint(error);
		break;
	default:
		API_IO_UART_puts("\tUNKOWN ERRORCODE!\n\rErrorcode: 0x");
		API_IO_UART_putnum(16, error);
	}
	API_IO_UART_puts("\n\r");
}


// replaces a character in a buffer with another character
void UI_CH_rp(char* buffer, char old_char, char new_char)
{
	while (*(buffer++) != '\0')
		if(*(buffer)==old_char)
		{
			*buffer = new_char;
			buffer++;
		}
}



void UI_CH_rm(char* buffer, char c)
{
	int j=0;
	while (*(buffer++) != '\0')
	{
		for(; *(buffer+j) == c; j++);
		*(buffer) = *(buffer+j);
	}
}
//
//void LL_LINE_init(char* buffer, FUNCTIE* input)
//{
//	input->functie = LIJN;
//	input->startx  = atoi(UI_get_param(&buffer[0], 1));
//	input->starty  = atoi(UI_get_param(&buffer[0], 2));
//	input->eindx	  = atoi(UI_get_param(&buffer[0], 3));
//	input->eindy   = atoi(UI_get_param(&buffer[0], 4));
//	input->kleur   = atoi(UI_get_param(&buffer[0], 5));
//	input->dikte   = atoi(UI_get_param(&buffer[0], 6));
//}



int main(void)
{
	API_IO_init();
	API_IO_clearscherm(VGA_COL_RED);
	FUNCTIE input;
	char buffer [50];
	int i;
	int error=-1;


//	memset(buffer, 0, sizeof(buffer));
//	API_IO_UART_puts("WELKOM MIJN CODE :D\n\r");
//	API_IO_UART_putint(API_DRAW_line(1, 1, 1, 200, 50, 1));

	while(1)
	{
		API_IO_UART_gets(buffer); // get user input
		UI_CH_rm(buffer, ' ');    // remove spaces
		UI_CH_rm(buffer, 0x08);   // remove backspaces
		UI_CH_rp(buffer, ',', '\0'); // replace comma with a string terminator

		// if input = empty
		if((strlen(buffer)==STR_EMPTY)||(buffer[0] == '\n'))
		{
			error = STR_LEEG;
			UI_ERR_put(error);
			continue;
		}

		// to-upper functienaam
		for(i=0;*(buffer+i)!='\0'; i++)
			*(buffer+i) = toupper(*(buffer+i));




		if (LL_STRING_check(buffer,"LIJN"))//!(strncmp(buffer,"LIJN",strlen("LIJN")))==TRUE)
		{
			LL_FIG_init(buffer, &input, LIJN);
			error = LL_exe(&input);
		}
		else if (LL_STRING_check(buffer,"RECHTHOEK"))
		{
			LL_FIG_init(buffer, &input, RECHTHOEK);
			error = LL_exe(&input);
		}
		else if (LL_STRING_check(buffer,"BITMAP"))
		{
			LL_FIG_init(buffer, &input, BITMAP);
			error = LL_exe(&input);
		}
		else if (LL_STRING_check(buffer,"CLEARSCHERM"))
		{
			LL_FIG_init(buffer, &input, CLEARSCHERM);
			error = LL_exe(&input);
		}
		else
			error = INPUTERROR;

		UI_ERR_put(error);
		memset(buffer, 0, sizeof(buffer));

	}
}
