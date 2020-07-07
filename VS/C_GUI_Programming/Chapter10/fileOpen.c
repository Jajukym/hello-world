#include <stdio.h>


void main (void)
{
	FILE *fp;   /*file pointer*/
	int value;   /*variable for storing read string from file*/
	fp = fopen ("/home/pi/Documents/C/magpi/input.txt", "rb");  /*rb is read binary*/
	if (fp)
	{
		while (1)
		{
			value = fgetc (fp);  /*file get characters*/
			if (value == EOF) break;  /*EOF is end of file and will break if not strings to read*/
			else printf ("%c", value);  /*prints file string to terminal*/
		}
		fclose (fp);
	}
}
