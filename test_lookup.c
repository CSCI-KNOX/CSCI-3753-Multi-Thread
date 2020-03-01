#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include "util.h"

int main(int argc, char *argv[])
{
	for (int i=1 ; i < argc ; i++)
	{
		FILE *f = fopen(argv[i], "r");
		
		char ip[2*1024];
		
		char *line = NULL;
		size_t line_max = 0;
		int len = getline(&line, &line_max, f);
		while (len > 0)
		{
			len--;
			line[len] = 0;
			
		//	printf("Lookup:[%d][%s]...", len, line);
			ip[0] = 0;
			int err = dnslookup(line, ip, sizeof(ip));
		//	printf("[%d][%s]\n", err, ip);

			printf("%s, %s\n", line, ip);
			len = getline(&line, &line_max, f);
		}
		
		fclose(f);
		free(line);
	}
	
	return 0;
}