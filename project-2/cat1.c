#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int main(int argc, char *argv[])
{
	FILE* fp;
	if (argc == 1)
	{
		while(!ferror(stdin) && !feof(stdin))
		{
			int c = fgetc(stdin);
			if (c != EOF)
			{
				fputc(c, stdout);
			}
		}
	}
	else if (argc == 2)
        {
		fp = fopen(argv[1], "r");
		if (fp)
		{
			char j;
			while (( j = fgetc(fp)) != EOF)
			{
				printf ("%c", j);
			}
			fclose (fp);	
		}
		else
			printf ("Error: File not found\n");
         }
	else if (argc == 3)
	{
		if (strcmp(argv[2], "-n") == 0)
		{
			fp = fopen(argv[1], "r");
                	if (fp)
               	 	{
                        	char j;
				int k = 1;
				bool print_line = true;
                        	while (( j = fgetc(fp)) != EOF)
                        	{
					if (print_line)
					{
						printf ("%i  ", k); 
						k++;
						print_line = false;
					}
                                	printf ("%c", j);
					if (j == '\n')
					{
						print_line = true;
					}
                        	}
				fclose(fp);
                	}
                	else
                        	printf ("Error: File not found\n");

		}
		else
			printf ("Error: unknown file option\n");
	}

}
