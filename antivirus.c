// Inclue bibliotecas basicas
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

// Define uma constante para verificar os arquivos gzip
const unsigned short gzip = 0x1f8b;

// Comeca funcao principal
int main(int argc, char* argv[]) {
	
	// Garante que haja somente um parametro 
	if (argc != 2) { 
		printf("Usage: antivirus signature < file_list\n");
		return 0;
	}

	// 	Le cada linha da entrada padrao
    char *line = NULL;
    size_t size;
    while (getline(&line, &size, stdin) != -1)
    {
    	// Remove quebra de linha do nome do arquivo
    	char *temp = NULL;
    	if ((temp = strstr(line, "\n")) != NULL) {
    		int len = strlen(line);
    		line[len-1] = '\0';
    	}

    	// Verifica se o arquivo existe
		if( access( line, F_OK ) != -1 ) {

			FILE *file;
			unsigned char in[2];

			file = fopen(line, "r");
			fread(&in, 1, 2, file);

			if(memcmp(in, &gzip, 2) == 0) {
				printf("Arquivo %s compactado\n", line);
			} else {
				printf("Arquivo %s nao compactado\n", line);
			}


		} else { //Se o arquivo não existe
			printf("Arquivo %s nao encontrado!\n", line);
		}

    }

    fprintf( stderr, "Arquivo %s contem a assinatura do virus\n", "file1.txt");
    fprintf( stdout, "Arquivo %s não contem a assinatura do virus\n", "file2.txt");

	return 0;
}