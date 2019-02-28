// Does the same as odd_even_ten but stops when negative is read
// David Nguyen z5166106
// 14/4/18

#include <stdio.h>

#define ARRAY_SIZE 1000

int main (int argc, char *argv[]){

	int num[ARRAY_SIZE];
	int i = 0;
	int limit = 0;

	while (i < ARRAY_SIZE){
		scanf("%d", &num[i]);
		if (num[i] < 0 ){
			limit = i;
			break;
		}
		i++;
	}

	i = 0;

	printf("Odd numbers were: ");

	while (i < limit){

		if (num[i]%2 > 0){
			printf("%d ", num[i]);
		}
		i++;
	}

	i = 0;

	printf("\nEven numbers were: ");

	while (i < limit){
		if (num[i]%2 == 0){
			printf("%d ", num[i]);
		}
		i++;
	}

	printf("\n");

	return 0;
}