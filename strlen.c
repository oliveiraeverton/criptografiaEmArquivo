#include <stdio.h>
#include <string.h>

int main(){
	
	char entrada[20];

	printf("Digite uma frase:\n");
	scanf(" %[^\n]", entrada);


	printf(" %s\n\n", entrada);


	printf(" %d", strlen(entrada));



	return 0;
}