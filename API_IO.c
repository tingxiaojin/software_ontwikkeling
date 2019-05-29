#include "includes.h"
#include "Arial.h"


///////////////////////////////////////////
 // init
//////////////////////////////////////////
void API_io_init()
{
	SystemInit(); 			// System speed to 168MHz
	UB_VGA_Screen_Init(); 	// Init VGA-Screen
//	LCD_init();
	DELAY_init();
	UART_init();
	UART_INT_init();
}

void  API_io_UART_INT_init(void)
{
	UART_INT_init();
}

///////////////////////////////////////////
 // errors
//////////////////////////////////////////
int  API_io_ERROR_inrange (int startx, int starty, int eindx, int eindy)
{
	int error=0;
	if((startx>VGA_DISPLAY_X)||(startx<0)||(eindx>VGA_DISPLAY_X)||(eindx<0)) error|=FOUTX;
	if((starty>VGA_DISPLAY_Y)||(starty<0)||(eindy>VGA_DISPLAY_Y)||(eindy<0)) error|=FOUTY;
	return error;
}


///////////////////////////////////////////
 // delays
//////////////////////////////////////////
void API_io_DELAY_us(unsigned int x)
{
	DELAY_us(x);
}

void API_io_DELAY_ms(unsigned int x)
{
	DELAY_ms(x);
}

void API_io_DELAY_s(unsigned int x)
{
	DELAY_s(x);
}




///////////////////////////////////////////
 // uart
///////////////////////////////////////////
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


void API_io_UART_gets(char* buffer)
{
	UART_gets(buffer, FALSE);
}


char API_io_UART_get()
{
	return UART_get();
}



void API_io_UART_puts(char* buffer)
{
	UART_puts(buffer);
}


void API_io_UART_putchar(char c)
{
	UART_putchar(c);
}


void API_io_UART_putint(int num)
{
	UART_putint(num);
}

void API_io_UART_putnum(unsigned int num, unsigned char deel)
{
	UART_putnum(num, deel);
}

///////////////////////////////////////////
 // tekst
///////////////////////////////////////////


//// replaces a character in a buffer with another character
//void UI_CH_rp(char* buffer, char old_char, char new_char)
//{
//	int i;
//	while (*(buffer++) != '\0')
//	{
//		if(*(buffer-1)=='\'')
//			for(i=0; i<200; i++)				// for loops are safer then while loops
//				if(*(buffer++) == '\'')break;
//
//		if(*(buffer)==old_char)
//		{
//			*buffer = new_char;
//			buffer++;
//		}
//	}
//}
//
//void UI_CH_rm(char* buffer, char c, char stopc)
//{
//	int i, j=0;
//
//	while (*(buffer) != stopc)
//	{
//		if (*(buffer+j-1) == '\'')
//			for(i=0;i<200; i++) //while(1) 	// for loops are safer then while loops
//			{
//				*(buffer) = *(buffer+j);
//				if(*(++buffer+j) == '\'') break;
//			}
//
//		for(i=0;*(buffer+j)==c && i<200; i++) j++; // for loops are safer then while loops
//		*(buffer) = *(buffer+j);
//		buffer++;
//	}
//}


// replaces a character in a buffer with another character
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


/*
 * note: removes characters until stopc found
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

int API_io_putc(char c, int x, int y, int kleur, int achtergrond)
{
	int i,j,k;//, error;
	int start, stop;


	c = c-' ';
	start = C_arial_16ptDescriptors[(int)c][1];
	stop  = (c == TEKENS-1)? sizeof(C_arial_16ptBitmaps):C_arial_16ptDescriptors[(int)c+1][1];

	for(i=0; start<stop; start+=C_arial_16ptDescriptors[(int)c][0], i++)
	{
		for(k=0; k<C_arial_16ptDescriptors[(int)c][0]; k++)
		{
			for(j=0; j<BIT; j++)
			{
				int test = 0x80>>j & C_arial_16ptBitmaps[start+k];
				if(test)
					UB_VGA_SetPixel((BIT*k)+j+x, y, kleur);
				else if(achtergrond != -1)
					UB_VGA_SetPixel((BIT*k)+j+x, y, achtergrond);
			}
		}
		y++;
	}
	return 0;
}


int API_io_puts(char* zin, int x_lup, int y_lup, int kleur, char* font, int fontgrootte, int fonststyle, int reserved)
{

	int i, error=0;
	int x = x_lup;
	int y = y_lup;
	error = API_io_putc(*(zin), x, y, kleur, reserved);

	for(i=1; i<strlen(zin); i++)
	{
		error = API_io_ERROR_inrange(x, y, x+(8*C_arial_16ptDescriptors[zin[i-1]-' '][0]), y+20);
		if (error == FOUTX){ y+=20;x=x_lup-(8*C_arial_16ptDescriptors[zin[i-1]-' '][0]);}
		else if(error == FOUTY) return error;

		error +=API_io_putc(*(zin+i), x+=(8*C_arial_16ptDescriptors[zin[i-1]-' '][0]), y, kleur, reserved);
	}

	//Hier moet je iets doen
	/*for(i=1; i<strlen(zin); i++)
	{
		error = API_io_ERROR_inrange(x, y, x+(8*arial_12ptDescriptors[zin[i-1]-' '][0]), y+20);
		if (error == FOUTX){ y+=20;x=x_lup-(8*arial_12ptDescriptors[zin[i-1]-' '][0]);}
		else if(error == FOUTY) return error;

		error +=API_io_putc(*(zin+i), x+=(8*arial_12ptDescriptors[zin[i-1]-' '][0]), y, kleur, reserved);
	}*/
	return error;
}


///////////////////////////////////////////
 // bitmap
//////////////////////////////////////////
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


///////////////////////////////////////////
 // clearscherm
//////////////////////////////////////////
void API_io_clearscherm(int kleur)
{
	UB_VGA_FillScreen(kleur);
}

///////////////////////////////////////////
 // figuren
//////////////////////////////////////////
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

