#include <stdio.h>

#define SPACE 256

int main()
{
	char buff[SPACE];
	scanf("%[^\n]s",buff);
	int x = buff[0];
	if(x != 1)
	{			
		FILE *f;
		f = fopen ("/dev/char_dev_file", "w");
		fprintf (f, "%s", buff);
		fclose (f);
	}
	return 0;
}
