#include "includes.h"
#include "Arial.h"
#include "Consolas.h"


//////////////////////////////////////////////////////////////////////////////////////////////
// state 0
int API_io_putc_0(char c, int x, int y, int kleur, int achtergrond)
{
	int i,j,k;//, error;
	int start, stop;

	c = c-' ';
	start = S_arial_8ptDescriptors[(int)c][1];
	stop  = (c == TEKENS-1)? sizeof(S_arial_8ptBitmaps):S_arial_8ptDescriptors[(int)c+1][1];

	for(i=0; start<stop; start+=S_arial_8ptDescriptors[(int)c][0], i++)
	{
		for(k=0; k<S_arial_8ptDescriptors[(int)c][0]; k++)
		{
			for(j=0; j<BIT; j++)
			{
				int test = 0x80>>j & S_arial_8ptBitmaps[start+k];
				if(test)
					UB_VGA_SetPixel((BIT*k)+j+x, y, kleur);
				//else if(achtergrond != -1)
					//UB_VGA_SetPixel((BIT*k)+j+x, y, achtergrond);
			}
		}
		y++;
	}
	return 0;
}


int API_io_puts_0(char* zin, int x_lup, int y_lup, int kleur, int reserved)
{
	int i, error=0;
	int x = x_lup;
	int y = y_lup;
	error = API_io_putc_0(*(zin), x, y, kleur, reserved);

	for(i=1; i<strlen(zin); i++)
	{
		error = API_io_ERROR_inrange(x, y, x+(8*S_arial_8ptDescriptors[zin[i-1]-' '][0]), y+20);
		if 		(error == FOUTX){ y+=20;x=x_lup-(8*S_arial_8ptDescriptors[zin[i-1]-' '][0]);}
		else if	(error == FOUTY) return error;

		error |=API_io_putc_0(*(zin+i), x+=(8*S_arial_8ptDescriptors[zin[i-1]-' '][0]), y, kleur, reserved);
	}

	return error;
}


//////////////////////////////////////////////////////////////////////////////////////////////
// state 1
int API_io_putc_1(char c, int x, int y, int kleur, int achtergrond)
{
	int i,j,k;//, error;
	int start, stop;

	c = c-' ';
	start = S_arial_8ptDescriptors[(int)c][1];
	stop  = (c == TEKENS-1)? sizeof(S_arial_8ptBitmaps):S_arial_8ptDescriptors[(int)c+1][1];

	for(i=0; start<stop; start+=S_arial_8ptDescriptors[(int)c][0], i++)
	{
		for(k=0; k<S_arial_8ptDescriptors[(int)c][0]; k++)
		{
			for(j=0; j<BIT; j++)
			{
				int test = 0x80>>j & S_arial_8ptBitmaps[start+k];
				if(test)
					UB_VGA_SetPixel((BIT*k)+j+x, y, kleur);
				//else if(achtergrond != -1)
					//UB_VGA_SetPixel((BIT*k)+j+x, y, achtergrond);
			}
		}
		y++;
	}
	return 0;
}


int API_io_puts_1(char* zin, int x_lup, int y_lup, int kleur, int reserved)
{
	int i, error=0;
	int x = x_lup;
	int y = y_lup;
	error = API_io_putc_1(*(zin), x, y, kleur, reserved);

	for(i=1; i<strlen(zin); i++)
	{
		error = API_io_ERROR_inrange(x, y, x+(8*S_arial_8ptDescriptors[zin[i-1]-' '][0]), y+20);
		if 		(error == FOUTX){ y+=20;x=x_lup-(8*S_arial_8ptDescriptors[zin[i-1]-' '][0]);}
		else if	(error == FOUTY) return error;

		error |=API_io_putc_1(*(zin+i), x+=(8*S_arial_8ptDescriptors[zin[i-1]-' '][0]), y, kleur, reserved);
	}

	return error;
}


//////////////////////////////////////////////////////////////////////////////////////////////
// state 2
int API_io_putc_2(char c, int x, int y, int kleur, int achtergrond)
{
	int i,j,k;//, error;
	int start, stop;

	c = c-' ';
	start = C_arial_8ptDescriptors[(int)c][1];
	stop  = (c == TEKENS-1)? sizeof(C_arial_8ptBitmaps):C_arial_8ptDescriptors[(int)c+1][1];

	for(i=0; start<stop; start+=C_arial_8ptDescriptors[(int)c][0], i++)
	{
		for(k=0; k<C_arial_8ptDescriptors[(int)c][0]; k++)
		{
			for(j=0; j<BIT; j++)
			{
				int test = 0x80>>j & C_arial_8ptBitmaps[start+k];
				if(test)
					UB_VGA_SetPixel((BIT*k)+j+x, y, kleur);
				//else if(achtergrond != -1)
					//UB_VGA_SetPixel((BIT*k)+j+x, y, achtergrond);
			}
		}
		y++;
	}
	return 0;
}


