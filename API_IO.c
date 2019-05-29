/**
  ******************************************************************************
  * @file    API_IO.c
  * @author  SOFTONT groep 7
  * @version V1.0.1
  * @date    29-05-2019
  * @brief   Deze file bezit alle IO functies waarmee hardware-matig het
* 			 VGA-scherm wordt aangestuurd
  *
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/

#include "includes.h"
#include "Arial.h"

/** @addtogroup API
  * @{
  */

/** @defgroup API_IO
  * @brief IO-functies
  * @{
  */

/** @defgroup IO_init functies
  * @{
  */

/**
  * @brief  Deze functie voert alle init functies uit.
  * @note	De volgende onderdelen hebben een init nodig:
  * 		- system klok
  * 		- VGA-scherm
  * 		- delay
  * 		- uart
  * @param  void
  * @retval void
  */
/*API_io_init*/
void API_io_init()
{
	SystemInit(); 			// System speed to 168MHz
	UB_VGA_Screen_Init(); 	// Init VGA-Screen
	DELAY_init();
	UART_init();
	UART_INT_init();
}

/**
  * @brief  Deze functie voert een init voor de uart uit
  * @note   void
  * @param  void
  * @retval void
  */
void  API_io_UART_INT_init(void)
{
	UART_INT_init();
}
/**
  * @}
  */

/** @defgroup IO_error functies
  * @{
  */
/**
  * @brief  Deze functie bekijkt of de coordinaten van een figuur niet buiten het scherm vallen.
  * @note   Als de coordinaten buiten het scherm vallen zal deze functie een error meegegeven.
  * @param  startx: Dit argument geeft het x coordinaat van het beginpunt mee.
  * @param  starty: Dit argument geeft het y coordinaat van het beginpunt mee
  * @param  eindx: 	Dit argument geeft het x coordinaat van het eindpunt mee
  * @param  eindy:	Dit argument geeft het y coordinaat van het eindpunt mee
  * @retval int error
  */
int  API_io_ERROR_inrange (int startx, int starty, int eindx, int eindy)
{
	int error=0;
	if((startx>VGA_DISPLAY_X)||(startx<0)||(eindx>VGA_DISPLAY_X)||(eindx<0)) error|=FOUTX;
	if((starty>VGA_DISPLAY_Y)||(starty<0)||(eindy>VGA_DISPLAY_Y)||(eindy<0)) error|=FOUTY;
	return error;
}
/**
  * @}
  */


/** @defgroup IO_delay functies
  * @{
  */

/**
  * @brief  Deze functie voert een delay uit in us.
  * @note   Deze functie zorgt ervoor dat het programma wacht in microseconden.
  * @param  x:  Dit argument geeft de hoeveelheid microseconde er gewacht
  * 			moet worden.
  * @retval void
  */
void API_io_DELAY_us(unsigned int x)
{
	DELAY_us(x);
}

/**
  * @brief  Deze functie voert een delay uit in ms.
  * @note   Deze functie zorgt ervoor dat het programma wacht in miliseconden.
  * @param  x:  Dit argument geeft de hoeveelheid miliseconde er gewacht
  * 			moet worden.
  * @retval void
  */
void API_io_DELAY_ms(unsigned int x)
{
	DELAY_ms(x);
}

/**
  * @brief  Deze functie voert een delay uit in s.
  * @note   Deze functie zorgt ervoor dat het programma wacht in seconden.
  * @param  x:  Dit argument geeft de hoeveelheid seconde er gewacht
  * 			moet worden.
  * @retval void
  */
void API_io_DELAY_s(unsigned int x)
{
	DELAY_s(x);
}

/**
  * @}
  */

/** @defgroup IO_uart functies
  * @{
  */

/**
  * @brief  Deze functie laad de string in een buffer
  * @note   void
  * @param  buffer: Dit argument is een string.
  * @retval void
  */
void API_io_UART_INT_gets(char* buffer)
{
	if((string[strlen(string)-1]=='\n')&&(strlen(string) > 1))
	{
//		API_io_UART_puts(string);
		strcpy(buffer, string);
		string[0] = '\0';
		charcounter = 0;
	}
	else
		*buffer = '\0';
}

