// Map digits 
// David Nguyen z5166106

#include <stdio.h>
#include <string.h>

#define BIG 1000

int main (int argc, char *argv[]){
		
	char *code = argv[1]; // Code for the numbers

	int character = getchar();

	while (character != EOF){
		
		if (character >= '0' && character <= '9'){
			if (character == '0'){
				character = code[0];
				putchar(character);
				character = getchar();
			} else if (character == '1'){
				character = code[1];
				putchar(character);
				character = getchar();
			} else if (character == '2'){
				character = code[2];
				putchar(character);
				character = getchar();
			} else if (character == '3'){
				character = code[3];
				putchar(character);
				character = getchar();
			} else if (character == '4'){
				character = code[4];
				putchar(character);
				character = getchar();
			} else if (character == '5'){
				character = code[5];
				putchar(character);
				character = getchar();
			} else if (character == '6'){
				character = code[6];
				putchar(character);
				character = getchar();
			} else if (character == '7'){
				character = code[7];
				putchar(character);
				character = getchar();
			} else if (character == '8'){
				character = code[8];
				putchar(character);
				character = getchar();
			} else {
				character = code[9];
				putchar(character);
				character = getchar();
			}
		} else {
			putchar(character);
			character = getchar();
		}

	}


	return 0;
}