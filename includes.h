/*
*********************************************************************************************************
*                                              EXAMPLE CODE
*
*                             (c) Copyright 2013; Micrium, Inc.; Weston, FL
*
*                   All rights reserved.  Protected by international copyright laws.
*                   Knowledge of the source code may not be used to write a similar
*                   product.  This file may only be used in accordance with a license
*                   and should not be redistributed in any way.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*                                           MASTER INCLUDES
*
*                                     ST Microelectronics STM32
*                                              with the
*
*                                           STM3240G-EVAL
*                                         Evaluation Board
*
* Filename      : includes.h
* Version       : V1.00
* Programmer(s) : van der Bent
* 				: COOcox
*
*  07-07-2014 toevoeging van false en true defines
*********************************************************************************************************
*/

#ifndef  INCLUDES_PRESENT
#define  INCLUDES_PRESENT
//#define OS_MASTER_FILE
/*
*********************************************************************************************************
*                                         STANDARD LIBRARIES
*********************************************************************************************************
*/

#include  <stdarg.h>
#include  <stdio.h>
#include  <stdlib.h>
#include  <math.h>
#include  <ctype.h>

#include <string.h>
#include <stdint.h>

/*
*********************************************************************************************************
*                                              LIBRARIES
*********************************************************************************************************
*/

//#include  "os_cpu.h"
//#include  "os_cfg.h"

/*
*********************************************************************************************************
*                                                 OS
*********************************************************************************************************
*/

//#include  "ucos_ii.h"

#include "misc.h"
#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"
#include "stm32f4xx_exti.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_syscfg.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_usart.h"
#include "stm32_ub_vga_screen.h"


/*
*********************************************************************************************************
*                                            INCLUDES END
*********************************************************************************************************
*/

#include "uart.h"
//#include "lcd.h"
#include "delay.h"
//#include "Arial.h"

#define TRUE		1
#define FALSE		0

//--------------------------------------------------------------
// Defines
//--------------------------------------------------------------
//#define TRUE  1
//#define FALSE 0

#define RECHTHOEK_GEVULD 1
#define RECHTHOEK_LEEG   0
//
#define API_IO_PIJL_LINKS  0
#define API_IO_PIJL_RECHTS 1
#define API_IO_PIJL_OMHOOG 2
#define API_IO_PIJL_OMLAAG 3
#define API_IO_SMILY_BLIJ  4
#define API_IO_SMILY_BOOS  5

//extern unsigned char* pijl_links;

#endif