/**
  * @brief  Deze functie laadt strings op de uart in buffer
  * @note   void
  * @param  buffer: Dit argument is een string van de uart
  * @retval void
  */
void API_io_UART_gets(char* buffer)
{
	UART_gets(buffer, FALSE);
}

/**
  * @brief  Deze functie laadt een character van de uart
  * @note   void
  * @param  void
  * @retval char output van uart
  */
char API_io_UART_get()
{
	return UART_get();
}


/**
  * @brief  Deze functie print een string op de terminal
  * @note   void
  * @param  buffer: De string die geput gaat worden
  * @retval void
  */
void API_io_UART_puts(char* buffer)
{
	UART_puts(buffer);
}

/**
  * @brief  Deze functie print een charakter op de terminal
  * @note   void
  * @param  c: de charakter die geput wordt op de terminal
  * @retval void
  */
void API_io_UART_putchar(char c)
{
	UART_putchar(c);
}

/**
  * @brief  Deze functie print getallen integers op de terminal
  * @note   void
  * @param  num: de decimale waarde van het getal dat geprint wordt
  * @retval void
  */
void API_io_UART_putint(int num)
{
	UART_putint(num);
}

/**
  * @brief  Stuurt meegegeven getal uit op de UART in het aangegeven getallenstelsel
  * @note   void
  * @param  num: decimale getal
  * @param  deel: gewenste talstelsel
  * @retval void
  */
void API_io_UART_putnum(unsigned int num, unsigned char deel)
{
	UART_putnum(num, deel);
}
/**
  * @}
  */

/** @defgroup IO_string functies
  * @{
  */

/**
  * @brief 	Verandert een karakter in een buffer met een ander karakter
  * 		replaces a character in a buffer with another character
  * @note   void
  * @param  buffer: de string
  * @param  old_char: het karakter dat vervangen wordt
  * @param  new_char: het karakter dat geplaatst wordt
  * @retval void
  */
void API_io_rp_c(char* buffer, char old_char, char new_char)
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
  * @brief 	Loopt door een string heeft totdat het gewenste karakter is gevonden
  * @note   removes characters until stopc found
  * @param  buffer: de string
  * @param  c: wordt als buffer gebruikt om door de string heen te lopen
  * @param  stopc: het karakter gevonden moet worden
  * @retval void
  */
void  API_io_rm_c_ut(char* buffer, char c, char stopc)
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
  * @brief 	Maakt van een string alle kleine letters hoofdletter. Als dit al een hoofdletter was
  * 		blijft dit zo
  * @note   Deze functie wordt gebruikt voor uitlezen van het font(arial of consolas)
  * @param  input: de string
  * @param  font: string die gelezen moet worden.
  * @retval TRUE or FALSE
  */
int STRING_check(char* input, char* font)
{
	int i;
	for(i=0;*(input+i)!='\0'; i++)
		*(input+i) = toupper(*(input+i));

	if(!(strncmp(input,font,strlen(font)))==TRUE)
		return TRUE;
	else
		return FALSE;
}

/**
  * @brief  Deze functie kan een karakter op een VGA-scherm printen
  * @note   Deze functie print alleen één karakter op het scherm. Afhankelijk van de bitmap en description array
  * 		wordt bepaald welk font grootte en style toegepast gaat worden.
  * @param  c: Dit argument is het karakter dat geprint gaat worden.
  * @param  x: Dit argument geeft de x-waarde linksboven.
  * @param  y: Dit argument geeft de y-waarde linksboven.
  * @param  kleur: Dit argument geeft de kleur van de letter.
  * @param  achtergrond: Dit argument geeft de kleur de achtergrond
  * @param  bitmap: Dit argument geeft de bitmap met het juiste font mee
  * @param  description: Dit argument geeft de description met het juiste font mee
  * 					 Hierin staat hoeveel bytes lang een letter is en de offset
  * 					 in het bitmap array van elke letter.
  * @param  bitmap_size: Dit argument geeft de grootte van de bitmap mee
  * @retval int error
  */
