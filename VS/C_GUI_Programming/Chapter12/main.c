#include <stdio.h>
#include "function.h"


void main (void)
{
	printf ("The total is %d\n", add_vals (1, 2, 3));
	
	float rad = 3;
	float circ = rad * 2 * PI;
	float area = rad * rad * PI;
	printf ("The circumference of a circle radius %f is %f\n",
			rad, circ);
	printf ("The area of a circle radius %f is %f\n", rad, area);
	
	printf ("The sum of %d and %d is %d\n", 5, 2, ADD(5,2));
	printf ("The sum of %d and %d is %d\n", 3, 7, ADD(3,7));
	
	printf (MY_TEXT);
}


/*The <> signs tell the compiler to look for the file in the directory 
 * where the system’s include files are stored; the "" signs indicate 
 * that the file is local and is in the same directory as the .c files 
 * you’re building.*/
