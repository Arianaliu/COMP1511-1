// Prints an L
// David Nguyen z5166106
// 24/3/18

#include <stdio.h>

int main(void) {

    int size, row = 1, i = 1;

    printf("Enter size: ");
    scanf("%d", &size);

    while (row <= size) {

    if ( row == size ) {
        while ( i <= size ){
        printf("*");
        i++;
        }
        printf("\n");
    } else {
    printf("*\n");
    }
    
    row++;
    }
    
return 0;
}