int API_io_puts_2(char* zin, int x_lup, int y_lup, int kleur, int reserved)
{
	int i, error=0;
	int x = x_lup;
	int y = y_lup;
	error = API_io_putc_2(*(zin), x, y, kleur, reserved);

	for(i=1; i<strlen(zin); i++)
	{
		error = API_io_ERROR_inrange(x, y, x+(8*C_arial_8ptDescriptors[zin[i-1]-' '][0]), y+20);
		if 		(error == FOUTX){ y+=20;x=x_lup-(8*C_arial_8ptDescriptors[zin[i-1]-' '][0]);}
		else if	(error == FOUTY) return error;

		error |=API_io_putc_2(*(zin+i), x+=(8*C_arial_8ptDescriptors[zin[i-1]-' '][0]), y, kleur, reserved);
	}

	return error;
}

//////////////////////////////////////////////////////////////////////////////////
// state 3
int API_io_putc_3(char c, int x, int y, int kleur, int achtergrond)
{
	int i,j,k;//, error;
	int start, stop;

	c = c-' ';
	start = S_arial_16ptDescriptors[(int)c][1];
	stop  = (c == TEKENS-1)? sizeof(S_arial_16ptBitmaps):S_arial_16ptDescriptors[(int)c+1][1];

	for(i=0; start<stop; start+=S_arial_16ptDescriptors[(int)c][0], i++)
	{
		for(k=0; k<S_arial_16ptDescriptors[(int)c][0]; k++)
		{
			for(j=0; j<BIT; j++)
			{
				int test = 0x80>>j & S_arial_16ptBitmaps[start+k];
				if(test)
					UB_VGA_SetPixel((BIT*k)+j+x, y, kleur);
				//else if(achtergrond != -1)
					//UB_VGA_SetPixel((BIT*k)+j+x, y, achtergrond);
			}
		}
		y++;
	}
	return 0;
}


int API_io_puts_3(char* zin, int x_lup, int y_lup, int kleur, int reserved)
{
	int i, error=0;
	int x = x_lup;
	int y = y_lup;
	error = API_io_putc_3(*(zin), x, y, kleur, reserved);

	for(i=1; i<strlen(zin); i++)
	{
		error = API_io_ERROR_inrange(x, y, x+(8*S_arial_16ptDescriptors[zin[i-1]-' '][0]), y+20);
		if 		(error == FOUTX){ y+=20;x=x_lup-(8*S_arial_16ptDescriptors[zin[i-1]-' '][0]);}
		else if	(error == FOUTY) return error;

		error |=API_io_putc_3(*(zin+i), x+=(8*S_arial_16ptDescriptors[zin[i-1]-' '][0]), y, kleur, reserved);
	}

	return error;
}


//////////////////////////////////////////////////////////////////////////////////////////////
// state 4
int API_io_putc_4(char c, int x, int y, int kleur, int achtergrond)
{
	int i,j,k;//, error;
	int start, stop;

	c = c-' ';
	start = B_arial_16ptDescriptors[(int)c][1];
	stop  = (c == TEKENS-1)? sizeof(B_arial_16ptBitmaps):B_arial_16ptDescriptors[(int)c+1][1];

	for(i=0; start<stop; start+=B_arial_16ptDescriptors[(int)c][0], i++)
	{
		for(k=0; k<B_arial_16ptDescriptors[(int)c][0]; k++)
		{
			for(j=0; j<BIT; j++)
			{
				int test = 0x80>>j & B_arial_16ptBitmaps[start+k];
				if(test)
					UB_VGA_SetPixel((BIT*k)+j+x, y, kleur);
				//else if(achtergrond != -1)
					//UB_VGA_SetPixel((BIT*k)+j+x, y, achtergrond);
			}
		}
		y++;
	}
	return 0;
}


