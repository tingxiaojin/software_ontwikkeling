/**
  ******************************************************************************
  * @file    LL.c
  * @author  SOFT_ONT groep 7
  * @version V1.0.5
  * @date    29-5-2019
  * @brief   Dit bestand biedt functionaliteit en High-level aansturing
  * 		 essentieel voor plaatsen van vormen en figuren op het VGA scherm (LL):
  *           - Inladen van figuren
  *           - Kleur string naar kleur integer waarde
  *           - String splitter
  *           - Uitvoeren van functies
  *
  *
  *  @verbatim
  *
  *          ===================================================================
  *			                        Plaatsen van figuren
  *          ===================================================================
  *
  *            Dit deel biedt informatie voor het laden van de vorm-structure
  *
  *            1. Gebruikt API_io_UART_gets() voor het ophalen van een string.
  *            2. Laat de string in LL_init(), dit laat het gewilde figuur in.
  *            3. Geef het geladen structure door aan LL_exe() om de commando uit te voeren.
  *
  * @note	De buffer moet aan een minimaal aantal parameters voldoen, afhankelijk per figuur.
  *
  * @note	Spaties worden standaard gewist, om spaties toch mogelijk te maken ivm de tekst-functie
  * 		moeten er aanhalingtekens('[zin]') aan het begin en eind van de zin staan.
  *
  *  @endverbatim
  */

#include "LL.h"
#include "API_DRAW.h"
#include "API_IO.h"


/**
  * @addtogroup LL
  * @brief LL driver modules
  * @{
  */

// Uncomment the following line
// if debug-mode is wanted:
//#define DEBUG


/** @addtogroup LL_string
  * @{
  * @addtogroup LL_string_functions
  * @{
  */

/**
  * @brief  Checkt of figuur-string in buffer-string staat.
  * @param  buffer: Pointer naar een string.
  * @param  figuur: String die gechekt moet worden op
  * 		overeenkomsten.
  * @retval String komt wel/niet overeen (TRUE/FALSE)
  */
int LL_STRING_check(char* buffer, char* figuur)
{
	int i;
	for(i=0;*(buffer+i)!='\0'; i++)
		*(buffer+i) = toupper(*(buffer+i));

	if(!(strncmp(buffer,figuur,strlen(figuur)))==TRUE)
		return TRUE;
	else
		return FALSE;
}



/**
  * @brief  Kleur-string naar kleur-integer converter.
  * @param  skleur: Pointer naar een string.
  * @retval 8-bit kleur waarde van de kleur in de string.
  */
int LL_STRING_kstoki(char* skleur)
{
	int i;
	int ikleur;
	char scol [][15] = {"GROEN","LICHTGROEN","ROOD","LICHTROOD","BLAUW","LICHTBLAUW","DEEPSKYBLUE","CYAAN","LICHTCYAAN",
			"MAGENTA","LICHTMAGENTA","GEEL","BRUIN","GRIJS","ZWART","WIT","ROZE","PAARS"};
	int icol [] = {VGA_COL_GREEN, VGA_COL_LIGHTGREEN, VGA_COL_RED, VGA_COL_LIGHTRED, VGA_COL_BLUE, VGA_COL_LIGHTBLUE,
			VGA_COL_DEEPSKYBLUE, VGA_COL_CYAN, VGA_COL_LIGHTCYAN, VGA_COL_MAGENTA, VGA_COL_LIGHTMAGENTA,VGA_COL_YELLOW,
			VGA_COL_BROWN,VGA_COL_GREY,VGA_COL_BLACK,VGA_COL_WHITE, VGA_COL_PINK, VGA_COL_PURPLE};

	for (i=0; i<sizeof(scol); i++)
		if(LL_STRING_check(skleur,(void*)scol[i]))
		{
			ikleur = icol[i];
			break;
		}
		else
			ikleur = 0;
	return ikleur;
}

/**
  * @brief  Geeft de begin pointer van de paramnum-ste
  * 		parameter.
  * @param  buffer: Pointer naar een string.
  * @param  paramnum: n-ste parameter.
  * @retval char pointer van het begin van de n-ste
  * 		parameter in buffer.
  */
char* LL_STRING_param(char* buffer, int paramnum)
{
	int i;
	for(;paramnum>0; paramnum--)
	{
		for (i=0; *buffer!='\0'; i++, buffer++);
		buffer++;
		if(i>200) return (void*)0;
	}
	return buffer;
}

