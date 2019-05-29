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
#include "API_IO.h"
#include "API_DRAW.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"


//int API_DRAW_letter(int pos, int x_lup, int y_lup, int kleur){
//	/*
//		R: Declareer alle variabelen bovenaan de functie
//		dat geeft meer overzicht aan de lezer
//	*/
//	// R: start krijgt de waarde van het begin van de letter
//
////	pos -= ' ';
//	int start = arial_16ptDescriptors[pos][1]; // wel beetje lange naam
//	int stop;
//
//	//R: dus:
//	/*
//	int l = x_lup;
//	int i,j,k = 0;
//	*/
//
//	// R: Heb geen idee wat je hier doet...
//	if(pos == TEKENS-1)	//als (pos == 94-1), dan moet stop alle waardes in het array krijgen?
//						//print ie dan alle letters en karakters in de tabel?
//		stop = sizeof(arial_16ptBitmaps);
//	else // R: "stop" wordt gelijk aan het begin van de andere letter, dit snap ik
//		stop = arial_16ptDescriptors[pos+1][1];
//
//
//	API_IO_UART_puts("Start\tStop");
//	API_IO_UART_puts("\n\r");
//	API_IO_UART_putint(start);
//	API_IO_UART_puts("\t");
//	API_IO_UART_putint(stop);
//	API_IO_UART_puts("\n\r");
//
//
//	API_IO_UART_puts("\n\r");
//	API_IO_UART_putint(arial_16ptDescriptors[pos][0]-1);
//	API_IO_UART_puts("\n\r");
//	//R: dus niet hier declareren, maar voor de if-statment
//	int l = x_lup;
//	int i,j,k = 0;
//
//	//R: print letter, goed gedaan mvr. Jin!
//	for(i=start; i<stop; i++)
//	{
//		//R: Voor elke byte, check de één en nullen, nice!
//		for(j=0; j<8; j++)
//		{
//			if(0x80>>j & arial_16ptBitmaps[i]) // als dit 1 is put zwart
//				UB_VGA_SetPixel(l,y_lup, kleur);
//			//else							// als dit 0 is put niks of wit
//				//UB_VGA_SetPixel(l,y_lup, VGA_COL_WHITE);
//			l++;
//		}
//		if(k<arial_16ptDescriptors[pos][0]-1)
//		{ //R: overbodige bracket
//			k++;
//		} //R: overbodige bracket
//		else
//		{
//			l = x_lup;
//			y_lup++;
//			k = 0;
//		}
//	}
//	return 0;
//}
//
//
////R: Echt goede professionele naam!
//int API_DRAW_text(int x_lup, int y_lup, int kleur){ //R: Deze bracket hoort regel beneden te staan
////	{ (hier)
//	//R: Nice, hier heb je wel alle variabelen boven aan in de func gedeclareerd!
////	char __command[] = "TING XIAO is super cool :)!"; //R: haha, jazeker!
//	char __command[] = "H!";
//	int buffer;
//	int factor;
//	int pos;
//
//	int var;
//	for (var = 0; var < strlen(__command); var++) { //R: Deze bracket hoort regel beneden te staan
//	//  { (hier)
//		pos = __command[var] - ' '; //R: Wat?
////		pos = __command[var];
//		if(var == 0)
//			factor = 1;
//		else // factor wordt gelijk aan aantal bytes, oke snap ik... (ht kan wel strakker)
//			factor = arial_16ptDescriptors[buffer][0];
//
//		API_DRAW_letter(pos, x_lup += (8*factor), y_lup, kleur);
//		buffer = pos;
//	}
//
//	return 0;
//}



//int API_IO_putc(int c, int x_lup, int y_lup, int kleur, int achtergrond)
//{
//	c = c-' ';
//	int start = arial_16ptDescriptors[c]  [1]; // (zal het wel anders noemen)
//	int stop  = (c == TEKENS-1)? sizeof(arial_16ptDescriptors):arial_16ptDescriptors[c+1][1];
//	int i,j,k;
//
//	for(i=0; start<stop; start+=arial_16ptDescriptors[c][0], i++)
//	{
//		for(k=0; k<arial_16ptDescriptors[c][0]; k++)
//		{
//			for(j=0; j<BIT; j++) // brackets kunnen weg
//				if(0x80>>j & arial_16ptBitmaps[start+k])
//					UB_VGA_SetPixel((BIT*k)+j+x_lup, y_lup, kleur); //R: Maakt "l" overbodig
//				else if(achtergrond)
//					UB_VGA_SetPixel((BIT*k)+j+x_lup, y_lup, VGA_COL_WHITE);
//		}
//		y_lup ++;
//	}
//	return 0;
//}

