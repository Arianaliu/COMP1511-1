// Ignores non characters
// David Nguyen z5166106
// 16/4/18

// NOTE TO SOLVE: Remove non characters and make caps = noncaps
// Use newstring

#include <stdio.h>
#include <string.h>
#include <assert.h>

int memory_return (int modlength, char string[], char newstring[], int mem);
char new_string (int modlength, char string[], char newstring[], int mem);
char reverse (int modlength, int mem, int length, char gnirts[], char 
			  newstring[]);
void print_palindrome (char gnirts[], char newstring[]);

int main(int argc, char *argv[]){
	
	char string[1000] = {'a'};
	char newstring[1000] = {'a'};
	char gnirts[1000] = {'a'};

	printf("Enter a string: ");
	fgets(string,1000,stdin);

	int length = strlen(string);
	int modlength = length - 2;
	int count = 0;
	int mem = 2;

	// Redos the first string without '\0' and '\n'
	*newstring = new_string(modlength, string, newstring, mem);
	// Returns a useful number
	mem = memory_return(modlength, string, newstring, mem);
	// Saves reverse order excluding '\0' and '\n'
	*gnirts = reverse(modlength, mem, length, gnirts, newstring);
	// Prints whether a palindrome or not
	print_palindrome(gnirts, newstring);

	return 0;
}

char new_string (int modlength, char string[], char newstring[], int mem){
	int i = 0;
	int count = 0;
	while (i <= modlength){
		if ((string[i] >= 'A' && string[i] <= 'Z') && string[i] != ' ') {
			string[i] = string[i] + 32;
		} else if ((string[i] >= 'a' && string[i] <= 'z') && string[i] != ' '){
			newstring[count] = string[i];
			i++;
			count++;
		} else {
			i++;
			mem++;
		}
	}
	return *newstring;
}

char reverse (int modlength, int mem, int length, char gnirts[], char 
			  newstring[]){
	int i = 0;
	while (i <= modlength){
		if (length-mem == -1){
			break;
		}
		gnirts[i] = newstring[length-mem];
		length--;
		i++;
	}
	return *gnirts;
}

int memory_return (int modlength, char string[], char newstring[], int mem){
	int i = 0;
	int count = 0;
	while (i <= modlength){
		if ((string[i] >= 'A' && string[i] <= 'Z') && string[i] != ' ') {
			string[i] = string[i] + 32;
		} else if ((string[i] >= 'a' && string[i] <= 'z') && string[i] != ' '){
			newstring[count] = string[i];
			i++;
			count++;
		} else {
			i++;
			mem++;
		}
	}
	return mem;
}

void print_palindrome (char gnirts[], char newstring[]){
	if (strcmp(gnirts,newstring) == 0){
		printf("String is a palindrome\n");
	} else {
		printf("String is not a palindrome\n");
	}
}