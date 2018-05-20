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
	
	// Variavel para guardar assinatura do virus
	char *signature = NULL;

	// Garante que haja somente um parametro 
	if (argc != 2) { 
		printf("Usage: antivirus signature < file_list\n");
		return 0;
	} else {
		signature = argv[1];
	}

	// 	Le cada linha da entrada padrao
    char *arquivo = NULL;
    size_t size;
    while (getline(&arquivo, &size, stdin) != -1)
    {
    	// Variavel para guardar se arquivo tem assinatura do virus
    	int found = 0;

    	// Remove quebra de linha do nome do arquivo
    	// Nao tinha a funcao memmem no meu gcc
    	char *temp = NULL;
    	if ((temp = strstr(arquivo, "\n")) != NULL) {
    		int len = strlen(arquivo);
    		arquivo[len-1] = '\0';
    	}

    	// Verifica se o arquivo existe
		if( access( arquivo, F_OK ) != -1 ) {

			FILE *file;
			unsigned char file_byte1[1];
			unsigned char file_byte2[1];

			file = fopen(arquivo, "r");
			fread(&file_byte1, 1, 1, file);
			// TODO: Ainda nao esta funcionando a comparacao de 2 bytes 
			//fread(&file_byte2, 2, 1, file);

			// Verifica se o arquivo esta compactado
			if(memcmp(file_byte1, &gzip_byte1, 1) == 0) {
				// printf("Arquivo %s compactado\n", arquivo);

				char buffer[2048];
				char command[124] = "gzip -dc ";

				// Concatena commando com nome do arquivo
				strcat(command, arquivo);
				FILE *fp = popen(command,"r");

				// Le arquivo compactado
				while (fgets(buffer,2048,fp)) 
				{
					// Procura assinatura do virus
			    	if ((temp = strstr(buffer, signature)) != NULL) {
			    		found = 1;
			    	}
				}

			} else {
				// printf("Arquivo %s nao compactado\n", arquivo);

				// 	Le cada linha do arquivos
			    char *linha = NULL;
			    size_t tamanho;
			    while (getline(&linha, &tamanho, file) != -1)
			    {
			    	// Procura assinatura do virus
			    	if ((temp = strstr(linha, signature)) != NULL) {
			    		found = 1;
			    	}
			    }

			}

			// Imprime mensagem de acordo com resultado do arquivos
			if (found == 1) {
				fprintf( stderr, "Arquivo %s contem a assinatura do virus\n", arquivo);
			} else {
				fprintf( stdout, "Arquivo %s nao contem a assinatura do virus\n", arquivo);
			}

		} else { //Se o arquivo não existe
			printf("Arquivo %s nao encontrado!\n", arquivo);
		}

    }

	return 0;
}