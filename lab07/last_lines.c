// Prints last 10 lines
// David Nguyen z5166106
// 17/4/18

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, char *argv[]){
 	
	FILE *fptr;
	fptr = fopen(argv[1],"r");
	int count = 0;
	int othercount = 0;
	int character = fgetc(fptr);

	while (character != EOF){ // Checks how many lines there are in file
		if (character == '\n'){
			character = fgetc(fptr);
			othercount++;
			count++;
		} else {
			character = fgetc(fptr);
			othercount++;
		}
	}

	int end = count - 10;

	if (count < 10){ // If less than 10 Lines in file prints all
		rewind(fptr);
		character = fgetc(fptr);
		while (character != EOF){
			if (character == '\n'){
				printf("%c", character);
				character = fgetc(fptr);
				end++;
			} else {
				printf("%c", character);
				character = fgetc(fptr);
			}
		}
	} else { // Does the other 
		count = 0;
		rewind(fptr);
		character = fgetc(fptr);
		while (character != EOF){
			if (character == '\n' && count != end){
				count++;
				character = fgetc(fptr);
			} else if (count == end) {
				printf("%c", character);
				character = fgetc(fptr);
			} else {
				character = fgetc(fptr);
			}
		}
	}

	fclose(fptr);

	if (fptr == NULL) {
    perror(argv[0]);
    return 1;
	}

	return 0;
}