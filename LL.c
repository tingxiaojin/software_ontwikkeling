#include <UI.h>
#include "API_DRAW.h"
#include "API_IO.h"
#include "LL.h"

void LL_exe(FUNCTIE* input)
{
	switch(input->functie)
	{
	case LIJN:
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

		API_DRAW_line(input->startx, input->starty, input->eindx, input->eindy, input->kleur, input->dikte);
		break;
	}
}