int API_io_puts_4(char* zin, int x_lup, int y_lup, int kleur, int reserved)
{
	int i, error=0;
	int x = x_lup;
	int y = y_lup;
	error = API_io_putc_4(*(zin), x, y, kleur, reserved);

	for(i=1; i<strlen(zin); i++)
	{
		error = API_io_ERROR_inrange(x, y, x+(8*B_arial_16ptDescriptors[zin[i-1]-' '][0]), y+20);
		if 		(error == FOUTX){ y+=20;x=x_lup-(8*B_arial_16ptDescriptors[zin[i-1]-' '][0]);}
		else if	(error == FOUTY) return error;

		error |=API_io_putc_4(*(zin+i), x+=(8*B_arial_16ptDescriptors[zin[i-1]-' '][0]), y, kleur, reserved);
	}

	return error;
}


//////////////////////////////////////////////////////////////////////////////////////////////
// state 5
int API_io_putc_5(char c, int x, int y, int kleur, int achtergrond)
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
				//else if(achtergrond != -1)
					//UB_VGA_SetPixel((BIT*k)+j+x, y, achtergrond);
			}
		}
		y++;
	}
	return 0;
}


int API_io_puts_5(char* zin, int x_lup, int y_lup, int kleur, int reserved)
{
	int i, error=0;
	int x = x_lup;
	int y = y_lup;
	error = API_io_putc_5(*(zin), x, y, kleur, reserved);

	for(i=1; i<strlen(zin); i++)
	{
		error = API_io_ERROR_inrange(x, y, x+(8*C_arial_16ptDescriptors[zin[i-1]-' '][0]), y+20);
		if 		(error == FOUTX){ y+=20;x=x_lup-(8*C_arial_16ptDescriptors[zin[i-1]-' '][0]);}
		else if	(error == FOUTY) return error;

		error |=API_io_putc_5(*(zin+i), x+=(8*C_arial_16ptDescriptors[zin[i-1]-' '][0]), y, kleur, reserved);
	}

	return error;
}


//////////////////////////////////////////////////////////////////////////////////////////////
// state 6
int API_io_putc_6(char c, int x, int y, int kleur, int achtergrond)
{
	int i,j,k;//, error;
	int start, stop;

	c = c-' ';
	start = S_consolas_8ptDescriptors[(int)c][1];
	stop  = (c == TEKENS-1)? sizeof(S_consolas_8ptBitmaps):S_consolas_8ptDescriptors[(int)c+1][1];

	for(i=0; start<stop; start+=S_consolas_8ptDescriptors[(int)c][0], i++)
	{
		for(k=0; k<S_consolas_8ptDescriptors[(int)c][0]; k++)
		{
			for(j=0; j<BIT; j++)
			{
				int test = 0x80>>j & S_consolas_8ptBitmaps[start+k];
				if(test)
					UB_VGA_SetPixel((BIT*k)+j+x, y, kleur);
				//else if(achtergrond != -1)
					//UB_VGA_SetPixel((BIT*k)+j+x, y, achtergrond);
			}
		}
		y++;
	}
	return 0;
}


int API_io_puts_6(char* zin, int x_lup, int y_lup, int kleur, int reserved)
{
	int i, error=0;
	int x = x_lup;
	int y = y_lup;
	error = API_io_putc_6(*(zin), x, y, kleur, reserved);

	for(i=1; i<strlen(zin); i++)
	{
		error = API_io_ERROR_inrange(x, y, x+(8*S_consolas_8ptDescriptors[zin[i-1]-' '][0]), y+20);
		if 		(error == FOUTX){ y+=20;x=x_lup-(8*S_consolas_8ptDescriptors[zin[i-1]-' '][0]);}
		else if	(error == FOUTY) return error;

		error |=API_io_putc_6(*(zin+i), x+=(8*S_consolas_8ptDescriptors[zin[i-1]-' '][0]), y, kleur, reserved);
	}

	return error;
}


//////////////////////////////////////////////////////////////////////////////////////////////
// state 7
int API_io_putc_7(char c, int x, int y, int kleur, int achtergrond)
{
	int i,j,k;//, error;
	int start, stop;

	c = c-' ';
	start = B_consolas_8ptDescriptors[(int)c][1];
	stop  = (c == TEKENS-1)? sizeof(B_consolas_8ptBitmaps):B_consolas_8ptDescriptors[(int)c+1][1];

	for(i=0; start<stop; start+=B_consolas_8ptDescriptors[(int)c][0], i++)
	{
		for(k=0; k<B_consolas_8ptDescriptors[(int)c][0]; k++)
		{
			for(j=0; j<BIT; j++)
			{
				int test = 0x80>>j & B_consolas_8ptBitmaps[start+k];
				if(test)
					UB_VGA_SetPixel((BIT*k)+j+x, y, kleur);
				//else if(achtergrond != -1)
					//UB_VGA_SetPixel((BIT*k)+j+x, y, achtergrond);
			}
		}
		y++;
	}
	return 0;
}


