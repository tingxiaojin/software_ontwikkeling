//--------------------------------------------------------------
// File     : APIdraw.h
//--------------------------------------------------------------

//--------------------------------------------------------------
#ifndef __API_draw

//--------------------------------------------------------------
// Includes
//--------------------------------------------------------------
#include "stm32f4xx.h"

//-------------------------------------------------------------
//functions arguments
//-------------------------------------------------------------
int API_draw_text(int x_lup, int y_lup, int color, char* text, char *fontname, int fontsize, int fontstyle, int reserved);
int API_draw_line(int x_1, int y_1, int x_2, int y_2, int color, int weight, int reserved);
int API_draw_rectangle(int x, int y, int width, int height, int color, int filled, int reserved1, int reserved2);
int API_draw_bitmap(int x_lup, int y_lup, int bm_nr);
int API_clearscreen(int color);
//--------------------------------------------------------------
#endif // __API_draw
