



#ifndef API_DRAW_H
#define API_DRAW_H

enum
{
	FOUTX =1,
	FOUTY,
	FOUTOMVANG,
	INPUTERROR,
	STR_LEEG,
	TOOMUCHPARAM,
	TOOLITTLEPARAM
};

extern int API_draw_line		(int x_1, int y_1, int x_2, int y_2, int color, int weight, int reserved);
extern int API_draw_rectangle	(int x, int y, int width, int height, int color, int filled, int weight, int bordercolor);
extern int API_draw_clearscreen (int color);
extern int API_draw_text		(int x_lup, int y_lup, int color, char* tekst, char* fontname, int fontsize, int fonstsytle, int reserved);
extern int API_draw_bitmap		(int x_lup, int y_lup, int bm_nr, int reserved);

//extern int API_DRAW_rechthoek(int startx, int starty, int breedte, int hoogte, int kleur, int gevuld);



#endif
