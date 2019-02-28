// Reads integers until EOF

#include <stdio.h>

int check_even (int num[], int i);

int main (int argc, char *argv[]) {

	int num[1000];
	int i = 0;

	while (scanf("%d", &num[i]) == 1) {
		i++;
	}

	int j = 0;
	int even = 0;

	while (j != i) {
		if (check_even(num, i) == 0) {
			puts("");
			break;
		} else if (num[j]%2 == 0) {
			if (even+1 == check_even(num, i)) {
				printf("%d\n", num[j]);
				j++;
			} else {
				printf("%d ", num[j]);
				even++;
				j++;
			}
		} else {
			j++;
		}
	}

	return 0;
}

int check_even (int num[], int i) {
	int j = 0;
	int result = 0;

	while (j != i) {
		if (num[j]%2 == 0) {
			j++;
			result++;
		} else {
			j++;
		}
	}

	return result;
}