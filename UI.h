/**
  ******************************************************************************
  * @file    UI.h
  * @author  SOFT_ONT groep 7
  * @version V1.0.2
  * @date    29-5-2019
  * @brief   Dit bestand biedt string functies om de volgende GUI
  *          functionaliteiten te regelen (UI): 
  *           - Error handling
  *           - Parameter teller
  *           - String opmaken
  */ 


#ifndef __UI_H
#define __UI_H


/** @addtogroup UI
  * @{
  */

/** @addtogroup StringUI
  * @{
  */

/** @addtogroup Ascii_waardes
  * @{
  */
#define UI_STR_EMPTY 0 		/*!< Waarde van een lege string */
#define UI_STR_CR	 0x0D	/*!< Carrier return */
#define UI_STR_T 	 '\0'	/*!< String terminator*/
#define UI_STR_KOMMA ','	/*!< Komma */
#define UI_STR_SPAT  ' '	/*!< Spatie */

/**
  * @}
  */

/**
  * @}
  */


/**
  * @}
  */

/* Error handling */
extern void UI_ERR_put	(int error);

/* Parameter teller */
extern int  UI_PARAMCNT (char* buffer, char sep);

/* String opmaak */
extern void UI_CH_rm	(char* buffer, char c, char rm);
extern void UI_CH_rp	(char* buffer, char old_char, char new_char);

#endif
