//Reads integer and prints out positive integers divisible by 3 or 5
//David Nguyen z5166106
//18/3/18

#include <stdio.h>

int main(void) {
    
    int number;
    int i = 1;
    
    printf("Enter number: ");
    scanf("%d", &number);

    while (i < number) {
    
        if (i%3 == 0) {
            printf("%d\n", i);
        } else if (i%5 == 0) {
            printf("%d\n", i);
        }

        i++;   

    }

return 0;
}
