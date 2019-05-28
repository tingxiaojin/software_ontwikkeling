
// Voorkom meerdere inclusions
#ifndef __LL_H
#define __LL_H

//extern int LL_exe(FUNCTIE* input);
extern int 	 LL_kstoki		(char* kleur);
extern int   LL_STRING_check(char*input, char* figuur);
extern void  LL_FIG_init	(char* buffer, FUNCTIE* input, int vorm);
extern char* LL_STRING_param(char* buffer, int paramnum);

#endif
