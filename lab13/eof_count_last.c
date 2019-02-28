// Counts how many times the last number occurred

#include <stdio.h>

int main (int argc, char *argv[]) {

	int i = 0;
	int num[1000];
	int counter = 0;

	while (scanf("%d", &num[i]) == 1) {
		i++;
	}

	int j = 0;

	while (j != i) {
		if (num[j] == num[i-1]) {
			counter++;
			j++;
		} else {
			j++;
		}
	}

	printf("%d\n", counter);
	
	return 0;
}