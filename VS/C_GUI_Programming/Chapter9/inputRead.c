#include <stdio.h>


void main (void)
{
	char input[256];
	int age;
	printf ("What is your name, user?\n");
	scanf ("%s", input); /*waits for input and creates string*/
	printf ("Hello, %s. How old are you?\n", input);
	scanf ("%d", &age); /*waits for input and creates decimal*/
	printf ("Well, %s, you look young for %d...\n", input, age);
}
