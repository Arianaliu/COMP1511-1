// Reads 10 integers and prints odd on one line and even on the other
// David Nguyen z5166106
// 14/4/2018

#include <stdio.h>

#define ARRAY_SIZE 10

int main (int argc, char *argv[]){

	int num[ARRAY_SIZE];
	int i = 0;

	while (i < 10){
		scanf("%d", &num[i]);
		i++;
	}

	i = 0;

	printf("Odd numbers were: ");

	while (i < 10){

		if (num[i]%2 > 0){
			printf("%d ", num[i]);
		}

		i++;
	}

	i = 0;

	printf("\nEven numbers were: ");

	while (i < 10){
		if (num[i]%2 == 0){
			printf("%d ", num[i]);
		}
		i++;
	}

	printf("\n");

	return 0;
}