// Hollow triangle
// David Nguyen z5166106
// 24/3/18

#include <stdio.h>

int main(void) {

    int size, row = 1, col = 1;

    printf("Enter size: ");
    scanf("%d", &size);

    while (row <= size) {

        while (col <= row) {
            if ( row == size ) {
            printf("*");
            } else if (col == row) {
            printf("*");
            } else if (row >= 3 && col >= 2){
            printf(" ");
            } else {
            printf("*");
            }
        col++;
        }

    printf("\n");
    col = 1;
    row++;
    }


return 0;
}
