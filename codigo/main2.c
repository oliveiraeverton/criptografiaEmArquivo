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

	// *********************************************************** ************************
	// *********************************************************** DECLARAÇÃO DE VARIÁVEIS
	// *********************************************************** ************************
	FILE *file;
	char arquivoEntrada[20];
	char c, k;
	int totalCaracter = 0;
	int qtdArquivo = 0;
	int numero = 0; // É O DECIMAL DA TABELA ASCII

	// SEMPRE TEMOS QUE INICAR COM NULL
	struct filaEncadeada *filaI = NULL;
	struct filaEncadeada *filaF = NULL;


	// *********************************************************** ************************
	// *********************************************************** LEITURA DE DADOS CMD
	// *********************************************************** ************************
	printf("Digite o nome do arquivo de entrada: ");
	scanf(" %s", arquivoEntrada);
	printf("\n");
	printf("Digite a quantidade de arquivo para a fragmentação:");
	scanf(" %d", &qtdArquivo);
	printf("\n");

	// VERIFICANDO SE O ARQUIVO PRINCIPAL FOI ABERTO COM SUCESSO
	file = fopen(arquivoEntrada, "r");
	if(file == NULL){
		printf("Erro ao abrir o arquivo %s", arquivoEntrada);
		return 1;
	}


	// *********************************************************** *********************
	// *********************************************************** ARQUIVOS FRAGMENTAÇÃO
	// *********************************************************** *********************

	struct vetorArquivo vetArquivo[qtdArquivo];
	// ************************* LEITURA DE DADOS CMD (NOME DO ARQUIVO DE DESTINO)
	printf("Digite o nome do arquivo de destino:");
    char arqDestino[20];
    scanf(" %s", arqDestino);
    printf("\n");


    char original[20];
    strcpy(original, arqDestino);


    // *********************************************************** ***************************
	// *********************************************************** LÓGICA PARA MONTAR OS .txt
	// *********************************************************** ***************************
    sprintf(arqDestino + (strlen(arqDestino)), "%d", 0);
    strcat(arqDestino, ".txt");
    strcpy(vetArquivo[0].nomeArquivoCriptografado, arqDestino);
    printf("Nome do arquivo de destino: %s\n", vetArquivo[0].nomeArquivoCriptografado);
    vetArquivo[0].file = fopen(vetArquivo[0].nomeArquivoCriptografado,"a");
    
    for(int i = 1; i < qtdArquivo; i++){
    	strcpy(arqDestino, original);
    	// Usando sprintf para concatenar o inteiro no final da string
    	sprintf(arqDestino + (strlen(arqDestino)), "%d", i);
        strcat(arqDestino, ".txt");
    	strcpy(vetArquivo[i].nomeArquivoCriptografado, arqDestino);
    	printf("Nome do arquivo de destino: %s\n", vetArquivo[i].nomeArquivoCriptografado);

    	vetArquivo[i].file = fopen(vetArquivo[i].nomeArquivoCriptografado,"a");
    }


	
    // *********************************************************** ********************
	// *********************************************************** ENFILEIRAR OS DADOS
	// *********************************************************** ********************
	while((k = fscanf(file, "%c", &c)) != EOF){
		enfileirar(c, &filaI, &filaF, &totalCaracter);
	}
	fclose(file); // PODEMOS FECHAR O ARQUIVO, POIS NÃO USAREMOS MAIS, TODOS OS DADOS CONTIDO NELE ESTÁ NA FILA

	// É NECESSÁRIO ABRIR O ARQUIVO_CHAVE PARA CONSEGUIR REMONTAR O ARQUIVO NOVAMENTE PARA O ESTADO ORIGINAL
	file = fopen("arquivo_chave.txt", "a");


	// *********************************************************** ÁREA DE DEBBUGER
	//for temporario
	/*for(int i = 0; i < totalCaracter; i++){
		k = desenfileirar(&filaI, &filaF);
		printf("%c", k);
	}
	*/
	// *********************************************************** ÁREA DE DEBBUGER

	for(int i = 0; i < totalCaracter; i++){
		k = desenfileirar(&filaI, &filaF);
		numero = (int)k;
		numero = numero%qtdArquivo;
		printf("O caracter %c foi para o arquivo %s\n", k, vetArquivo[numero].nomeArquivoCriptografado);
		fprintf(vetArquivo[numero].file, "%c", k);
		fprintf(file, "%d", numero);
	}






	// *********************************************************** FECHA OS ARQUIVOS RESTANTES
	for(int i = 0; i < qtdArquivo; i++){
		fclose(vetArquivo[i].file);
	}
	fclose(file);

	return 0;
}