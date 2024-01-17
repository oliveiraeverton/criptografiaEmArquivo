#include<stdio.h>


int main(){





	char G = 'G';
	char o = 'o';
	char g = 'g';



	int numero = 0;

	printf("%c é no ASCII %d\n", G, G);
	printf("%c é no ASCII %d\n", o, o);
	printf("%c é no ASCII %d\n", g, g);



	printf("%c é no ASCII %d\n", G, G%3);
	printf("%c é no ASCII %d\n", o, o%3);
	printf("%c é no ASCII %d\n", g, g%3);
	return 0;
}