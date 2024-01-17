#include<stdio.h>
#include<stdlib.h>
#include<string.h>
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
	int k; 
	char c, cc;
	int totalCaracter=0;
	int numero = 0;

	char nomeArquivoInicial[20];
	int qtdArquivoFragmentado;

	// SEMPRE TEMOS QUE INICAR COM NULL
	struct filaEncadeada *filaIchave = NULL;
	struct filaEncadeada *filaFchave = NULL;



	// *********************************************************** ************************
	// *********************************************************** ARQUIVO CHAVE
	// *********************************************************** ************************
	file = fopen("arquivo_chave.txt", "r");

	if(file == NULL){
		printf("Arquivo chave não foi aberto\n");
		return 1;
	}

	while((k = fscanf(file, "%c", &c)) != EOF){
		enfileirar(c, &filaIchave, &filaFchave, &totalCaracter);
	}
	fclose(file);



	// *********************************************************** ÁREA DE DEBBUGER
	/*char ww;
	for(int i = 0; i < totalCaracter; i++){
		ww = desenfileirar(&filaIchave, &filaFchave);
		printf("%c ", ww);
	}*/
	// *********************************************************** ÁREA DE DEBBUGER



	// *********************************************************** ************************
	// *********************************************************** LEITURA DE DADOS CMD
	// *********************************************************** ************************

	printf("Digite o nome do arquivo inicial:");
	scanf(" %s", nomeArquivoInicial);
	printf("\n");

	printf("Digite a quantidade de arquivos fragmentados:");
	scanf("%d", &qtdArquivoFragmentado);
	printf("\n");



	// *********************************************************** ***************************
	// *********************************************************** LÓGICA PARA MONTAR OS .txt
	// *********************************************************** ***************************

	char original[20];
    strcpy(original, nomeArquivoInicial);

	struct vetorArquivo vetArquivo[qtdArquivoFragmentado];
    sprintf(nomeArquivoInicial + (strlen(nomeArquivoInicial)), "%d", 0);
    strcat(nomeArquivoInicial, ".txt");
    strcpy(vetArquivo[0].nomeArquivoCriptografado, nomeArquivoInicial);
    printf("Nome do arquivo de destino: %s\n", vetArquivo[0].nomeArquivoCriptografado);
    vetArquivo[0].file = fopen(vetArquivo[0].nomeArquivoCriptografado,"r");
    
    for(int i = 1; i < qtdArquivoFragmentado; i++){
    	strcpy(nomeArquivoInicial, original);
    	// Usando sprintf para concatenar o inteiro no final da string
    	sprintf(nomeArquivoInicial + (strlen(nomeArquivoInicial)), "%d", i);
        strcat(nomeArquivoInicial, ".txt");
    	strcpy(vetArquivo[i].nomeArquivoCriptografado, nomeArquivoInicial);
    	printf("Nome do arquivo de destino: %s\n", vetArquivo[i].nomeArquivoCriptografado);

    	vetArquivo[i].file = fopen(vetArquivo[i].nomeArquivoCriptografado,"r");
    	if(vetArquivo[i].file == NULL){
    		printf("ERRO AO ABRIR O ARQUIVO");
    		return 0;
    	}
    }


    
    // ABRINDO O ARQUIVO PARA MONTAR O ORIGINAL
    file = fopen("original.txt", "a");

	if(file == NULL){
		printf("Arquivo chave não foi aberto\n");
		return 1;
	}


	// MONTAR O ARQUIVO ORIGINAL
	for(int i = 0; i < totalCaracter; i++){

		c = desenfileirar(&filaIchave, &filaFchave);
		numero = c - '0'; // CONVERTER PARA INTEIRO (FUNCIONA DE 0 a 9), OU SEJA O ARQUIVO FRAGMENTADO TEM Q SER DE TAMANHO ATÉ 9 NESSA IMPLEMENTAÇÃO;
		fscanf(vetArquivo[numero].file, "%c", &cc);
		fprintf(file,"%c", cc);
	
	}
	fclose(file);
	for(int i = 0; i < qtdArquivoFragmentado; i++){
		fclose(vetArquivo[i].file);
	}

	return 0;
}