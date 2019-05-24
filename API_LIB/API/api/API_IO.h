//--------------------------------------------------------------
// File     : main.h
//--------------------------------------------------------------

//--------------------------------------------------------------
#ifndef __API_IO_H
#define __API_IO_H


//--------------------------------------------------------------
// Includes
//--------------------------------------------------------------

//--------------------------------------------------------------
// Defines
//--------------------------------------------------------------


//--------------------------------------------------------------
// Extern declared functions
//--------------------------------------------------------------
extern void API_IO_init		  (void);
extern int  API_IO_line		  (int startx, int starty, int eindx, int eindy, char kleur, int dikte);
extern void API_IO_bitmap	  (int x, int y, unsigned char* bitmap, int background);
extern int  API_IO_rechthoek  (int x, int y, int breedte, int hoogte, int kleur, int gevuld);
extern void API_IO_clearscherm(int kleur);
extern void API_IO_UART_puts  (char* buffer);
extern void API_IO_UART_putint(int num);
extern void API_IO_UART_putnum(unsigned int num, unsigned char deel);
extern void API_IO_UART_putchar(char c);
extern void API_IO_UART_gets  (char* buffer);
extern char API_IO_UART_get   (char c);
extern int  API_IO_putc		  (int c, int x_lup, int y_lup, int kleur, int achtergrond);

//--------------------------------------------------------------
#endif // __STM32F4_UB_MAIN_H
