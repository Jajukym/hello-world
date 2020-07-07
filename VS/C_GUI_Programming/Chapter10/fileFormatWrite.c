#include <stdio.h>
int main (void)
{
	FILE *fp;
	int value;
	fp = fopen ("/home/pi/Documents/C/magpi/output.txt", "wb");  /*wb is write binary*/
	if (fp)
	{
		fprintf(fp, "This is some text. \n"); /*full string printing*/
		fprintf(fp, "This is some text."); /*full string printing*/
		fprintf(fp, "This is some text. \n"); /*full string printing*/
		fclose (fp);
	}
}
