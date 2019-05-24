



#ifndef API_DRAW_H
#define API_DRAW_H

enum
{
	FOUTX =1,
	FOUTY,
	FOUTOMVANG,
	INPUTERROR,
	STR_LEEG,
};

extern int API_DRAW_bitmap	(int nr, int x, int y, int background);
extern int API_DRAW_line	(int startx, int starty, int eindx, int eindy, char kleur, int dikte);
extern int API_ERROR_inrange(int startx, int starty, int eindx, int eindy);
extern int API_DRAW_rechthoek(int startx, int starty, int breedte, int hoogte, int kleur, int gevuld);
extern int API_DRAW_text(char* zin, int x_lup, int y_lup, int kleur, int achtergrond);


#endif
