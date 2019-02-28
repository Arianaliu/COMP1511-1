// Word count
// David Nguyen z5166106

#include <string.h>
#include <stdio.h>

#define MAXWORD 1000

int word_counter (char wordarray[], int i);
int check_blanks (char wordarray[], int length);
void print_results (int newlinecount, int wordcount, int charactercount);

int main (int argc, char *argv[]){
	
	int character      = getchar();
	char wordarray[MAXWORD] = {'a'};
	int newlinecount   = 0;
	int wordcount      = 0;
	int charactercount = 0;

	int i = 0;
	int length = 0;

	while (character != EOF)	{
		if (character == '\n'){
			if (i == 0 || wordarray[i-1] == '\n'){
				newlinecount++;
				charactercount++;
				wordarray[i] = character;
				i++;
				character = getchar();
			} else {
				newlinecount++;
				wordcount++;
				charactercount++;
				wordarray[i] = character;
				i++;
				character = getchar();
			}
		} else if ((i >= 2) && ((character >= 'A' && character <= 'Z') || 
					(character >= 'a' &&character <= 'z'))){ // Word counter
			if (word_counter(wordarray, i) == 1){
				charactercount++;
				wordcount++;
				wordarray[i] = character;
				i++;
				character = getchar();
			} else {
				charactercount++;
				wordarray[i] = character;
				i++;
				character = getchar();
			}
		} else { // Anything else
			charactercount++;
			wordarray[i] = character;
			i++;
			character = getchar();
		}
	}

	length = i;

	if (wordarray[i-1] != '\n'){ // If the last character isnt a new line, adds a word
		wordcount++;
	}

	if (check_blanks(wordarray, length) == 0){
		wordcount = 0;
		print_results(newlinecount, wordcount, charactercount);
	} else {
		print_results(newlinecount, wordcount, charactercount);
	}

	return 0;
}

int word_counter (char wordarray[], int i){
	int result = 0;

	if ((wordarray[i-1] == ' ' && (wordarray[i-2] >= 33 && wordarray[i-2] <= 
		126)) || (((wordarray[i-1] >= 33 && wordarray[i-1] <= 47) || (wordarray[i-1]
		>= 58 && wordarray[i-1] <= 64) || (wordarray[i-1] >= 91 && wordarray[i-1] <= 96) 
		|| (wordarray[i-1] >= 123 && wordarray[i-1] <= 126)) && wordarray[i-2] == ' ')){
		result = 1;
	} else {
		result = 0;
	}

	return result;
}

int check_blanks (char wordarray[], int length){
	int i = 0;
	int result = 0;

	while (i < length){
		if ((wordarray[i] >= 'A' && wordarray[i] <= 'Z') || 
			(wordarray[i] >= 'a' && wordarray[i] <= 'z')){
			result = 1;
			i++;
		} else {
			i++;
		}
	}

	return result;
}

void print_results (int newlinecount, int wordcount, int charactercount){
	printf("\n%d lines %d words %d characters\n", newlinecount, wordcount, 
			charactercount);
}
