#include <stdio.h>


int main (void)
{
	FILE *fp;
	int value;
	fp = fopen ("/home/pi/Documents/C/magpi/input.txt", "rb");
	if (fp)
	{
		fseek (fp, 20, SEEK_SET);
		//fseek (fp, -10, SEEK_END);
		fseek (fp, 0, SEEK_CUR);
		while (1)
		{
			value = fgetc (fp);
			if (value == EOF) break;
			else printf ("%c", value); /*Use collected value and manipulate as an array*/
		}
	fclose (fp);
	}
}
