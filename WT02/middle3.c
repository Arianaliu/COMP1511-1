// Prints the middle of 3 integers
// David Nguyen z5166106
// 24/3/18

#include <stdio.h>

int main(void) {

    int ger1, ger2, ger3;

    printf("Enter integer: ");
    printf("Enter integer: ");
    printf("Enter integer: ");

    scanf("%d", &ger1);
    scanf("%d", &ger2);
    scanf("%d", &ger3);
    
    // If Ger 1 is the middle
    if ((ger1 >= ger2 && ger1 <= ger3) || (ger1 >= ger3 && ger1 <= ger2)) {
    printf("Middle: %d \n", ger1);
    } else if ((ger2 >= ger1 && ger2 <= ger3) || (ger2 >= ger3 && ger2 <= ger1)) {
    printf("Middle: %d \n", ger2);
    } else {
    printf("Middle: %d \n", ger3);
    }

return 0;
}
