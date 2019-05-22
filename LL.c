#include "UI.h"
#include "API_DRAW.h"
#include "API_IO.h"

#define DEBUG

int LL_exe(FUNCTIE* input)
{
	int error=0;
	switch(input->functie)
	{
	case LIJN:

#ifdef DEBUG
		API_IO_UART_puts("\n\r");
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
//		API_IO_UART_putint(error);
		break;

	case RECHTHOEK:
#ifdef DEBUG
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
		API_IO_UART_putint(input->functie);
		API_IO_UART_puts(" ");
		API_IO_UART_putint(input->kleur);
		API_IO_UART_puts(" \n\r");
#endif
		API_IO_clearscherm(input->kleur);
	}
	return error;
}