int API_io_putc(char c, int x, int y, int kleur, int achtergrond, uint8_t* bitmap, int description[TEKENS][GEGEVENS], int bitmapsize)
{
	int i,j,k;//, error;
	int start, stop;


	c = c-' ';
	start = description[(int)c][1];										//bepaling startpositie in de bitmaparray
	stop  = (c == TEKENS-1)? sizeof(bitmap):description[(int)c+1][1];	//bepaling stoppositie in de bitmaparray

	for(i=0; start<stop; start+=description[(int)c][0], i++)
	{
		//k bekijkt of de letter breedte groter is dan 1 byte
		// zo ja moet de forloop met j meerdere keren printen
		for(k=0; k<description[(int)c][0]; k++)
		{
			for(j=0; j<BIT; j++)										//print per 8bits 8 pixels
			{
				int test = 0x80>>j & bitmap[start+k];
				if(test)
					UB_VGA_SetPixel((BIT*k)+j+x, y, kleur);				//letterkleur
				else if(achtergrond != -1)
					UB_VGA_SetPixel((BIT*k)+j+x, y, achtergrond);		//achtergrondkleur
			}
		}
		y++;
	}
	return 0;
}

/**
  * @brief  Deze functie kan een zin op een VGA-scherm printen
  * @note   API_io_putc wordt gebruikt om alle letters één voor één te printen van zin.
  * 		Verder wordt in een switchcase bepaald welk font meegegeven gaat worden aan
  * 		API_io_putc.
  * @param  zin: 		Dit argument is de string die op het scherm moet worden geprint
  * @param  x_lup: 		Dit argument geeft de x-waarde linksboven.
  * @param  y_lup: 		Dit argument geeft de y-waarde linksboven.
  * @param  kleur: 		Dit argument geeft de kleur van de letters.
  * @param  font: 		Dit argument is het gewenste font(arial/ consolas)
  * @param  fontgrootte:Dit argument geeft de grootte van het font mee (1/2)
  * @param  fontstyle: 	Dit argument geeft de style mee (standaar/vet/cursief)
  * @param  reserved: 	Dit argument mag gebruikt worden voor extra's
  * @retval int error
  */
