#include<stdio.h>
#include<stdlib.h>


struct filaEncadeada{

    char c;
    struct filaEncadeada *prox;


};


void enfileirar(char c, struct filaEncadeada **estruturaI, struct filaEncadeada **estruturaF){
    struct filaEncadeada *nova;
    nova = (struct filaEncadeada *) malloc(sizeof (struct filaEncadeada));
    (*nova).c = c;
    (*nova).prox = NULL;
    printf("c = %c\n", (*nova).c);

    if(*estruturaF == NULL){
        *estruturaI = nova;
        *estruturaF = nova;
     }else{
        (**estruturaF).prox = nova;
        *estruturaF = nova;
     }
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
int main(){

    int qtd = 3;
    struct filaEncadeada *vetor[3];
    struct filaEncadeada *vetorF[3];


    for(int i = 0; i < qtd; i++){
        vetor[i] = NULL;
        *(vetorF+i) = NULL;
    }



    enfileirar('T', &vetor[0], &vetorF[0]);
    enfileirar('R', &vetor[0], &vetorF[0]);
    enfileirar('I', &vetor[0], &vetorF[0]);
    enfileirar('C', &vetor[0], &vetorF[0]);
    enfileirar('K', &vetor[0], &vetorF[0]);
    
    char k[5];
    k[0] = desenfileirar(&vetor[0], &vetorF[0]);
    k[1] = desenfileirar(&vetor[0], &vetorF[0]);
    k[2] = desenfileirar(&vetor[0], &vetorF[0]);
    k[3] = desenfileirar(&vetor[0], &vetorF[0]);
    k[4] = desenfileirar(&vetor[0], &vetorF[0]);

    printf("%s\n", k);
    return 0;

    


}