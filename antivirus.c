// Inclue bibliotecas basicas

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

// Comeca funcao principal
int main(int argc, char* argv[]) {
	
	// Garante que haja somente um parametro 
	if (argc != 2) { 
		printf("Usage: antivirus signature < file_list\n");
		return 0;
	}

    char *line = NULL;
    size_t size;
	// 	Le cada linha da entrada padrao
    while (getline(&line, &size, stdin) != -1)
    {
        printf("%s\n", line);
    }

	return 0;
}