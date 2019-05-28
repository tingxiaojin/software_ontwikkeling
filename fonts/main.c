#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "main.h"


int main (void)
{
	int i, j, k, l;
	char characters[] = "!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";
	
	printf("sizeof arial_8ptDescriptors= %d\n", sizeof(arial_8ptDescriptors)/8);
	printf("value [0][0] = %d\n", arial_8ptDescriptors[0][0]);
	printf("value [0][1] = %d\n", arial_8ptDescriptors[0][1]);

	for(j=0/*59*/; j<(sizeof(arial_8ptDescriptors)/8); j++)
	{
		printf("\t\t %c\n", characters[j]);
		for (i=arial_8ptDescriptors[j][1]; i<arial_8ptDescriptors[j+1][1]; i+=k)
		{
			for(k=0; k<arial_8ptDescriptors[j][0]; k++) // print enkel de rij
				for(l=0; l<8; l++)
					if((0x80>>l) & (arial_8ptBitmaps[i+k]))
						printf("%c ",'@');
					else
						printf("%c ",'.');	
			printf("\t%d\n", k);
		}
		printf("\n\n")	;
	}
	
	return 0;
}