int API_io_puts_7(char* zin, int x_lup, int y_lup, int kleur, int reserved)
{
	int i, error=0;
	int x = x_lup;
	int y = y_lup;
	error = API_io_putc_7(*(zin), x, y, kleur, reserved);

	for(i=1; i<strlen(zin); i++)
	{
		error = API_io_ERROR_inrange(x, y, x+(8*B_consolas_8ptDescriptors[zin[i-1]-' '][0]), y+20);
		if 		(error == FOUTX){ y+=20;x=x_lup-(8*B_consolas_8ptDescriptors[zin[i-1]-' '][0]);}
		else if	(error == FOUTY) return error;

		error |=API_io_putc_7(*(zin+i), x+=(8*B_consolas_8ptDescriptors[zin[i-1]-' '][0]), y, kleur, reserved);
	}

	return error;
}


//////////////////////////////////////////////////////////////////////////////////////////////
// state 8
int API_io_putc_8(char c, int x, int y, int kleur, int achtergrond)
{
	int i,j,k;//, error;
	int start, stop;

	c = c-' ';
	start = C_consolas_8ptDescriptors[(int)c][1];
	stop  = (c == TEKENS-1)? sizeof(C_consolas_8ptBitmaps):C_consolas_8ptDescriptors[(int)c+1][1];

	for(i=0; start<stop; start+=C_consolas_8ptDescriptors[(int)c][0], i++)
	{
		for(k=0; k<C_consolas_8ptDescriptors[(int)c][0]; k++)
		{
			for(j=0; j<BIT; j++)
			{
				int test = 0x80>>j & C_consolas_8ptBitmaps[start+k];
				if(test)
					UB_VGA_SetPixel((BIT*k)+j+x, y, kleur);
				//else if(achtergrond != -1)
					//UB_VGA_SetPixel((BIT*k)+j+x, y, achtergrond);
			}
		}
		y++;
	}
	return 0;
}


int API_io_puts_8(char* zin, int x_lup, int y_lup, int kleur, int reserved)
{
	int i, error=0;
	int x = x_lup;
	int y = y_lup;
	error = API_io_putc_8(*(zin), x, y, kleur, reserved);

	for(i=1; i<strlen(zin); i++)
	{
		error = API_io_ERROR_inrange(x, y, x+(8*C_consolas_8ptDescriptors[zin[i-1]-' '][0]), y+20);
		if 		(error == FOUTX){ y+=20;x=x_lup-(8*C_consolas_8ptDescriptors[zin[i-1]-' '][0]);}
		else if	(error == FOUTY) return error;

		error |=API_io_putc_8(*(zin+i), x+=(8*C_consolas_8ptDescriptors[zin[i-1]-' '][0]), y, kleur, reserved);
	}

	return error;
}


//////////////////////////////////////////////////////////////////////////////////////////////
// state 9
int API_io_putc_9(char c, int x, int y, int kleur, int achtergrond)
{
	int i,j,k;//, error;
	int start, stop;

	c = c-' ';
	start = S_consolas_16ptDescriptors[(int)c][1];
	stop  = (c == TEKENS-1)? sizeof(S_consolas_16ptBitmaps):S_consolas_16ptDescriptors[(int)c+1][1];

	for(i=0; start<stop; start+=S_consolas_16ptDescriptors[(int)c][0], i++)
	{
		for(k=0; k<S_consolas_16ptDescriptors[(int)c][0]; k++)
		{
			for(j=0; j<BIT; j++)
			{
				int test = 0x80>>j & S_consolas_16ptBitmaps[start+k];
				if(test)
					UB_VGA_SetPixel((BIT*k)+j+x, y, kleur);
				//else if(achtergrond != -1)
					//UB_VGA_SetPixel((BIT*k)+j+x, y, achtergrond);
			}
		}
		y++;
	}
	return 0;
}


