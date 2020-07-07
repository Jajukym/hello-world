#include <stdio.h>

int result; /*global variable is accessable from any function*/


void add (int a, int b)
{
	result = a + b; /*write here*/
}


void main (void)
{
	add (3, 4);
	printf ("The result is %d\n", result);  /*read here*/
}
