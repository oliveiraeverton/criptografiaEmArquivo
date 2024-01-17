#include <stdio.h>
#include <string.h>

struct vetorArquivo{
	char nomeArquivoCriptografado[20];
	FILE *file;
};

int main(){


	FILE *file;
	char vetor[500];
	int qtdArq = 0;

    char nomeArquivoEntrada[20];
    printf("Digite o nome do arquivo:\n");

    scanf(" %s", nomeArquivoEntrada);
	file = fopen(nomeArquivoEntrada, "r");

    
    if (file == NULL) {
        printf("Não foi possível abrir o arquivo.\n");
        return 1; 
    }


    fscanf(file, " %[^\n]", vetor);
    fclose(file);


    printf("\n%s\n", vetor);

    printf("Em quantos arquivos você quer fragmentar o arquivo %s:\n", nomeArquivoEntrada);
    scanf("%d", &qtdArq);

    struct vetorArquivo vetorCriptografia[qtdArq];

    printf("Digite o nome do arquivo de destino\n");
    char arqDestino[20];
    scanf(" %s", arqDestino);

    char original[20];
    strcpy(original, arqDestino);


    sprintf(arqDestino + (strlen(arqDestino)), "%d", 0);
    strcat(arqDestino, ".txt");
    strcpy(vetorCriptografia[0].nomeArquivoCriptografado, arqDestino);
    printf("Nome do arquivo de destino: %s\n", vetorCriptografia[0].nomeArquivoCriptografado);

    for(int i = 1; i < qtdArq; i++){
    	strcpy(arqDestino, original);
    	// Usando sprintf para concatenar o inteiro no final da string
    	sprintf(arqDestino + (strlen(arqDestino)), "%d", i);
        strcat(arqDestino, ".txt");
    	strcpy(vetorCriptografia[i].nomeArquivoCriptografado, arqDestino);
    	printf("Nome do arquivo de destino: %s\n", vetorCriptografia[i].nomeArquivoCriptografado);
    }


   for(int i = 0; i < qtdArq; i++){
   		vetorCriptografia[i].file = fopen(vetorCriptografia[i].nomeArquivoCriptografado, "a");
   		if (vetorCriptografia[i].file == NULL) {
        printf("Não foi possível abrir o arquivo.\n");
        return 1; 
    }
   }
   for(int i = 0; i < strlen(vetor); i++){

   	fprintf(vetorCriptografia[i%qtdArq].file, "%c", vetor[i]);


   }

    

    for(int i = 0; i < qtdArq; i++){
        fclose(vetorCriptografia[i].file);
    }
	return 0;
}