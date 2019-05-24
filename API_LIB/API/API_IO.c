#include "includes.h"
#include "Arial.h"

void API_IO_init()
{
	SystemInit(); 			// System speed to 168MHz
	UB_VGA_Screen_Init(); 	// Init VGA-Screen
//	LCD_init();
	DELAY_init();
	UART_init();
//	UART_INT_init();
}

char API_IO_UART_get()
{
	return UART_get();
}

void API_IO_UART_gets(char* buffer)
{
	UART_gets(buffer, FALSE);
}

void API_IO_UART_putint(int num)
{
	UART_putint(num);
}

void API_IO_UART_putnum(unsigned int num, unsigned char deel)
{
	UART_putnum(num, deel);
}

void API_IO_UART_putchar(char c)
{
	UART_putchar(c);
}


void API_IO_UART_puts(char* buffer)
{
	UART_puts(buffer);
}


int API_IO_putc(int c, int x_lup, int y_lup, int kleur, int achtergrond)
{
	int i,j,k;
	int start;
	int stop;

	c = c-' ';
	start = arial_16ptDescriptors[c]  [1]; // (zal het wel anders noemen)
	stop  = (c == TEKENS-1)? sizeof(arial_16ptDescriptors):arial_16ptDescriptors[c+1][1];


	for(i=0; start<stop; start+=arial_16ptDescriptors[c][0], i++)
	{
		for(k=0; k<arial_16ptDescriptors[c][0]; k++)
		{
			for(j=0; j<BIT; j++) // brackets kunnen weg
				if(0x80>>j & arial_16ptBitmaps[start+k])
					UB_VGA_SetPixel((BIT*k)+j+x_lup, y_lup, kleur); //R: Maakt "l" overbodig
				else if(achtergrond)
					UB_VGA_SetPixel((BIT*k)+j+x_lup, y_lup, VGA_COL_WHITE);
		}
		y_lup ++;
	}
	return 0;
}


void API_IO_bitmap(int x, int y, unsigned char* bitmap, int background)
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

void API_IO_clearscherm(int kleur)
{
	UB_VGA_FillScreen(kleur);
}

int API_IO_line(int startx, int starty, int eindx, int eindy, char kleur, int dikte)
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

int API_IO_rechthoek(int x, int y, int breedte, int hoogte, int kleur, int gevuld)
{
	breedte +=x;
	hoogte  +=y;

	switch(gevuld)
	{
	case RECHTHOEK_LEEG:
		API_IO_line(x, y, breedte,y, kleur, 1);
		API_IO_line(x, y, x, hoogte, kleur, 1);
		API_IO_line(breedte, hoogte, breedte,y, kleur, 1);
		API_IO_line(breedte, hoogte, x, hoogte, kleur, 1);
		break;
	case RECHTHOEK_GEVULD:
		for(;y<hoogte; y++)
			API_IO_line(x, y, breedte, y, kleur, 1);
		break;
	default:
		return 1;
	}
	return 0;
}


