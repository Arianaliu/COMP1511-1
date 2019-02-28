// Checks if the string is a palindrome
// David Nguyen z5166106
// 16/4/18

#include <stdio.h>
#include <string.h>
#include <assert.h>

int check_num(int modlength, char gnirts[]);
void print_palindrome(int modlength, char gnirts[], char newstring[]);

int main(int argc, char *argv[]){
	
	char string[1000] = {'a'};
	char newstring[1000] = {'a'};
	char gnirts[1000] = {'a'};

	printf("Enter a string: ");
	fgets(string,1000,stdin);

	int length = strlen(string);
	int modlength = length - 2;
	int i = 0;
	int count = 0;

	//printf("String length = %d \n", length);

	// Redos the first string without '\0' and '\n'
	while (i <= modlength){
		newstring[i] = string[i];
		i++;
	}

	i = 0;

	// Saves reverse order excluding '\0' and '\n'
	while (i <= modlength){
		gnirts[i] = string[length-2];
		length--;
		i++;
	}

	i = 0;

	//printf("%s %s \n", gnirts, newstring);
	if (check_num(modlength, gnirts) == 1){
		print_palindrome(modlength, gnirts, newstring);
	} else if (strcmp(gnirts,newstring) == 0){
		printf("String is a palindrome\n");
	} else {
		printf("String is not a palindrome\n");
	}
	return 0;
}

int check_num (int modlength, char gnirts[]){
	int result = 0;
	int i = 0;
	while (i <= modlength){
		if (gnirts[i] >= '0' && gnirts[i] <= '9'){
			i++;
			result = 1;
		} else {
			i++;
		}
	}
	return result; 
}

void print_palindrome (int modlength, char gnirts[], char newstring[]){
	int i = 0;
	int count = 0;
	while (i <= modlength){
		if (gnirts[i] != newstring[i]){
			printf("String is not a palindrome\n");
			break;
		} else if (gnirts[i] == newstring[i]){
			count++;
			if (count == modlength){
				printf("String is a palindrome\n");
				break;
			} else {
				i++;
			}
		} else {
			i++;
		}
	}
}