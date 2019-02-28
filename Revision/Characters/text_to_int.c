// Text to int

#include <stdio.h>

int main (int argc, char *argv[]) {
	
	int character = getchar();

	while (character != EOF) {
		printf("%d\n", character);
		character = getchar();
	}

	return 0;
}