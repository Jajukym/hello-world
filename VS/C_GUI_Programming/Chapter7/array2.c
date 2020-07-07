#include <stdio.h>


void main (void)
{
	int val = 69;
	char string[50];
	
	sprintf (string, "The value of val is %d\n", val);
	printf ("%s", string);
}
