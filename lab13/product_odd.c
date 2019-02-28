// Product of odd

#include <stdio.h>

int main (int argc, char *argv[]) {

	int lower;
	int upper;
	int result = 1;
	
	printf("Enter lower: ");
	scanf("%d", &lower);
	printf("Enter upper: ");
	scanf("%d", &upper);

	int i = lower+1;

	while (i != upper) {
		if (i%2 == 1) {
			result = result * i;
			i++;
		} else {
			i++;
		}
	}

	printf("%d\n", result);

	return 0;
}