int API_io_puts(char* zin, int x_lup, int y_lup, int kleur, char* font, int fontgrootte, int fontstyle, int reserved)
{

	int i, error=0;
	int x = x_lup;
	int y = y_lup;
	int state = DEFAULT;

	if(STRING_check(font, "arial"))
	{
		switch(fontstyle)
		{
			case 0 : //S
				if(fontgrootte == 1)//8pt
					state = 0;
				else				//16pt
					state = 3;
				break;
			case 1 :
				if(fontgrootte == 1)
					state = 1;
				else
					state = 4;
				break;
			case 2 :
				if(fontgrootte == 1)
					state = 2;
				else
					state = 5;
				break;
			default:
				error = 1;
				break;
		}
	}
	else
	{
		if(STRING_check(font, "consolas"))
		{
			switch(fontstyle)
			{
				case 0 :
					if(fontgrootte == 1)//8pt
						state = 6;
					else				//16pt
						state = 9;
					break;
				case 1 :
					if(fontgrootte == 1)
						state = 7;
					else
						state = 10;
					break;
				case 2 :
					if(fontgrootte == 1)
						state = 8;
					else
						state = 11;
					break;
				default:
					error = 1;
					break;
			}
		}
		else {
			error = 1;
		}
	}

	switch(state)
	{
		case 0: //arial, normaal, 8pt
			error = API_io_putc(*(zin), x, y, kleur, reserved, S_arial_8ptBitmaps, S_arial_8ptDescriptors, sizeof(S_arial_8ptBitmaps));
			for(i=1; i<strlen(zin); i++)
			{
				error = API_io_ERROR_inrange(x, y, x+(8*S_arial_8ptDescriptors[zin[i-1]-' '][0]), y+20);
				if 		(error == FOUTX){ y+=20;x=x_lup-(8*S_arial_8ptDescriptors[zin[i-1]-' '][0]);}
				else if	(error == FOUTY) return error;

				error |=API_io_putc(*(zin+i), x+=(8*S_arial_8ptDescriptors[zin[i-1]-' '][0]), y, kleur, reserved, S_arial_8ptBitmaps, S_arial_8ptDescriptors, sizeof(S_arial_8ptBitmaps));
			}
			break;
		case 1: //arial, vet, 8pt
			error = API_io_putc(*(zin), x, y, kleur, reserved, B_arial_8ptBitmaps, B_arial_8ptDescriptors, sizeof(B_arial_8ptBitmaps));
			for(i=1; i<strlen(zin); i++)
			{
				error = API_io_ERROR_inrange(x, y, x+(8*B_arial_8ptDescriptors[zin[i-1]-' '][0]), y+20);
				if 		(error == FOUTX){ y+=20;x=x_lup-(8*B_arial_8ptDescriptors[zin[i-1]-' '][0]);}
				else if	(error == FOUTY) return error;

				error |=API_io_putc(*(zin+i), x+=(8*B_arial_8ptDescriptors[zin[i-1]-' '][0]), y, kleur, reserved, B_arial_8ptBitmaps, B_arial_8ptDescriptors, sizeof(B_arial_8ptBitmaps));
			}
			break;
		case 2: //arial, cursief, 8pt
			error = API_io_putc(*(zin), x, y, kleur, reserved, C_arial_8ptBitmaps, C_arial_8ptDescriptors, sizeof(C_arial_8ptBitmaps));
			for(i=1; i<strlen(zin); i++)
			{
				error = API_io_ERROR_inrange(x, y, x+(8*C_arial_8ptDescriptors[zin[i-1]-' '][0]), y+20);
				if 		(error == FOUTX){ y+=20;x=x_lup-(8*C_arial_8ptDescriptors[zin[i-1]-' '][0]);}
				else if	(error == FOUTY) return error;

				error |=API_io_putc(*(zin+i), x+=(8*C_arial_8ptDescriptors[zin[i-1]-' '][0]), y, kleur, reserved, C_arial_8ptBitmaps, C_arial_8ptDescriptors, sizeof(C_arial_8ptBitmaps));
			}
			break;
		case 3: //arial, normaal, 16pt
			error = API_io_putc(*(zin), x, y, kleur, reserved, S_arial_16ptBitmaps, S_arial_16ptDescriptors, sizeof(S_arial_16ptBitmaps));
			for(i=1; i<strlen(zin); i++)
			{
				error = API_io_ERROR_inrange(x, y, x+(8*S_arial_16ptDescriptors[zin[i-1]-' '][0]), y+20);
				if 		(error == FOUTX){ y+=20;x=x_lup-(8*S_arial_16ptDescriptors[zin[i-1]-' '][0]);}
				else if	(error == FOUTY) return error;

				error |=API_io_putc(*(zin+i), x+=(8*S_arial_16ptDescriptors[zin[i-1]-' '][0]), y, kleur, reserved, S_arial_16ptBitmaps, S_arial_16ptDescriptors, sizeof(S_arial_16ptBitmaps));
			}
			break;
		case 4: //arial, vet, 16pt
			error = API_io_putc(*(zin), x, y, kleur, reserved, B_arial_16ptBitmaps, B_arial_16ptDescriptors, sizeof(B_arial_16ptBitmaps));
			for(i=1; i<strlen(zin); i++)
			{
				error = API_io_ERROR_inrange(x, y, x+(8*B_arial_16ptDescriptors[zin[i-1]-' '][0]), y+20);
				if 		(error == FOUTX){ y+=20;x=x_lup-(8*B_arial_16ptDescriptors[zin[i-1]-' '][0]);}
				else if	(error == FOUTY) return error;

				error |=API_io_putc(*(zin+i), x+=(8*B_arial_16ptDescriptors[zin[i-1]-' '][0]), y, kleur, reserved, B_arial_16ptBitmaps, B_arial_16ptDescriptors, sizeof(B_arial_16ptBitmaps));
			}
			break;
		case 5: //arial, cursief, 16pt
			error = API_io_putc(*(zin), x, y, kleur, reserved, C_arial_16ptBitmaps, C_arial_16ptDescriptors, sizeof(C_arial_16ptBitmaps));
			for(i=1; i<strlen(zin); i++)
			{
				error = API_io_ERROR_inrange(x, y, x+(8*C_arial_16ptDescriptors[zin[i-1]-' '][0]), y+20);
				if 		(error == FOUTX){ y+=20;x=x_lup-(8*C_arial_16ptDescriptors[zin[i-1]-' '][0]);}
				else if	(error == FOUTY) return error;

				error |=API_io_putc(*(zin+i), x+=(8*C_arial_16ptDescriptors[zin[i-1]-' '][0]), y, kleur, reserved, C_arial_16ptBitmaps, C_arial_16ptDescriptors, sizeof(C_arial_16ptBitmaps));
			}
			break;
		case 6: //consalas, normaal, 8pt
			error = API_io_putc(*(zin), x, y, kleur, reserved, S_consolas_8ptBitmaps, S_consolas_8ptDescriptors, sizeof(S_consolas_8ptBitmaps));
			for(i=1; i<strlen(zin); i++)
			{
				error = API_io_ERROR_inrange(x, y, x+(8*S_consolas_8ptDescriptors[zin[i-1]-' '][0]), y+20);
				if 		(error == FOUTX){ y+=20;x=x_lup-(8*S_consolas_8ptDescriptors[zin[i-1]-' '][0]);}
				else if	(error == FOUTY) return error;

				error |=API_io_putc(*(zin+i), x+=(8*S_consolas_8ptDescriptors[zin[i-1]-' '][0]), y, kleur, reserved, S_consolas_8ptBitmaps, S_consolas_8ptDescriptors, sizeof(S_consolas_8ptBitmaps));
			}
			break;
		case 7: //consalas, vet, 8pt
			error = API_io_putc(*(zin), x, y, kleur, reserved, S_consolas_8ptBitmaps, S_consolas_8ptDescriptors, sizeof(S_consolas_8ptBitmaps));
			for(i=1; i<strlen(zin); i++)
			{
				error = API_io_ERROR_inrange(x, y, x+(8*S_consolas_8ptDescriptors[zin[i-1]-' '][0]), y+20);
				if 		(error == FOUTX){ y+=20;x=x_lup-(8*S_consolas_8ptDescriptors[zin[i-1]-' '][0]);}
				else if	(error == FOUTY) return error;

				error |=API_io_putc(*(zin+i), x+=(8*S_consolas_8ptDescriptors[zin[i-1]-' '][0]), y, kleur, reserved, S_consolas_8ptBitmaps, S_consolas_8ptDescriptors, sizeof(S_consolas_8ptBitmaps));
			}
			break;
		case 8: //consalas, cursief, 8pt
			error = API_io_putc(*(zin), x, y, kleur, reserved, C_consolas_8ptBitmaps, C_consolas_8ptDescriptors, sizeof(C_consolas_8ptBitmaps));
			for(i=1; i<strlen(zin); i++)
			{
				error = API_io_ERROR_inrange(x, y, x+(8*C_consolas_8ptDescriptors[zin[i-1]-' '][0]), y+20);
				if 		(error == FOUTX){ y+=20;x=x_lup-(8*C_consolas_8ptDescriptors[zin[i-1]-' '][0]);}
				else if	(error == FOUTY) return error;

				error |=API_io_putc(*(zin+i), x+=(8*C_consolas_8ptDescriptors[zin[i-1]-' '][0]), y, kleur, reserved, C_consolas_8ptBitmaps, C_consolas_8ptDescriptors, sizeof(C_consolas_8ptBitmaps));
			}
			break;
		case 9: //consalas, normaal, 16pt
			error = API_io_putc(*(zin), x, y, kleur, reserved, S_consolas_16ptBitmaps, S_consolas_16ptDescriptors, sizeof(S_consolas_16ptBitmaps));
			for(i=1; i<strlen(zin); i++)
			{
				error = API_io_ERROR_inrange(x, y, x+(8*S_consolas_16ptDescriptors[zin[i-1]-' '][0]), y+20);
				if 		(error == FOUTX){ y+=20;x=x_lup-(8*S_consolas_16ptDescriptors[zin[i-1]-' '][0]);}
				else if	(error == FOUTY) return error;

				error |=API_io_putc(*(zin+i), x+=(8*S_consolas_16ptDescriptors[zin[i-1]-' '][0]), y, kleur, reserved, S_consolas_16ptBitmaps, S_consolas_16ptDescriptors, sizeof(S_consolas_16ptBitmaps));
			}
			break;
		case 10: //consalas, vet, 16pt
			error = API_io_putc(*(zin), x, y, kleur, reserved, B_consolas_16ptBitmaps, B_consolas_16ptDescriptors, sizeof(B_consolas_16ptBitmaps));
			for(i=1; i<strlen(zin); i++)
			{
				error = API_io_ERROR_inrange(x, y, x+(8*B_consolas_16ptDescriptors[zin[i-1]-' '][0]), y+20);
				if 		(error == FOUTX){ y+=20;x=x_lup-(8*B_consolas_16ptDescriptors[zin[i-1]-' '][0]);}
				else if	(error == FOUTY) return error;

				error |=API_io_putc(*(zin+i), x+=(8*B_consolas_16ptDescriptors[zin[i-1]-' '][0]), y, kleur, reserved, B_consolas_16ptBitmaps, B_consolas_16ptDescriptors, sizeof(B_consolas_16ptBitmaps));
			}
			break;
		case 11: //consalas, cursief, 16pt
			error = API_io_putc(*(zin), x, y, kleur, reserved, C_consolas_16ptBitmaps, C_consolas_16ptDescriptors, sizeof(C_consolas_16ptBitmaps));
			for(i=1; i<strlen(zin); i++)
			{
				error = API_io_ERROR_inrange(x, y, x+(8*C_consolas_16ptDescriptors[zin[i-1]-' '][0]), y+20);
				if 		(error == FOUTX){ y+=20;x=x_lup-(8*C_consolas_16ptDescriptors[zin[i-1]-' '][0]);}
				else if	(error == FOUTY) return error;

				error |=API_io_putc(*(zin+i), x+=(8*C_consolas_16ptDescriptors[zin[i-1]-' '][0]), y, kleur, reserved, C_consolas_16ptBitmaps, C_consolas_16ptDescriptors, sizeof(C_consolas_16ptBitmaps));
			}
			break;
		default:
			error = 1;
			break;
	}
	return error;
}
/**
  * @}
  */

