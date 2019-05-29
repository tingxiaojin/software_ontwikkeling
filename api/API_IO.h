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
#define  VGA_COL_BLACK          0  //0x00
#define  VGA_COL_BLUE           3  //0x01
#define  VGA_COL_LIGHTBLUE      0xBB //0x0B
#define  VGA_COL_DEEPSKYBLUE    0x17 //0x0B
#define  VGA_COL_GREEN			0x10
#define  VGA_COL_LIGHTGREEN     0x1C//0x3C
#define  VGA_COL_CYAN           0x1F //0x1F
#define  VGA_COL_LIGHTCYAN      0xEF//0x7F
#define  VGA_COL_RED            0xE0 //0x60
#define  VGA_COL_LIGHTRED       0xED//0xE0
#define  VGA_COL_MAGENTA        0xE3//0x83
#define  VGA_COL_LIGHTMAGENTA   0xF3//0xE3
#define  VGA_COL_BROWN			0xA4//133//137//105//69 //0x45
#define  VGA_COL_YELLOW         0xFC//0xFC
#define  VGA_COL_PINK         	0xEE//0xFC
#define  VGA_COL_PURPLE        	0x82//0xFC
#define  VGA_COL_GREY			0x92//108//112
#define  VGA_COL_WHITE          0xFF



//--------------------------------------------------------------
// Extern declared functions
//--------------------------------------------------------------
extern void  API_io_init		  	(void);
extern void  API_io_UART_INT_init	(void);

extern int   API_io_ERROR_inrange	(int startx, int starty, int eindx, int eindy);

extern void  API_io_DELAY_us		(unsigned int x);
extern void  API_io_DELAY_ms		(unsigned int x);
extern void  API_io_DELAY_s 		(unsigned int x);

extern void  API_io_UART_INT_gets	(char* buffer);
extern void  API_io_UART_gets  		(char* buffer);
extern char  API_io_UART_get   		(void);

extern void  API_io_UART_puts  		(char* buffer);
extern void  API_io_UART_putchar	(char  c);
extern void  API_io_UART_putint		(int   num);
extern void  API_io_UART_putnum		(unsigned int num, unsigned char deel);

extern void  API_io_rp_c			(char* buffer, char old_char, char new_char);
extern void  API_io_rm_c_ut			(char* buffer, char c		, char stopc);
extern int 	 API_io_putc 			(int c,    int x, 	   int y,	  int kleur, int achtergrond);
extern int 	 API_io_puts 			(char* zin, int x_lup, int y_lup, int kleur, char* font, int fontgrootte, int fonststyle, int reserved);

extern void  API_io_bitmap	  		(int x, 	 int y, 	 unsigned char* bitmap, int background);
extern void  API_io_clearscherm		(int kleur);

extern int   API_io_line		  	(int startx, int starty, int eindx, 	 		int eindy, 		char kleur, int dikte);
extern int   API_io_rechthoek  		(int x, 	 int y, 	 int breedte, 			int hoogte, 	int kleur,  int gevuld);

//--------------------------------------------------------------
// Extern declared variables
//--------------------------------------------------------------

//--------------------------------------------------------------
#endif // __STM32F4_UB_MAIN_H
