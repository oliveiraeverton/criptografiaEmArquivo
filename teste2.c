#include<stdio.h>


int main(){
	


	FILE *file;


	file = fopen("arquivo1.txt", "r");


	int k = 1;
	char c;
	while((k = fscanf(file, "%c", &c)) != EOF){
		printf("%c", c);
	}
	printf("\n\n");

	fclose(file);
	return 0;
}