#include <stdio.h>
#include <stdlib.h>

int main()
{

	FILE *fptr;

    fptr = fopen("/dev/char_dev_file", "r");
	
	char ch;
	ch = fgetc(fptr);
	
	while (ch != EOF && ch != 0)
	{
		printf ("%c", ch);
		ch = fgetc(fptr);
	}
    fclose(fptr);
    printf("\n");
}
