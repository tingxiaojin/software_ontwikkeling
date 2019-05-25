
#include "UI.h"
#include "API_DRAW.h"
#include "API_IO.h"


#define DEBUG
//#define DEBUG_ERROR



int LL_STRING_check(char* input, char* figuur)
{
	int i;
	for(i=0;*(input+i)!='\0'; i++)
		*(input+i) = toupper(*(input+i));

	if(!(strncmp(input,figuur,strlen(figuur)))==TRUE)
		return TRUE;
	else
		return FALSE;
}


/*
 * Kleur-string to kleur-integer
 */
int LL_kstoki(char* skleur)
{
	int ikleur;
	if(LL_STRING_check(skleur,"GROEN"))
		ikleur = VGA_COL_GREEN;
	else if(LL_STRING_check(skleur,"LICHTGROEN"))
		ikleur = VGA_COL_LIGHTGREEN;
	else if(LL_STRING_check(skleur,"ROOD"))
		ikleur = VGA_COL_RED;
	else if(LL_STRING_check(skleur,"LICHTROOD"))
		ikleur = VGA_COL_LIGHTRED;
	else if(LL_STRING_check(skleur,"BLAUW"))
		ikleur = VGA_COL_BLUE;
	else if(LL_STRING_check(skleur,"LICHTBLAUW"))
		ikleur = VGA_COL_LIGHTBLUE;
	else if(LL_STRING_check(skleur,"CYAN"))
		ikleur = VGA_COL_CYAN;
	else if(LL_STRING_check(skleur,"LICHTCYAN"))
		ikleur = VGA_COL_LIGHTCYAN;
	else if(LL_STRING_check(skleur,"LICHTMAGENTA"))
		ikleur = VGA_COL_LIGHTMAGENTA;
	else if(LL_STRING_check(skleur,"GEEL"))
		ikleur = VGA_COL_YELLOW;
	else if(LL_STRING_check(skleur,"BRUIN"))
		ikleur = VGA_COL_BROWN;
	else if(LL_STRING_check(skleur,"GRIJS"))
		ikleur = VGA_COL_GREY;
	else if(LL_STRING_check(skleur,"ZWART"))
		ikleur = VGA_COL_BLACK;
	else if(LL_STRING_check(skleur,"WIT"))
		ikleur = VGA_COL_WHITE;
	return ikleur;
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
		input->kleur   = LL_STRING_param(&buffer[0], 5);
		input->dikte   = atoi(LL_STRING_param(&buffer[0], 6));
		break;

	case RECHTHOEK:
		input->functie = RECHTHOEK;
		input->startx  = atoi(LL_STRING_param(&buffer[0], 1));
		input->starty  = atoi(LL_STRING_param(&buffer[0], 2));
		input->breedte = atoi(LL_STRING_param(&buffer[0], 3));
		input->hoogte  = atoi(LL_STRING_param(&buffer[0], 4));
		input->kleur   = LL_STRING_param(&buffer[0], 5);
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
		input->kleur	 = LL_STRING_param(&buffer[0], 1);
		break;

	case WACHT:
		input->functie= WACHT;
		input->ms = atoi(LL_STRING_param(&buffer[0], 1));
		break;

	case FIGUUR:
//		int *ploader = &input->startx;
//		int i;
		input->functie=LIJN;
		input->kleur  =LL_STRING_param(&buffer[0], 11);
		input->dikte  =1;
//		for(i=1; i<10; i++, ploader++)
//			*ploader = atoi(LL_STRING_param(&buffer[0], i));
		input->startx=  atoi(LL_STRING_param(&buffer[0], 1));
		input->starty=  atoi(LL_STRING_param(&buffer[0], 2));
		input->startx2= atoi(LL_STRING_param(&buffer[0], 3));
		input->starty2= atoi(LL_STRING_param(&buffer[0], 4));
		input->startx3= atoi(LL_STRING_param(&buffer[0], 5));
		input->starty3= atoi(LL_STRING_param(&buffer[0], 6));
		input->startx4= atoi(LL_STRING_param(&buffer[0], 7));
		input->starty4= atoi(LL_STRING_param(&buffer[0], 8));
		input->startx5= atoi(LL_STRING_param(&buffer[0], 9));
		input->starty5= atoi(LL_STRING_param(&buffer[0], 10));
		break;
	}
}

int LL_exe(FUNCTIE* input)
{
	int error=0;
	int i;
	int*pstartx= &input->startx;
	int*pstarty= &input->starty;

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
		API_IO_UART_puts(input->kleur);
		API_IO_UART_puts(" ");
		API_IO_UART_putint(input->dikte);
		API_IO_UART_puts(" \n\r");
#endif

		error = API_DRAW_line(input->startx, input->starty, input->eindx, input->eindy, LL_kstoki(input->kleur), input->dikte);

#ifdef DEBUG_ERROR
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
		API_IO_UART_puts(input->kleur);
		API_IO_UART_puts(" ");
		API_IO_UART_putint(input->gevuld);
		API_IO_UART_puts(" \n\r");
#endif
		error = API_DRAW_rechthoek(input->startx, input->starty, input->breedte, input->hoogte, LL_kstoki(input->kleur), input->gevuld);
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
		API_IO_UART_puts(input->kleur);
		API_IO_UART_puts(" \n\r");
#endif
		API_IO_clearscherm(LL_kstoki(input->kleur));
		break;

	case WACHT:
		API_IO_DELAY_ms(input->ms);
		break;

	case FIGUUR:

		for(i=0; i<4; i++)
			error += API_DRAW_line(*(pstartx+i), *(pstarty+i), *(pstartx+i+1), *(pstarty+i+1), LL_kstoki(input->kleur), input->dikte);
		break;
	}

	return error;
}

