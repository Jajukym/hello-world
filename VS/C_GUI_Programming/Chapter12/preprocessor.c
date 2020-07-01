#include <stdio.h>



void main (void)
{
#if 0
	printf ("Some code\n");
#else
	printf ("Some other code\n");
#endif
}


/*With a 0 after the #if, the code between the #if and the #else 
 * doesn’t get called, but the code between the #else and the #endif 
 * does. If you change the value after the #if to a 1, the code between 
 * the #if and the #else does get called, but the code between the #else 
 * and the #endif doesn’t. This is a really useful trick to temporarily 
 * remove or replace a piece of code when you’re debugging.*/

/*The most common use of #if is for temporarily removing code – just 
 * wrap it between an #if 0 and an #endif. The #else is optional, but 
 * sometimes you want to substitute the code you’ve removed with 
 * different code*/
