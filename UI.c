/**
  ******************************************************************************
  * @file    UI.c
  * @author  SOFT_ONT groep 7
  * @version V1.0.5
  * @date    29-5-2019
  * @brief   Dit bestand biedt string functies om de volgende GUI
  *          functionaliteiten te regelen (UI):
  *           - Error handling
  *           - Parameter teller
  *           - String opmaken
  */

//--------------------------------------------------------------


#include "UI.h"
#include "LL.h"
#include "API_IO.h"
#include "API_DRAW.h"

/** @addtogroup UI
  * @brief UI driver modules
  * @{
  */

/** @addtogroup UI_error
  * @brief Error functions
  * @{
  * @addtogroup UI_error_functions
  * {
  */




/**
  * @brief  Geeft error-code en betekenis aan gebruiker
  * 		terug via de UART.
  * @param  error: integer waarde van een error code.
  * @retval None
  */
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
/**
  * @}
  * @}
  */


/** @addtogroup UI_string
  * @brief String functions
  * @{
  * @addtogroup UI_string_functions
  * @{
  */

/**
  * @brief  Telt het aantal string-delen, gescheiden door sep.
  * @param  buffer: Pointer naar een string waarvan de parameters
  * 		   geteld moeten worden.
  * @param  sep: Char met de waarde waarmee de string gescheiden
  * 		   moet worden.
  * @retval Num of parameters in function.
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



/**
  * @brief  Vervangt old_char in een string met new_char
  * @param  buffer: Pointer naar een string waarvan de parameters
  * 		   geteld moeten worden.
  * @param  old_char: Char-waarde in de string die vervangen moet
  * 		   worden met new_char.
  * @param  new_char: Char-waarde waarmee old_char vervangen wordt.
  * @retval None
  */
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




/**
  * @brief 	Verwijderd een character in een string.
  * @param 	buffer: Pointer naar een string waarvan de character
  * 		verwijderd moet worden.
  * @param 	c: Char-waarde in de string die verwijderd moet
  * 		worden.
  * @param 	stopc: Char-waarde waar de functie moet stoppen met
  * 		verwijderen.
  * @retval None
  */
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

/**
  * @}
  */

/**
  * @}
  * @}
  */


int main(void)
{
	API_io_init();
//	API_io_UART_INT_init();
	API_draw_clearscreen(VGA_COL_BLACK);
	FUNCTIE input;
	char buffer [100];
	int error=-1;


//	API_io_UART_puts("WELKOM MIJN CODE :D\n\r");

	while(1)
	{
//		API_io_UART_INT_gets(buffer); // get user input
//		API_io_DELAY_s(5);
		API_io_UART_gets(buffer);
//		for(i=0; i<sizeof(buffer); i++)
//			API_io_UART_putchar(buffer[i]);
//		return 0;
//		if(strlen(buffer)==EMPTY)
//			continue;
//
//		// if input = empty
//		if(buffer[0] == CR)
//		{
//UI_STR_CR	error = STR_LEEG;
//			UI_ERR_put(error);
//			continue;
//		}

		UI_CH_rm		  (buffer, UI_STR_SPAT , UI_STR_T);			// remove spaces until first ST found
		input.parameters = UI_PARAMCNT(buffer, UI_STR_KOMMA);		// count the parameters
		UI_CH_rp		  (buffer, UI_STR_KOMMA, UI_STR_T); 		// replace comma's (',') with a ST ('\0')

		if (LL_STRING_check(buffer,"LIJN"))
		{
			LL_FIG_init(buffer, &input, LIJN);
			error = LL_FIG_exe(&input);
		}
		else if (LL_STRING_check(buffer,"RECHTHOEK"))
		{
			LL_FIG_init(buffer, &input, RECHTHOEK);
			error = LL_FIG_exe(&input);
		}
		else if (LL_STRING_check(buffer,"BITMAP"))
		{
			LL_FIG_init(buffer, &input, BITMAP);
			error = LL_FIG_exe(&input);
		}
		else if (LL_STRING_check(buffer,"CLEARSCHERM"))
		{
			LL_FIG_init(buffer, &input, CLEARSCHERM);
			error = LL_FIG_exe(&input);
		}
		else if (LL_STRING_check(buffer,"WACHT"))
		{
			LL_FIG_init(buffer, &input, WACHT);
			memset(buffer, 0, sizeof(buffer));
			error = LL_FIG_exe(&input);
		}
		else if (LL_STRING_check(buffer,"TEKST"))
		{
			LL_FIG_init(buffer, &input, TEKST);
			error = LL_FIG_exe(&input);
		}
		else if (LL_STRING_check(buffer,"FIGUUR"))
		{
			LL_FIG_init(buffer, &input, FIGUUR);
			error = LL_FIG_exe(&input);
		}
		else if (LL_STRING_check(buffer,"NL-FLAG"))
		{
			LL_FIG_init(buffer, &input, NLFLAG);
			error = LL_FIG_exe(&input);
		}
		else if (LL_STRING_check(buffer,"IT-FLAG"))
		{
			LL_FIG_init(buffer, &input, ITFLAG);
			error = LL_FIG_exe(&input);
		}
		else if (LL_STRING_check(buffer,"TOREN"))
		{
			LL_FIG_init(buffer, &input, TOREN);
			error = LL_FIG_exe(&input);
		}
		else
			error = INPUTERROR;

		UI_ERR_put(error);
	}
}