//
//int API_DRAW_text(char* zin, int x_lup, int y_lup, int kleur, int achtergrond)
//{
//	int i, error=0;
///*
//	//R: Je had gelijk, strlen deed heel raar,
//	//hij verwacht een const char, zodra je
//	//een const char aanpast, zoals een spatie
//	//weg halen (' ') is het geen const meer
//	//en gaat iej raar doen, blijkbaar.
//	 * Zo losde ik het op :p
//*/
//
//	API_IO_putc(zin[0], x_lup, y_lup, kleur,achtergrond);
//	for (i=1; i< strlen(zin); i++)
//		error=API_IO_putc(zin[i], x_lup+=(8*(arial_16ptDescriptors[(int)(zin[i-1]-' ')][0])), y_lup, kleur,achtergrond);
//	return error;
//}


///*
// * return: on error NULL
// */
//char* LL_STRING_param(char* buffer, int paramnum)
//{
//	int i;
//	for(;paramnum>0; paramnum--)
//	{
//		for (i=0; *buffer!='\0'; i++, buffer++);
//		buffer++;
//		if(i>200) return (void*)0;
//	}
//	return buffer;
//}


int main(void)
{

//  uint32_t n;
	API_io_init();
	API_io_UART_INT_init();
//	int i;
//	SystemInit(); // System speed to 168MHz
//	UB_VGA_Screen_Init(); // Init VGA-Screen
//	LCD_init();
//	DELAY_init();
//	UART_init();

//	char buffer[50];

	API_io_clearscherm(VGA_COL_WHITE);
//	API_draw_line(200, 0, 0, 200, 50, 5, 0);
<<<<<<< HEAD
	API_draw_text(0,50,VGA_COL_WHITE, "!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_`abcdefghijklmnopqrstuvwxyz{|}","arial",1,1, VGA_COL_RED);
=======
	API_draw_text(0,50,VGA_COL_WHITE,"The quick brown fox jumps over the lazy dog",NULL,1,1, VGA_COL_RED);
>>>>>>> origin/API_ting
//	API_IO_clearscherm(VGA_COL_RED);

//	API_IO_UART_puts("\n\rCode done\n\r");
//	API_IO_line(0, 0, 319, 240, VGA_COL_BLUE, 1);
//	API_IO_rechthoek(50,50,200,170,VGA_COL_WHITE, RECHTHOEK_LEEG);
//
//
//	API_DRAW_bitmap(API_IO_PIJL_LINKS, 500,50, TRUE);
////	DELAY_ms(3000);
//	API_DRAW_bitmap(API_IO_PIJL_RECHTS, 20, 30, FALSE);
////	DELAY_ms(1000);
//	API_DRAW_bitmap(API_IO_PIJL_OMHOOG, 100, 20, TRUE);
////	DELAY_ms(1000);
//	API_DRAW_bitmap(API_IO_PIJL_OMLAAG, 80, 70, FALSE);
////	DELAY_ms(1000);
//	API_DRAW_bitmap(API_IO_SMILY_BLIJ,  80, 150, TRUE);
////	DELAY_ms(1000);
//	API_DRAW_bitmap(API_IO_SMILY_BOOS, 175, 70, FALSE);
////	API_draw_line(0, 0, 200, 200, VGA_COL_BLUE, 5);

char buffer[100];

//API_IO_UART_putchar(buffer[0]);

  while(1)
  {/*
	  // put the code here
//		API_IO_UART_gets(buffer);
//		API_IO_UART_putchar(buffer[1]);
//		API_IO_UART_puts(buffer);
//		API_IO_UART_puts("\n\r");
//		DELAY_s(1);
	  API_io_UART_INT_gets(buffer);
	  API_io_UART_puts(buffer);
//	  API_io_clearscherm(atoi(buffer));
	  API_io_rp_c(buffer, ',', '\0');
	  int red 	= atoi(LL_STRING_param(buffer,0));
	  int green = atoi(LL_STRING_param(buffer,1));
	  int blue 	= atoi(LL_STRING_param(buffer,2));
	  int bitval = (int)((((int)((float)red/(float)256*8))<<5) | (((int)((float)green/(float)256*8))<<2) | ((int)((float)blue/(float)256*4)));

	  if (strlen(buffer)!= 0)
	  {
		  API_io_UART_puts("RGB:\t8-bit val: \n\r");
		  API_io_UART_putint(red);
		  API_io_UART_puts(" ");
		  API_io_UART_putint(green);
		  API_io_UART_puts(" ");
		  API_io_UART_putint(blue);
		  API_io_UART_puts(" \t0x");
		  API_io_UART_putnum(bitval, 16);
		  API_io_UART_puts("\n\r\n\r");
		  API_io_clearscherm(bitval);
	  }
//	  if((string[strlen(string)-1]=='\n')&&(strlen(string) > 1))
//	  {
//		  API_IO_UART_puts(string);
//		  string[0] = '\0';
//		  charcounter = 0;
//	  }*/
  }
  //return 0;
}
