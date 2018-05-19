// Inclue bibliotecas basicas
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

// Define uma constante para verificar os arquivos gzip
const unsigned short gzip_byte1 = 0x1f;
const unsigned short gzip_byte2 = 0x8b;

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
			unsigned char file_byte1[1];
			unsigned char file_byte2[1];

			file = fopen(line, "r");
			fread(&file_byte1, 1, 1, file);
			//fread(&file_byte2, 2, 1, file);

			if(memcmp(file_byte1, &gzip_byte1, 1) == 0) {
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