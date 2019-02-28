// Prints first 10 lines or specified by -n
// David Nguyen z5166106
// 17/4/18

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_lines1 (int character, FILE *fptr, char *argv[]);
void print_lines2 (int character, FILE *fptr, char *argv[]);

int main (int argc, char *argv[]){

	// Saves argv[1] to a string 
	char *listnum = argv[1];
	
	if (strcmp(listnum,"-n") == 0){ // If the string is -n then it does this
		FILE *fptr;
		fptr = fopen(argv[3],"r");
		int character = fgetc(fptr);
		print_lines1 (character, fptr, argv);
		fclose(fptr);		
		if (fptr == NULL) {
	    perror(argv[0]);
	    return 1;
  		}
	} else { // Prints for 10 lines and if less than 10 lines prints all
		FILE *fptr;
		fptr = fopen(argv[1],"r");
		int character = fgetc(fptr);
		print_lines2 (character, fptr, argv);
		fclose(fptr);
		if (fptr == NULL) {
	    perror(argv[0]);
	    return 1;
  		}
	}

	return 0;
}

void print_lines1 (int character, FILE *fptr, char *argv[]){
	int count = 0;

	while (character != EOF){
		if (character == '\n'){
			printf("%c", character);
			character = fgetc(fptr);
			count++;
		} else if (count == atoi(argv[2])){ // argv[2] is # lines to print
			break;
		} else {
			printf("%c", character);
			character = fgetc(fptr);
		}
	}
}

void print_lines2 (int character, FILE *fptr, char *argv[]){
	int count = 0;

	while (character != EOF){
		if (character == '\n'){
			printf("%c", character);
			character = fgetc(fptr);
			count++;
		} else if (count == 10){
			break;
		} else {
			printf("%c", character);
			character = fgetc(fptr);
		}
	}
}