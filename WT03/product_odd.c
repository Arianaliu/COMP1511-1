// Product of odd numbers between 2 integers
// David Nguyen z5166106
// 5/4/2018

#include <stdio.h>

int main(void) {

    int num1, num2, result = 1;
    num1 = num2 = 0;

    printf("Enter lower: ");
    scanf("%d", &num1);
    printf("Enter upper: ");
    scanf("%d", &num2);

    num1 = num1 +1;

    while (num1 < num2) { 
        
        
        if (num1 == num2) {
        break;
        }
        //printf("%d\n", result);
        //printf("%d\n", num1);

        if (num1%2 == 0){
        num1++;;
        } else if (num1%2 == 1) {
        result = result*num1;
        num1++;
        } else if (result == 1) {
        printf("1\n");
        }
    }

    printf("%d\n", result);
    
return 0;
}
