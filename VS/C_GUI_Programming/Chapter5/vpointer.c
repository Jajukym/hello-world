#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void itoa();
void reverse();


/* itoa:  convert n to characters in s */
void itoa(int n, char s[])
 {
     int i, sign;
 
     if ((sign = n) < 0)  /* record sign */
         n = -n;          /* make n positive */
     i = 0;
     do {       /* generate digits in reverse order */
         s[i++] = n % 10 + '0';   /* get next digit */
     } while ((n /= 10) > 0);     /* delete it */
     if (sign < 0)
         s[i++] = '-';
     s[i] = '\0';
     reverse(s);
 }
 
 /* reverse:  reverse string s in place */
 void reverse(char s[])
 {
     int i, j;
     char c;
 
     for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
         c = s[i];
         s[i] = s[j];
         s[j] = c;
     }
 }
 
 
 
 
void main (void)
{
	 char s[5]; //itoa buffer
	 int intval = 255958283;
	 void *vptr = &intval;
	 
	 printf ("The value at vptr as an int is %d\n", *((int *) vptr));
	 printf ("The value at vptr as a char is %d\n", *((char *) vptr));
	 itoa(intval, s); //itoa conversion
	 printf ("The value at vtpr as a str is %s\n", s);
}
