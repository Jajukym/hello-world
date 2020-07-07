#include <stdio.h>

void main (void) /*The hard way to scan and compare elements in an array*/
{
	char str1[10] = "first";
	char str2[10] = "fire";
	
	char *ptr1 = str1, *ptr2 = str2; /*creates pointer*/
	
	while (*ptr1 != 0 && *ptr2 != 0) /*loop through string arrays*/
	{
		//if (*ptr1 != *ptr2) /*pointer value compare not satified*/
		/*{*/
			//printf("All Done!!!\n");
			//break; /*jumps out of loop*/
		/*}*/
				
		if (*ptr1 == *ptr2) /*pointer value compare satified*/
		{
			printf("%c and %c\n", *ptr1, *ptr2); /*prints the character pointer value*/
			printf("%d and %d\n", *ptr1, *ptr2); /*prints the decimal pointer value*/
			printf("0x%02x and 0x%02x\n", *ptr1, *ptr2); /*prints the decimal pointer value*/
			printf ("The two strings are identical.\n");
		}
		else
		{
			printf("%c and %c\n", *ptr1, *ptr2); /*prints the character pointer value*/
			printf("%d and %d\n", *ptr1, *ptr2); /*prints the decimal pointer value*/
			printf("0x%02x and 0x%02x\n", *ptr1, *ptr2); /*prints the hex pointer value*/
			printf ("The two strings are different.\n");
			break; /*jumps out of loop*/
		}
		*ptr1++; /*advance pointer through string array*/
		*ptr2++; /*advance pointer through string array*/
	}
}
