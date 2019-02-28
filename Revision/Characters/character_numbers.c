// Print decimal and hexadecimal characters

#include <stdio.h>

int main (int argc, char *argv[]) {
	
	int i = 32;

	while (i != 127) {

		printf("%d 0x%x %c\n", i, i, i);
		i++;
	}

	return 0;
}