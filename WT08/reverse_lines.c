// Prints line in reverse
// David Nguyen z5166106
// 10/4/18

#include <stdio.h>

#define MAX 256

int main (int argc, char *argv[]){
	
	int character = getchar();
	int array[MAX];
	int newarray[MAX];
	int i = 0;
	int j = 0;
	int length = 0;
	int modlength = 0;

	while (character != EOF) {
		// Step 1 - Record the original string
		if (character != '\n') {
			array[i] = character;
			character = getchar();
			i++;
			length = i;
			modlength = length;
		} else if (character == '\n') {
		// Step 2 - Record and print the reverse
			array[i] = character;
			j = 0;
			while (j < modlength) {
				newarray[j] = array[length-1];
				putchar(newarray[j]);
				length--;
				j++;
			}
			i = length;
			newarray[j] = '\n';
			putchar(newarray[j]);
			character = getchar();
		} else {
			character = getchar();
		}
		
	}

	return 0;
}