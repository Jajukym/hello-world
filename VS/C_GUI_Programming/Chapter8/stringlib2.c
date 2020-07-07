#include <stdio.h>
#include <string.h>


void main (void) /*The easy way to compare full strings*/
{
	char str1[10] = "first";
	char str2[10] = "first";


	if (strcmp (str1, str2) == 0) /*string compare "cheating"*/
	{
		printf ("The two strings are identical.\n");
	}
	else
	{
		printf ("The two strings are different.\n");
	}
}
