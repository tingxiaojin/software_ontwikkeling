



#ifndef API_DRAW_H
#define API_DRAW_H

enum
{
	FOUTX =1,
	FOUTY,
	FOUTOMVANG,
	INPUTERROR,
<<<<<<< HEAD
	STR_LEEG,
};

extern int API_DRAW_bitmap	(int nr, int x, int y, int background);
extern int API_DRAW_line	(int startx, int starty, int eindx, int eindy, char kleur, int dikte);
extern int API_ERROR_inrange(int startx, int starty, int eindx, int eindy);
extern int API_DRAW_rechthoek(int startx, int starty, int breedte, int hoogte, int kleur, int gevuld);
extern int API_DRAW_text(char* zin, int x_lup, int y_lup, int kleur, int achtergrond);
=======
	STR_LEEG
};

extern int API_draw_line		(int x_1, int y_1, int x_2, int y_2, int color, int weight, int reserved);
extern int API_draw_rectangle	(int x, int y, int width, int height, int color, int filled, int weight, int bordercolor);
extern int API_draw_clearscreen (int color);
extern int API_draw_text		(int x_lup, int y_lup, int color, char* tekst, char* fontname, int fontsize, int fonstsytle, int reserved);
extern int API_draw_bitmap		(int x_lup, int y_lup, int bm_nr, int reserved);

//extern int API_DRAW_rechthoek(int startx, int starty, int breedte, int hoogte, int kleur, int gevuld);

>>>>>>> 9ae6e993bd5e9bdc24d95542520f61ca8aeb76e2


#endif
