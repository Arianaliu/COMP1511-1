// Digit filler
// DAvid Nguyen z5166106
// 4/5/18

#include <stdio.h>

int main (int argc, char *argv[]){
	
	int i = getchar();

	while ( i != EOF){
		if ((i >= '0' && i <= '9') || i == ' ' || i == '\n'){
			putchar(i);
			i = getchar();
		} else {
			i = '.';
			putchar(i);
			i = getchar();
		}

	}

	return 0;
}