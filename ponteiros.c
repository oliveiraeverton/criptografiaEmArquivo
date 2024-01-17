#include<stdio.h>



void modificaValor(int valor, int **ptrptr){


	**ptrptr = valor;



}


void inverteposicao(int **ptrptrposA,  int **ptrptrposB){


	int guardaInformacao = **ptrptrposA;
	**ptrptrposA = **ptrptrposB;
	**ptrptrposB = guardaInformacao;



}
int main(){


	int varA = 32;
	int varB = 91;

	int *pontA = &varA;
	int *pontB = &varB;


	printf("varA = %d , varB = %d\n", *pontA, *pontB); 


	int **ptrptrA = &pontA;
	int **ptrptrB = &pontB;


	printf("varA = %d , varB = %d\n", **ptrptrA, **ptrptrB);



	printf("*******************************************************************************************\n");



	int *vetor[3];

	vetor[0] = &varA;
	vetor[1] = &varB;
	vetor[2] = NULL;


	printf("varA = %d , varB = %d\n", **vetor, **(vetor+1));
	printf("varA = %d , varB = %d\n", *vetor[0], *vetor[1]);


	printf("*******************************************************************************************\n");



	modificaValor(101010, &vetor[0]);
	printf("varA = %d , varB = %d\n", **vetor, **(vetor+1));
	modificaValor(121212, &vetor[1]);
	printf("varA = %d , varB = %d\n", **vetor, **(vetor+1));



	printf("*******************************************************************************************\n");

	inverteposicao(&vetor[0], &vetor[1]);
	printf("varA = %d , varB = %d\n", **vetor, **(vetor+1));

	return 0;
}