/** @defgroup IO_bitmap functies
  * @{
  */

/**
  * @brief  Deze functie kan een bitmap op een VGA-scherm printen
  * @note   Er wordt een bitmaparray meegegeven aan de functie.
  * 		Daaruit kan de hoogte en de breedte worden gehaald
  * 		die met een dubbele forloop de bitmap kunnen printen
  * @param  x: 			Dit argument geeft de x-waarde linksboven.
  * @param  y: 			Dit argument geeft de y-waarde linksboven.
  * @param  bitmap:		Dit argument geeft het array mee van de juiste bitmap
  * @param  background: Dit argument geeft de kleur van de achtergrond
  * @retval void
  */
void API_io_bitmap(int x, int y, unsigned char* bitmap, int background)
{
	int i,j;
	unsigned int breedte = (unsigned int)(*(bitmap+0)|(*(bitmap+1)<<8)|(*(bitmap+2)<<16)|(*(bitmap+3)<<32));
	unsigned int hoogte  = (unsigned int)(*(bitmap+4)|(*(bitmap+5)<<8)|(*(bitmap+6)<<16)|(*(bitmap+7)<<32));
	for (j=0; j<hoogte; j++)
		for(i=0; i<breedte; i++)
			if((bitmap[j*breedte+i+8]!=0xFF) && (background == FALSE))
				UB_VGA_SetPixel(x+i,y+j, bitmap[j*breedte+i+8]);
			else if (background == TRUE)
				UB_VGA_SetPixel(x+i,y+j, bitmap[j*breedte+i+8]);
}
/**
  * @}
  */

