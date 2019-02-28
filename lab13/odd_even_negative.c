// Read odd and even numbers

#include <stdio.h>

int check_even (int array[], int i);
int check_odd  (int array[], int i);

int main (int argc, char *argv[]){

	int i = 0;
	int array[1000] = {0};

	scanf("%d", &array[i]);
	
	while (array[i] >= 0) {
		i++;
		scanf("%d", &array[i]);
	}

	int k = 0;
	int oddprint = 0;
	printf("Odd numbers were: ");

	while (k != i) { // Odd
		if (oddprint + 1 == check_odd(array, i) && array[k]%2 == 1) {
			printf("%d\n", array[k]);
			k++;
		} else if (array[k]%2 == 1) {
			printf("%d ", array[k]);
			oddprint++;
			k++;
		} else {
			k++;
		}
	}

	if (oddprint == 0) {
		printf("\n");
	}

	int j = 0;
	int evenprint = 0;
	printf("Even numbers were: ");

	while (j != i) { // Even
		if (evenprint + 1 == check_even(array, i) && array[j]%2 == 0) {
			printf("%d\n", array[j]);
			j++;
		} else if (array[j]%2 == 0) {
			printf("%d ", array[j]);
			evenprint++;
			j++;
		} else {
			j++;
		}
	}

	if (evenprint == 0) {
		printf("\n");
	}

	return 0;
}

int check_odd (int array[], int i) {
	int oddcounter = 0;
	int count = 0;

	while (count != i) {
		if (array[count]%2 == 1) {
			oddcounter++;
			count++;
		} else {
			count++;
		}
	}

	return oddcounter;
}

int check_even (int array[], int i) {
	int evencounter = 0;
	int count = 0;

	while (count != i) {
		if (array[count]%2 == 0) {
			evencounter++;
			count++;
		} else {
			count++;
		}
	}

	return evencounter;
}