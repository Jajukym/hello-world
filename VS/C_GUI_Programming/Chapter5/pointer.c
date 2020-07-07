#include <stdio.h>
void main (void)
{
	 /*all three lines are needed to create a pointer or bad stuff will happen*/
	 int a; //the variable
	 int *ptr_to_a; //the pointer to variable
	 ptr_to_a = &a; //the pointer to variable address
	 
	 
	 a = 5;
	 printf ("The value of a is %d\n", a);
	 
	 *ptr_to_a = 6;
	 printf ("The value of a is %d\n", a);
	 
	 printf ("The value of ptr_to_a is %d\n", ptr_to_a);
	 printf ("It stores the value %d\n", *ptr_to_a);
	 printf ("The address of a is %d\n", &a);
}
