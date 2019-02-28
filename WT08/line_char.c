// Line character
// David Nguyen z5166106
// 10/4/18

#include <stdio.h>

#define MAX_CHAR 256

int main (int argc, char *argv[]){
	
	int character       = getchar();
	int position        = 0;
	int array[MAX_CHAR] = {'z'};
	int i               = 0;

	while (character != '\n') {
		array[i] = character;
		character = getchar();
		i++;
	}

	scanf("%d", &position);
	printf("The character in position %d is '%c'\n", position, array[position]);

	return 0;
}