//#include "stm32f4xx.h"
//#include "stm32_ub_vga_screen.h"
//#include <math.h>
//#include <stdio.h>
//#include <stdio.h>
//#include "includes.h"

//#include "pijl_links.h"
//#include "pijl_rechts.h"
//#include "pijl_omhoog.h"
//#include "pijl_omlaag.h"
//#include "smiley_blij.h"
//#include "smiley_boos.h"

#define FOUTX 		0x01
#define FOUTY 		0x02
#define FOUTOMVANG 	0x04
#define INPUTERROR  0x08

extern int API_DRAW_bitmap	(int nr, int x, int y, int background);
extern int API_DRAW_line	(int startx, int starty, int eindx, int eindy, char kleur, int dikte);