/**
  * @}
  * @}
  */

/**
  * @addtogroup LL_print_figuren
  * @{
  */

/**
  * @brief  Zet parameters van buffer over
  * 		in de input structure op de bijhorende
  * 		variabelen.
  * @param  buffer: Pointer naar een string.
  * @param  input: input structure.
  * @param  vorm: integer waarde van vorm.
  * @retval None
  */
void LL_FIG_init(char* buffer, FUNCTIE* input, int vorm)
{
	switch(vorm)
	{
	case LIJN:
		input->functie = LIJN;
		input->startx  = atoi(LL_STRING_param(&buffer[0], PARAM1));
		input->starty  = atoi(LL_STRING_param(&buffer[0], PARAM2));
		input->eindx   = atoi(LL_STRING_param(&buffer[0], PARAM3));
		input->eindy   = atoi(LL_STRING_param(&buffer[0], PARAM4));
		input->kleur   = 	  LL_STRING_param(&buffer[0], PARAM5) ;
		input->dikte   = atoi(LL_STRING_param(&buffer[0], PARAM6));
		break;

	case RECHTHOEK:
		input->functie = RECHTHOEK;
		input->startx  = atoi(LL_STRING_param(&buffer[0], PARAM1));
		input->starty  = atoi(LL_STRING_param(&buffer[0], PARAM2));
		input->breedte = atoi(LL_STRING_param(&buffer[0], PARAM3));
		input->hoogte  = atoi(LL_STRING_param(&buffer[0], PARAM4));
		input->kleur   = 	  LL_STRING_param(&buffer[0], PARAM5) ;
		input->gevuld  = atoi(LL_STRING_param(&buffer[0], PARAM6));
		break;

	case TEKST:
		input->functie 		= TEKST;
		input->startx  		= atoi(LL_STRING_param(&buffer[0], PARAM1));
		input->starty  		= atoi(LL_STRING_param(&buffer[0], PARAM2));
		input->kleur   		= 	   LL_STRING_param(&buffer[0], PARAM3) ;
		input->tekst   		= 	   LL_STRING_param(&buffer[0], PARAM4) ;
		input->font	   		= 	   LL_STRING_param(&buffer[0], PARAM5) ;
		input->fontgrootte	= atoi(LL_STRING_param(&buffer[0], PARAM6));
		input->fontstijl	= atoi(LL_STRING_param(&buffer[0], PARAM7));
		input->achtergrond	= atoi(LL_STRING_param(&buffer[0], PARAM8));
		break;

	case BITMAP:
		input->functie= BITMAP;
		input->nr 	  = 	  atoi(LL_STRING_param(&buffer[0], PARAM1));
		input->startx = 	  atoi(LL_STRING_param(&buffer[0], PARAM2));
		input->starty = 	  atoi(LL_STRING_param(&buffer[0], PARAM3));
		input->achtergrond = (atoi(LL_STRING_param(&buffer[0], PARAM4))==TRUE)? 0:1;
		break;

	case CLEARSCHERM:
		input->functie   = CLEARSCHERM;
		input->kleur	 = LL_STRING_param(&buffer[0], PARAM1);
		break;

	case WACHT:
		input->functie= WACHT;
		input->ms =  atoi(LL_STRING_param(&buffer[0], PARAM1));
		break;

	case FIGUUR:
//		int *ploader = &input->startx;
//		int i;
		input->functie=FIGUUR;
		input->dikte  =1;
//		for(i=1; i<10; i++, ploader++)
//			*ploader = atoi(LL_STRING_param(&buffer[0], i));
		input->startx = atoi(LL_STRING_param(&buffer[0], PARAM1));
		input->starty = atoi(LL_STRING_param(&buffer[0], PARAM2));
		input->startx2= atoi(LL_STRING_param(&buffer[0], PARAM3));
		input->starty2= atoi(LL_STRING_param(&buffer[0], PARAM4));
		input->startx3= atoi(LL_STRING_param(&buffer[0], PARAM5));
		input->starty3= atoi(LL_STRING_param(&buffer[0], PARAM6));
		input->startx4= atoi(LL_STRING_param(&buffer[0], PARAM7));
		input->starty4= atoi(LL_STRING_param(&buffer[0], PARAM8));
		input->startx5= atoi(LL_STRING_param(&buffer[0], PARAM9));
		input->starty5= atoi(LL_STRING_param(&buffer[0], PARAM10));
		input->kleur  = 	 LL_STRING_param(&buffer[0], PARAM11 );
		input->startx6= input->startx;
		input->starty6= input->starty;
		break;

	case NLFLAG:
		input->functie=NLFLAG;
		break;

	case ITFLAG:
		input->functie=ITFLAG;
		break;

	case TOREN:
		input->functie=TOREN;
		input->startx= atoi(LL_STRING_param(&buffer[0], PARAM1));
		input->starty= atoi(LL_STRING_param(&buffer[0], PARAM2));
		input->kleur = 		LL_STRING_param(&buffer[0], PARAM3) ;
		break;
	}

}


