#include <stdio.h>

void main(void)
{
	double a; //double has 15 digits of precision vs float has 7 digits of precision
	double b = 3.641;
	double c;
	
	a = 2.897;
	c = a + b;
	printf("The sum of %f and %f is %f\n", a, b, c);
}
