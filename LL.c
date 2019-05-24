
#include "UI.h"
#include "API_DRAW.h"
#include "API_IO.h"


#define DEBUG

int LL_STRING_check(char* input, char* figuur)
{
	if(!(strncmp(input,figuur,strlen(figuur)))==TRUE)
		return TRUE;
	else
		return FALSE;
}


char* LL_STRING_param(char* buffer, int paramnum)
{
	for(;paramnum>0; paramnum--)
	{
		for (; *buffer!='\0'; buffer++);
		buffer++;
	}
	return buffer;
}

int LL_STRING_isallnum(char* str)
{
//	char* buff = str;
	int error=0;
	while(*str++!='\0')
		error = (isdigit(*str) == TRUE)? 0: INPUTERROR;
	return error;
}


// Logic Layer Figure init
void LL_FIG_init(char* buffer, FUNCTIE* input, int vorm)
{
	switch(vorm)
	{
	case LIJN:
		input->functie = LIJN;
		input->startx  = atoi(LL_STRING_param(&buffer[0], 1));
		input->starty  = atoi(LL_STRING_param(&buffer[0], 2));
		input->eindx   = atoi(LL_STRING_param(&buffer[0], 3));
		input->eindy   = atoi(LL_STRING_param(&buffer[0], 4));
		input->kleur   = atoi(LL_STRING_param(&buffer[0], 5));
		input->dikte   = atoi(LL_STRING_param(&buffer[0], 6));
		break;

	case RECHTHOEK:
		input->functie = RECHTHOEK;
		input->startx  = atoi(LL_STRING_param(&buffer[0], 1));
		input->starty  = atoi(LL_STRING_param(&buffer[0], 2));
		input->breedte = atoi(LL_STRING_param(&buffer[0], 3));
		input->hoogte  = atoi(LL_STRING_param(&buffer[0], 4));
		input->kleur   = atoi(LL_STRING_param(&buffer[0], 5));
		input->gevuld  = atoi(LL_STRING_param(&buffer[0], 6));
		break;

	case BITMAP:
		input->functie= BITMAP;
		input->nr 	  = atoi(LL_STRING_param(&buffer[0], 1));
		input->startx = atoi(LL_STRING_param(&buffer[0], 2));
		input->starty = atoi(LL_STRING_param(&buffer[0], 3));
		input->achtergrond = (strlen(buffer)>=5)? atoi(LL_STRING_param(&buffer[0], 4)): 1;
		break;

	case CLEARSCHERM:
		input->functie   = CLEARSCHERM;
		input->kleur	 = atoi(LL_STRING_param(&buffer[0], 1));
		break;
	}
}

int LL_exe(FUNCTIE* input)
{
	int error=0;
	switch(input->functie)
	{
	case LIJN:

#ifdef DEBUG
		API_IO_UART_puts("\n\rReceived data from user LL:\n\r");
		API_IO_UART_putint(input->functie);
		API_IO_UART_puts(" ");
		API_IO_UART_putint(input->startx);
		API_IO_UART_puts(" ");
		API_IO_UART_putint(input->starty);
		API_IO_UART_puts(" ");
		API_IO_UART_putint(input->eindx);
		API_IO_UART_puts(" ");
		API_IO_UART_putint(input->eindy);
		API_IO_UART_puts(" ");
		API_IO_UART_putint(input->kleur);
		API_IO_UART_puts(" ");
		API_IO_UART_putint(input->dikte);
		API_IO_UART_puts(" \n\r");
#endif

		error = API_DRAW_line(input->startx, input->starty, input->eindx, input->eindy, input->kleur, input->dikte);

#ifdef DEBUG
		API_IO_UART_puts(" \n\r");
		API_IO_UART_putint(error);
		API_IO_UART_puts(" \n\r");
#endif
		break;

	case RECHTHOEK:
#ifdef DEBUG
		API_IO_UART_puts("\n\rReceived data from user LL:\n\r");
		API_IO_UART_putint(input->functie);
		API_IO_UART_puts(" ");
		API_IO_UART_putint(input->startx);
		API_IO_UART_puts(" ");
		API_IO_UART_putint(input->starty);
		API_IO_UART_puts(" ");
		API_IO_UART_putint(input->breedte);
		API_IO_UART_puts(" ");
		API_IO_UART_putint(input->hoogte);
		API_IO_UART_puts(" ");
		API_IO_UART_putint(input->kleur);
		API_IO_UART_puts(" ");
		API_IO_UART_putint(input->gevuld);
		API_IO_UART_puts(" \n\r");
#endif
		error = API_IO_rechthoek(input->startx, input->starty, input->breedte, input->hoogte, input->kleur, input->gevuld);
//		API_IO_UART_puts("\n\rError: \n\r");
//		API_IO_UART_putint(error);
		break;
	case BITMAP:
#ifdef DEBUG
		API_IO_UART_puts("\n\rReceived data from user:\n\r");
		API_IO_UART_putint(input->functie);
		API_IO_UART_puts(" ");
		API_IO_UART_putint(input->nr);
		API_IO_UART_puts(" ");
		API_IO_UART_putint(input->startx);
		API_IO_UART_puts(" ");
		API_IO_UART_putint(input->starty);
		API_IO_UART_puts(" \n\r");
#endif
		error = API_DRAW_bitmap(input->nr, input->startx, input->starty, input->achtergrond);
//		API_IO_UART_puts("\n\rError: \n\r");
//		API_IO_UART_putint(error);
		break;

	case CLEARSCHERM:
#ifdef DEBUG
		API_IO_UART_puts("\n\rReceived data from user:\n\r");
		API_IO_UART_putint(input->functie);
		API_IO_UART_puts(" ");
		API_IO_UART_putint(input->kleur);
		API_IO_UART_puts(" \n\r");
#endif
		API_IO_clearscherm(input->kleur);
	}
	return error;
}