/**
  * @brief  Voert de ingeladen functie uit.
  * @param  input: input structure.
  * @retval Foutmelding
  */
int LL_FIG_exe(FUNCTIE* input)
{
	int error=0;
	int i,j;		// maak toren
	int*pstartx= &input->startx;
	int*pstarty= &input->starty;

	switch(input->functie)
	{
	case LIJN:

#ifdef DEBUG
		API_io_UART_puts("\n\rReceived data from user LL:\n\r");
		API_io_UART_putint(input->functie);
		API_io_UART_puts(" ");
		API_io_UART_putint(input->startx);
		API_io_UART_puts(" ");
		API_io_UART_putint(input->starty);
		API_io_UART_puts(" ");
		API_io_UART_putint(input->eindx);
		API_io_UART_puts(" ");
		API_io_UART_putint(input->eindy);
		API_io_UART_puts(" ");
		API_io_UART_puts(input->kleur);
		API_io_UART_puts(" ");
		API_io_UART_putint(input->dikte);
		API_io_UART_puts(" \n\r");
#endif
		if(input->parameters < PARAM6) return TOOLITTLEPARAM;
		error = API_draw_line(input->startx, input->starty, input->eindx, input->eindy, LL_STRING_kstoki(input->kleur), input->dikte, 0);
		break;

	case RECHTHOEK:
#ifdef DEBUG
		API_io_UART_puts("\n\rReceived data from user LL:\n\r");
		API_io_UART_putint(input->functie);
		API_io_UART_puts(" ");
		API_io_UART_putint(input->startx);
		API_io_UART_puts(" ");
		API_io_UART_putint(input->starty);
		API_io_UART_puts(" ");
		API_io_UART_putint(input->breedte);
		API_io_UART_puts(" ");
		API_io_UART_putint(input->hoogte);
		API_io_UART_puts(" ");
		API_io_UART_puts(input->kleur);
		API_io_UART_puts(" ");
		API_io_UART_putint(input->gevuld);
		API_io_UART_puts(" \n\r");
#endif
		if(input->parameters < PARAM6) return TOOLITTLEPARAM;
		error = API_draw_rectangle(input->startx, input->starty, input->breedte,
				input->hoogte, LL_STRING_kstoki(input->kleur), input->gevuld, 0, 0);
		break;

	case TEKST:
#ifdef DEBUG
		API_io_UART_puts("\n\rReceived data from user LL:\n\r");
		API_io_UART_putint(input->functie);
		API_io_UART_puts(" ");
		API_io_UART_putint(input->startx);
		API_io_UART_puts(" ");
		API_io_UART_putint(input->starty);
		API_io_UART_puts(" ");
		API_io_UART_puts(input->kleur);
		API_io_UART_puts(" ");
		API_io_UART_puts(input->tekst);
		API_io_UART_puts(" ");
		API_io_UART_puts(input->font);
		API_io_UART_puts(" ");
		API_io_UART_putint(input->fontgrootte);
		API_io_UART_puts(" ");
		API_io_UART_putint(input->fontstijl);
		API_io_UART_puts(" \n\r");
#endif
		if(input->parameters < PARAM8) return TOOLITTLEPARAM; // error handling (func niet uitvoeren als fout)
		error = API_draw_text(input->startx, input->starty, LL_STRING_kstoki(input->kleur),
				input->tekst, input->font, input->fontgrootte, input->fontstijl, input->achtergrond);
		break;

	case BITMAP:
#ifdef DEBUG
		API_io_UART_puts("\n\rReceived data from user:\n\r");
		API_io_UART_putint(input->functie);
		API_io_UART_puts(" ");
		API_io_UART_putint(input->nr);
		API_io_UART_puts(" ");
		API_io_UART_putint(input->startx);
		API_io_UART_puts(" ");
		API_io_UART_putint(input->starty);
		API_io_UART_puts(" ");
		API_io_UART_putint(input->achtergrond);
		API_io_UART_puts(" \n\r");
#endif
		if(input->parameters < PARAM4) return TOOLITTLEPARAM;
		error = API_draw_bitmap(input->startx, input->starty, input->nr, input->achtergrond);
		break;

	case CLEARSCHERM:
#ifdef DEBUG
		API_io_UART_puts("\n\rReceived data from user:\n\r");
		API_io_UART_putint(input->functie);
		API_io_UART_puts(" ");
		API_io_UART_puts(input->kleur);
		API_io_UART_puts(" \n\r");
#endif
		if(input->parameters < PARAM1) return TOOLITTLEPARAM;
		API_io_clearscherm(LL_STRING_kstoki(input->kleur));
		break;

	case WACHT:
		if(input->parameters < PARAM1) return TOOLITTLEPARAM;
		API_io_DELAY_ms(input->ms);
		break;

	case FIGUUR:

		API_io_UART_putint(input->functie);
		for(i=0; i<5; i++)
		{
			API_io_UART_puts(" ");
			API_io_UART_putint(*(pstartx+i));
			API_io_UART_puts(" ");
			API_io_UART_putint(*(pstarty+i));
			error += API_draw_line(*(pstartx+i), *(pstarty+i), *(pstartx+i+1),
					*(pstarty+i+1), LL_STRING_kstoki(input->kleur), input->dikte, 0);
		}
		API_io_UART_puts(" ");
		API_io_UART_puts(input->kleur);
		API_io_UART_puts("\n\r");
		break;

	case NLFLAG:
		API_draw_rectangle(0,  0, 320, 80, VGA_COL_RED  , 0, 0, 0);
		API_draw_rectangle(0, 80, 320, 80, VGA_COL_WHITE, 0, 0, 0);
		API_draw_rectangle(0,160, 320, 80, VGA_COL_BLUE , 0, 0, 0);
		break;

	case ITFLAG:
		API_draw_clearscreen(VGA_COL_RED);
		API_draw_rectangle(0  , 0, 106, 240, VGA_COL_GREEN, 0, 0, 0);
		API_draw_rectangle(106, 0, 106, 240, VGA_COL_WHITE, 0, 0, 0);
		break;

	case TOREN:
		// Bloks
		API_draw_rectangle(input->startx   , input->starty		, 10, 20, LL_STRING_kstoki(input->kleur), 0, 0, 0);
		API_draw_rectangle(input->startx+25, input->starty		, 10, 20, LL_STRING_kstoki(input->kleur), 0, 0, 0);
		API_draw_rectangle(input->startx+50, input->starty		, 10, 20, LL_STRING_kstoki(input->kleur), 0, 0, 0);

		// Base structure
		API_draw_rectangle(input->startx	,input->starty+20	, 60, 20, LL_STRING_kstoki(input->kleur), 0, 0, 0);
		API_draw_rectangle(input->startx+15	,input->starty+40	, 30, 60, LL_STRING_kstoki(input->kleur), 0, 0, 0);
		API_draw_rectangle(input->startx	,input->starty+100	, 60, 40, LL_STRING_kstoki(input->kleur), 0, 0, 0);


		// Cosmetica
		for(j=0; j<40; j+=10)
			for(i=0; i<60; i+=10)
				API_draw_rectangle(input->startx+i, input->starty+100+j, 10, 10, VGA_COL_BLACK, 1, 0, 0);   // bakstenen

		for(j=0; j<60; j+=10)
			for(i=0; i<30; i+=10)
				API_draw_rectangle(input->startx+15+i, input->starty+40+j, 10, 10, VGA_COL_BLACK, 1, 0, 0); // bakstenen

		for(j=0; j<20; j+=10)
			for(i=0; i<60; i+=10)
				API_draw_rectangle(input->startx+i, input->starty+20+j, 10, 10, VGA_COL_BLACK, 1, 0, 0);    // bakstenen

		API_draw_line(input->startx   ,input->starty+100, input->startx+60, input->starty+100, VGA_COL_WHITE, 3 , 0);
		API_draw_line(input->startx+15, input->starty+40, input->startx+45, input->starty+40 , VGA_COL_WHITE, 3 , 0);
		break;

	}

	return error;
}

/**
  * @}
  */


/**
  * @}
  */
