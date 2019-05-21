#include "stm32_ub_vga_screen.h"


int API_draw_line(int x_1, int y_1, int x_2, int y_2, int color, int weight, int reserved)
{
  int i;
  int x, y;
  float dx, dy, a;

  dx = x_2 - x_1;
  dy = y_2 - y_1;
  a  = dy/dx;
for(i=weight/2; weight>0; i--, weight--)
{

	if (fabs(a)<=1)
    if (x_1 < x_2)
      for (x=x_1; x<x_2; x++)
      {
        y = (int)(a*(x-x_1)+y_1+i); // y = ax + b
        UB_VGA_SetPixel(x,y,color);
      }
    else
      for (x=x_2; x<x_1; x++)
      {
        y = (int)(a*(x-x_1)+y_1+i); // y = ax + b
        UB_VGA_SetPixel(x,y,color);
      }

  else
    if (y_1 < y_2)
      for (y=y_1; y<y_2; y++)
      {
        x = (int)((1/a)*(y-y_1)+x_1+i); // x = (y - b)/a
        UB_VGA_SetPixel(x,y,color);
      } else
      for (y=y_2; y<y_1; y++)
      {
        x = (int)((1/a)*(y-y_1)+x_1+i); // y = ax + b
        UB_VGA_SetPixel(x,y,color);
      }
}

  return 0;
}