int API_io_puts_9(char* zin, int x_lup, int y_lup, int kleur, int reserved)
{
	int i, error=0;
	int x = x_lup;
	int y = y_lup;
	error = API_io_putc_9(*(zin), x, y, kleur, reserved);

	for(i=1; i<strlen(zin); i++)
	{
		error = API_io_ERROR_inrange(x, y, x+(8*S_consolas_16ptDescriptors[zin[i-1]-' '][0]), y+20);
		if 		(error == FOUTX){ y+=20;x=x_lup-(8*S_consolas_16ptDescriptors[zin[i-1]-' '][0]);}
		else if	(error == FOUTY) return error;

		error |=API_io_putc_9(*(zin+i), x+=(8*S_consolas_16ptDescriptors[zin[i-1]-' '][0]), y, kleur, reserved);
	}

	return error;
}


//////////////////////////////////////////////////////////////////////////////////////////////
// state 10
int API_io_putc_10(char c, int x, int y, int kleur, int achtergrond)
{
	int i,j,k;//, error;
	int start, stop;

	c = c-' ';
	start = B_consolas_16ptDescriptors[(int)c][1];
	stop  = (c == TEKENS-1)? sizeof(B_consolas_16ptBitmaps):B_consolas_16ptDescriptors[(int)c+1][1];

	for(i=0; start<stop; start+=B_consolas_16ptDescriptors[(int)c][0], i++)
	{
		for(k=0; k<B_consolas_16ptDescriptors[(int)c][0]; k++)
		{
			for(j=0; j<BIT; j++)
			{
				int test = 0x80>>j & B_consolas_16ptBitmaps[start+k];
				if(test)
					UB_VGA_SetPixel((BIT*k)+j+x, y, kleur);
				//else if(achtergrond != -1)
					//UB_VGA_SetPixel((BIT*k)+j+x, y, achtergrond);
			}
		}
		y++;
	}
	return 0;
}


int API_io_puts_10(char* zin, int x_lup, int y_lup, int kleur, int reserved)
{
	int i, error=0;
	int x = x_lup;
	int y = y_lup;
	error = API_io_putc_10(*(zin), x, y, kleur, reserved);

	for(i=1; i<strlen(zin); i++)
	{
		error = API_io_ERROR_inrange(x, y, x+(8*B_consolas_16ptDescriptors[zin[i-1]-' '][0]), y+20);
		if 		(error == FOUTX){ y+=20;x=x_lup-(8*B_consolas_16ptDescriptors[zin[i-1]-' '][0]);}
		else if	(error == FOUTY) return error;

		error |=API_io_putc_10(*(zin+i), x+=(8*B_consolas_16ptDescriptors[zin[i-1]-' '][0]), y, kleur, reserved);
	}

	return error;
}


//////////////////////////////////////////////////////////////////////////////////////////////
// state 11
int API_io_putc_11(char c, int x, int y, int kleur, int achtergrond)
{
	int i,j,k;//, error;
	int start, stop;

	c = c-' ';
	start = C_consolas_16ptDescriptors[(int)c][1];
	stop  = (c == TEKENS-1)? sizeof(C_consolas_16ptBitmaps):C_consolas_16ptDescriptors[(int)c+1][1];

	for(i=0; start<stop; start+=C_consolas_16ptDescriptors[(int)c][0], i++)
	{
		for(k=0; k<C_consolas_16ptDescriptors[(int)c][0]; k++)
		{
			for(j=0; j<BIT; j++)
			{
				int test = 0x80>>j & C_consolas_16ptBitmaps[start+k];
				if(test)
					UB_VGA_SetPixel((BIT*k)+j+x, y, kleur);
				//else if(achtergrond != -1)
					//UB_VGA_SetPixel((BIT*k)+j+x, y, achtergrond);
			}
		}
		y++;
	}
	return 0;
}


int API_io_puts_11(char* zin, int x_lup, int y_lup, int kleur, int reserved)
{
	int i, error=0;
	int x = x_lup;
	int y = y_lup;
	error = API_io_putc_11(*(zin), x, y, kleur, reserved);

	for(i=1; i<strlen(zin); i++)
	{
		error = API_io_ERROR_inrange(x, y, x+(8*C_consolas_16ptDescriptors[zin[i-1]-' '][0]), y+20);
		if 		(error == FOUTX){ y+=20;x=x_lup-(8*C_consolas_16ptDescriptors[zin[i-1]-' '][0]);}
		else if	(error == FOUTY) return error;

		error |=API_io_putc_11(*(zin+i), x+=(8*C_consolas_16ptDescriptors[zin[i-1]-' '][0]), y, kleur, reserved);
	}

	return error;
}
