#include <stdio.h>


void main (void) /*read a value from a string*/
{
	int val;
	char string[25] = "1295";
	
	sscanf (string, "%d", &val); /*scan tool*/
	
	printf ("The value in the string is %d\n", val);
}
