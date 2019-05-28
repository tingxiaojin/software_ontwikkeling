

#include "UI.h"
#include "LL.h"
#include "API_IO.h"
#include "API_DRAW.h"



void UI_ERR_put(int error)
{
	if (!error) return;
	API_io_UART_puts("\n\rError: \n\r");
	switch(error)
	{
//	case 0: break; 	// alles verliep goed
	case FOUTX:
		API_io_UART_puts("\tX VALUE OVERSIZED!\n\rErrorcode: ");
		API_io_UART_putint(error);
		break;
	case FOUTY:
		API_io_UART_puts("\tY VALUE OVERSIZED!\n\rErrorcode: ");
		API_io_UART_putint(error);
		break;
	case FOUTOMVANG:
		API_io_UART_puts("\tBOTH X AND Y VALUE OVERSIZED!\n\rErrorcode: ");
		API_io_UART_putint(error);
		break;
	case INPUTERROR:
		API_io_UART_puts("\tINPUT UNRECOGNIZED!\n\rErrorcode: ");
		API_io_UART_putint(error);
		break;
	case STR_LEEG:
		API_io_UART_puts("\tINPUT EMPTY!\n\rErrorcode: ");
		API_io_UART_putint(error);
		break;
	case TOOMUCHPARAM:
		API_io_UART_puts("\tTO MUCH PARAMETERS! GIVE ME LESS\n\rErrorcode: ");
		API_io_UART_putint(error);
		break;
	case TOOLITTLEPARAM:
		API_io_UART_puts("\tTO LITTLE PARAMETERS! GIVE ME MORE\n\rErrorcode: ");
		API_io_UART_putint(error);
		break;
	default:
		API_io_UART_puts("\tUNKOWN ERRORCODE!\n\rErrorcode: 0x");
		API_io_UART_putnum(16, error);
	}
	API_io_UART_puts("\n\r");
}


/*
 * @Note: counts the num of param, seperated by the sep character
 * @Return: num of parameters in function
 */
int UI_PARAMCNT(char* buffer, char sep)
{
	int paramcnt, i;
	for(paramcnt=PARAM1; *buffer!='\0';buffer++)
	{
		if(*buffer=='\'')
			for(i=0; i<200; i++)				// for loops are safer then while loops
				if(*(buffer++) == '\'')break;

		paramcnt+= (*buffer == sep)? 1 : 0 ;
	}
	return paramcnt;
}

// replaces a character in a buffer with another character
void UI_CH_rp(char* buffer, char old_char, char new_char)
{
	int i;
	while (*(buffer++) != '\0')
	{
		if(*(buffer-1)=='\'')
			for(i=0; i<200; i++)				// for loops are safer then while loops
				if(*(buffer++) == '\'')break;

		if(*(buffer)==old_char)
		{
			*buffer = new_char;
			buffer++;
		}
	}
}

void UI_CH_rm(char* buffer, char c, char stopc)
{
	int i, j=0;

	while (*(buffer) != stopc)
	{
		if (*(buffer+j-1) == '\'')
			for(i=0;i<200; i++) //while(1) 	// for loops are safer then while loops
			{
				*(buffer) = *(buffer+j);
				if(*(++buffer+j) == '\'') break;
			}

		for(i=0;*(buffer+j)==c && i<200; i++) j++; // for loops are safer then while loops
		*(buffer) = *(buffer+j);
		buffer++;
	}
}

int main(void)
{
	API_io_init();
	API_io_UART_INT_init();
	API_draw_clearscreen(VGA_COL_BLACK);
	FUNCTIE input;
	char buffer [100];
	int error=-1;


	API_io_UART_puts("WELKOM MIJN CODE :D\n\r");
//	API_io_UART_putint(API_draw_line(1, 1, 1, 200, 50, 1));

	while(1)
	{
		API_io_UART_INT_gets(buffer); // get user input
//		API_io_UART_puts(buffer);

		if(strlen(buffer)==EMPTY)
			continue;

		// if input = empty
		if(buffer[0] == CR)
		{
			error = STR_LEEG;
			UI_ERR_put(error);
			continue;
		}

//		API_io_rm_c_ut	(buffer, ' ', ST);	// remove spaces until first ST found
//		API_io_rp_c		(buffer, ',', ST);	// replace comma's (',') with a ST ('\0')

		UI_CH_rm		  (buffer, ' ', ST);			// remove spaces until first ST found
		input.parameters = UI_PARAMCNT	(buffer, ',');	// count the parameters
		UI_CH_rp		  (buffer, ',', ST); 			// replace comma's (',') with a ST ('\0')

		if (LL_STRING_check(buffer,"LIJN"))
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
		else if (LL_STRING_check(buffer,"WACHT"))
		{
			LL_FIG_init(buffer, &input, WACHT);
			error = LL_exe(&input);
		}
		else if (LL_STRING_check(buffer,"TEKST"))
		{
			LL_FIG_init(buffer, &input, TEKST);
			error = LL_exe(&input);
		}
		else if (LL_STRING_check(buffer,"FIGUUR"))
		{
			LL_FIG_init(buffer, &input, FIGUUR);
			error = LL_exe(&input);
		}
		else if (LL_STRING_check(buffer,"NL-FLAG"))
		{
			LL_FIG_init(buffer, &input, NLFLAG);
			error = LL_exe(&input);
		}
		else if (LL_STRING_check(buffer,"IT-FLAG"))
		{
			LL_FIG_init(buffer, &input, ITFLAG);
			error = LL_exe(&input);
		}
		else if (LL_STRING_check(buffer,"TOREN"))
		{
			LL_FIG_init(buffer, &input, TOREN);
			error = LL_exe(&input);
		}
		else
			error = INPUTERROR;

		UI_ERR_put(error);
//		memset(buffer, 0, sizeof(buffer));

	}
}
