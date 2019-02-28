// Removes repeated lines
// David Nguyen z5166106
// 10/4/18

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 256

struct string {
	char string[MAX];
};

int main (int argc, char *argv[]){

	int i = 0;
	int count[MAX] = {0};

	// Declaring the struct string container and a temporary holder
	struct string stringcontainer[MAX];
	struct string temporary[MAX];

	// Step 1. Create a loop that continuosly records strings
	while (fgets(stringcontainer[i].string, MAX, stdin) != NULL) {
		int j = 0;
		strcpy(temporary[i].string, stringcontainer[i].string);
		// Step 2. Check if the string already exists if not print it!
		while (j <= i) {
			if (strcmp(stringcontainer[i].string, stringcontainer[j].string) 
				== 0) {
				if (count[j] == 0) {
					int newlength = strlen(stringcontainer[j].string);
					*&temporary[j].string[newlength-1] = // Deletes the newline at the end
					*&temporary[j].string[newlength];
					puts(temporary[j].string);
					count[j]++;
					i++;
					break;
				} else {
					i++;
					break;
				}
			} else {
				j++;
			}
		}
	}

	return 0;
}