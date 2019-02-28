// Prime factors
// David Nguyen z5166106
// 5/4/2018

#include <stdio.h>

int main(void) {

    int num1, result;
    int i = 0;
    int j = 3;

    printf("Enter number: ");
    scanf("%d", &num1);

    if (num1%7 != 0 && num1%2 != 0 && num1%5 != 0){
    printf("%d is prime\n", num1);
    return 0;
    } else {
    printf("The prime factorization of %d is:\n", num1);
    }

    result = num1;

    while (num1%2 == 0) {
        printf("%d", 2);
        if (num1 == 2){
        break;
        } else if (num1%2 == 0 || num1%3 == 0 || num1%5 == 0 || num1%7 == 0){
        printf(" * ");
        } 
        num1 = num1/2;
    }

    while (i < 1000) {
        while (num1%j == 0) {
            printf("%d ", j);
            if (num1 == 3 || num1 == 5 || num1 == 7) {
            break;
            } else if (num1%2 == 0 || num1%3 == 0 || num1%5 == 0 || num1%7 == 0){
            printf("* ");
            }
            num1 = num1/j;
        }
    i = i+2;
    j = j + 2;;
    }

    printf("= %d\n", result);
return 0;
}
