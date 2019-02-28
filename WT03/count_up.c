// Count
// David Nguyen z5166106
// 5/4/2018

#include <stdio.h>

int main(void) {

    int i = 0;
    int num1, num2;
    num1 = num2 = 0;

    printf("Enter lower: ");
    scanf("%d", &num1);
    printf("Enter upper: ");
    scanf("%d", &num2);

    while (num1 < num2){
    num1++;
    if (num1 == num2) {
    break;
    }
    printf("%d\n", num1);
    }


return 0;
}
