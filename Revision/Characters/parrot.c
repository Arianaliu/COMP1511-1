// Parrot sqawk

#include <stdio.h>

int main (int argc, char *argv[]) {
	
	int character = getchar();

	while (character != EOF) {
		putchar(character);
		character = getchar();
	}

	return 0;
}