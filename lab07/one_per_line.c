// Prints one character per line 
// David Nguyen z5166106

#include <stdio.h>

void print (void);

int main(int argc, char *argv[]){
	
	print();

	return 0;
}

void print (void){
	char array[100];
	int i = 0;

	printf("Enter a string: ");
	fgets(array, 100, stdin);

	while ((array[i] >= '!' && array[i] <= '~') || array[i] == ' '){
		printf("%c \n", array[i]);
		i++;
	}
}	