#include<stdio.h>
#include<string.h>
#include<stdlib.h>
struct vetorArquivo{
	char nomeArquivoCriptografado[20];
	FILE *file;
};

struct filaEncadeada{

	char c;
	struct filaEncadeada *prox;


};


void enfileirar(char c, struct filaEncadeada **estruturaI, struct filaEncadeada **estruturaF, int *totalCaracter){
    struct filaEncadeada *nova;
    nova = (struct filaEncadeada *) malloc(sizeof (struct filaEncadeada));
    (*nova).c = c;
    (*nova).prox = NULL;
    //printf("c = %c\n", (*nova).c);

    if(*estruturaF == NULL){
        *estruturaI = nova;
        *estruturaF = nova;
    }else{
        (**estruturaF).prox = nova;
        *estruturaF = nova;
    }
    (*totalCaracter)++;
    //printf("%d %c\n", *totalCaracter, c);
    //free(nova);
}
char desenfileirar(struct filaEncadeada **estruturaI, struct filaEncadeada **estruturaF){

    char c;
    if(*estruturaI == NULL){
    	return '\0';
    }else{
    	struct filaEncadeada *nova;
        
        nova = *estruturaI;
        (*estruturaI) = (*nova).prox;
        c = (*nova).c;
        if(*estruturaI == NULL){
            *estruturaF = NULL;
        }
        free(nova);
        return c;
    }


    return c;
}

void limparFila(){
	//implementar
}
int main(){
	int  totalCaracter = 0;
	char arquivoInicial[20];
	int qtdArquivo;
	printf("Digite o nome do arquivo inicial:\n");
	scanf(" %s", arquivoInicial);

	printf("Digite a quantidade de arquivos existentes:\n");
	scanf("%d", &qtdArquivo);

	struct vetorArquivo vetor[qtdArquivo];
    


    char original[20];
    strcpy(original, arquivoInicial);


    sprintf(arquivoInicial + (strlen(arquivoInicial)), "%d", 0);
    strcat(arquivoInicial, ".txt");
    strcpy(vetor[0].nomeArquivoCriptografado, arquivoInicial);
    printf("Nome do arquivo de destino: %s\n", vetor[0].nomeArquivoCriptografado);

    for(int i = 1; i < qtdArquivo; i++){
    	strcpy(arquivoInicial, original);
    	// Usando sprintf para concatenar o inteiro no final da string
    	sprintf(arquivoInicial + (strlen(arquivoInicial)), "%d", i);
        strcat(arquivoInicial, ".txt");
    	strcpy(vetor[i].nomeArquivoCriptografado, arquivoInicial);
    	printf("Nome do arquivo de destino: %s\n", vetor[i].nomeArquivoCriptografado);
    }


    FILE *arquivo;

    arquivo = fopen("original.txt", "a");

    if (arquivo == NULL) {
        printf("Não foi possível abrir o arquivo.\n");
        return 1; 
    }

    
    struct filaEncadeada *filaI[qtdArquivo];
    struct filaEncadeada *filaF[qtdArquivo];

    for(int i = 0; i < qtdArquivo; i++){
		filaI[i] = NULL;
		*(filaF+i) = NULL;
	}

    //abre os arquivos e enfileira os caracteres
    for(int i = 0; i < qtdArquivo; i++){
    	
    	int k = 1;
    	char c;


    	vetor[i].file = fopen(vetor[i].nomeArquivoCriptografado, "r");
    	if (vetor[i].file == NULL) {
        printf("Não foi possível abrir o arquivo.\n");
        return 1; 
    }
    	while((k = fscanf(vetor[i].file, "%c", &c)) != EOF){
			//printf("%c", c);
			//printf("AQUI!!\n");
			//enfileirar
			enfileirar(c, &filaI[i], &filaF[i], &totalCaracter);
		}
		printf("\n");
		fclose(vetor[i].file);
    }



    //fprintf(arquivo, "%c", desenfileirar(&filaI[0], &filaF[0]));
    for(int i = 0; i < totalCaracter/qtdArquivo; i++){

    	for(int w = 0; w < qtdArquivo; w++){
    		fprintf(arquivo, "%c", desenfileirar(&filaI[w], &filaF[w]));
    	}
    	
    }

    for(int w = 0; w < qtdArquivo; w++){
    	if(filaF[w] != NULL){
    		fprintf(arquivo, "%c", desenfileirar(&filaI[w], &filaF[w]));
    	}
    }
    fclose(arquivo);

	return 0;
}