/** @defgroup IO_clearscherm functies
  * @{
  */

/**
  * @brief  Deze functie maakt het hele scherm de gewenste kleur
  * @note   void
  * @param  kleur: dit argument geeft de kleur van scherm.
  * @retval void
  */
void API_io_clearscherm(int kleur)
{
	UB_VGA_FillScreen(kleur);
}
/**
  * @}
  */

/** @defgroup IO_figuren functies
  * @{
  */

/**
  * @brief  Deze functie put een lijn op het VGA-scherm
  * @note   Er wordt met behulp van y=ax+b een lijn getekend.
  * @param  startx: Dit argument geeft de x-waarde van het beginpunt.
  * @param  starty: Dit argument geeft de y-waarde van het beginpunt.
  * @param  eindx: 	Dit argument geeft de x-waarde van het eindpunt.
  * @param  eindy: 	Dit argument geeft de y-waarde van het eindpunt.
  * @param  kleur: Dit argument geeft de kleur van de lijn.
  * @param  dikte: Dit argument geeft de dikte van de lijn.
  * @retval int error
  */
int API_io_line(int startx, int starty, int eindx, int eindy, char kleur, int dikte)
{
  int x, y, i;
  float dx, dy, rc;


  dx = eindx - startx;
  dy = eindy - starty;
  rc  = dy/dx;


  for(i=dikte/2; dikte>0; i--, dikte--)
  {
	  if (fabs(rc)<=1)
		if (startx < eindx)
		  for (x=startx; x<eindx; x++)
		  {
			y = (int)(rc*(x-startx)+starty+i); // y = ax + b
			UB_VGA_SetPixel(x,y,kleur);
		  }
		else
		  for (x=eindx; x<startx; x++)
		  {
			y = (int)(rc*(x-startx)+starty+i); // y = ax + b
			UB_VGA_SetPixel(x,y-1,kleur);
		  }

	  else
		if (starty < eindy)
		  for (y=starty; y<eindy; y++)
		  {
			x = (int)((1/rc)*(y-starty)+startx+i); // x = (y - b)/a
			UB_VGA_SetPixel(x,y,kleur);
		  }
		else
		  for (y=eindy; y<starty; y++)
		  {
			x = (int)((1/rc)*(y-starty)+startx+i); // y = ax + b
			UB_VGA_SetPixel(x,y,kleur);
		  }
  }
  return 0;
}
/**
  * @brief  Deze functie tekent een rechthoek op het VGA-scherm
  * @note   afhankelijke van gevuld wordt het rechthoek met of zonder rand
  * 		gevuld= 0 -> rechthoek met rand
  * 		gevuld= 1 -> rechthoek gevuld zonder rand
  * @param  x: 		Dit argument geeft de x-waarde van het punt linksboven.
  * @param  y: 		Dit argument geeft de y-waarde van het punt linksboven.
  * @param  breedte:Dit argument geeft de breedte van de rechthoek
  * @param  hoogte: Dit argument geeft dehoogte van de rechthoek
  * @param  kleur: 	Dit argument geeft de kleur van de rechthoek
  * @param  gevuld: Dit argument geeft aan of de rechthoek een rand heeft of gevuld is
  * @retval 0
  */
int API_io_rechthoek(int x, int y, int breedte, int hoogte, int kleur, int gevuld)
{
	breedte +=x;
	hoogte  +=y;

	switch(gevuld)
	{
	case RECHTHOEK_LEEG:
		API_io_line(x, y, breedte,y, kleur, 1);
		API_io_line(x, y, x, hoogte, kleur, 1);
		API_io_line(breedte, hoogte, breedte,y, kleur, 1);
		API_io_line(breedte, hoogte, x, hoogte, kleur, 1);
		break;

	case RECHTHOEK_GEVULD:
		for(;y<hoogte; y++)
			API_io_line(x, y, breedte, y, kleur, 1);
		break;

	default:
		return 1;
	}
	return 0;
}
/**
  * @}
  */
/**
  * @}
  */
/**
  * @}
  */
