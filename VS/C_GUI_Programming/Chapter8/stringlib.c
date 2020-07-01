#include <stdio.h>
#include <string.h>


void main (void)
{
	char str1[10] = "first"; /*str1 holds 10 characters is 10 locations in memory*/
	char str2[10] = "second";
	char str3[20] = "and";
	
	
	printf("%s\n", str3); /*This is what is stored in the character array*/
	printf("%c\n", str3[1]); /*This is what is stored in the array location 1*/
	
	
	strcpy (str3, str1); /*This overwrites the first argument with the second argument*/
	strcat (str3, str2); /*concatenates the two string arguments together*/
	
	printf ("%s + %s = %s\n", str1, str2, str3);
}
