// Danish Flag
// David Nguyen z5166106
// 19/3/18

#include <stdio.h>

void printFlag (int size);
void printFlag1 (int size, int col, int row);

int main(void) {
	
	int size;

	printf("Enter the flag size: ");
	scanf("%d", &size);

	printFlag (size);


	return 0;
}

void printFlag (int size) {

	int row = 1;
	int col = 1;

	while (row <= size*4) {

		printFlag1 (size, col, row);

		row++;
		printf("\n");
		col = 1;
	}
}

void printFlag1 (int size, int col, int row) {

while ( col <= size*9) {

			if ( col == size*3 || col == (size*3) + 1) {
				printf(" ");
			} else if (row == size*2 || row == (size*2) + 1) {
				printf(" ");
			} else {
				printf("#");
			}
			col++;
		}
}
