#include <stdio.h>
int main (void)
{
	FILE *fp;
	int value;
	fp = fopen ("/home/pi/Documents/C/magpi/output.txt", "wb");  /*wb is write binary*/
	if (fp)
	{
		for (value = 65; value < 91; value++) /*decimal value of hex table 70 = E*/
		{
			fputc (value, fp); /*Writes to the file*/
		}
		fclose (fp);
	}
}
