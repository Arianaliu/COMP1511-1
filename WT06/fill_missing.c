// Fills missing numbers
// David Nguyen z5166106
// 26/4/18

#include <stdio.h>

#define BIG_NUMBER 1000

void print_missing_numbers (int array[], int length);

int main (int argc, char *argv[]){

	int i = 0;
	int array[BIG_NUMBER] = {0};
	
	while (i < BIG_NUMBER){ // Scans until EOF
		if (scanf("%d", &array[i]) != 1){
			break;
		} else {
			i++;
		}
	}

	int length = i;
	i = 0;

	//printf("Length = %d\n", length);

	print_missing_numbers(array, length);
	printf("\n");

	return 0;
}

void print_missing_numbers (int array[], int length){

	int i = 0;
	int j = 1;
	int big = 0;

	// Checks what the biggest number is
	while (i < length) {
		if (array[i] > big){
			big = array[i];
			i++;
		} else {
			i++;
		}
	}

	i = 1;

	// Prints out the missing numbers
	while (i < big) {
		j = 0;
		while (j < length){
			if (array[j] == i){
				i++;
				break;
			} else if (j == length-1 && array[j] != i) {
				printf("%d ", i);
				i++;
				break;
			} else {
				j++;
			}
		}
	}

}
