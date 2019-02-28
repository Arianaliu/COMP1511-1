//Reads positive input and prints factors and sum and is perfect or not
//David Nguyen z5166106
//18/3/18

#include <stdio.h>

int main(void) {

    int number1;
    int i = 1;
    int sum = 0;

    printf("Enter number: ");
    scanf("%d", &number1);

    int number2 = number1;
    
    printf("The factors of %d are: \n", number1);       

    while (i<=number2) {

        if (number2%i == 0) {
        	printf("%d\n", i);	
        	sum += i;
        }

        i++;
        
    }   

    printf("Sum of factors = %d \n", sum);
    
    if ((sum-number1) == number1) {
        printf("%d is a perfect number\n", number1);
    } else {
    	printf("%d is not a perfect number\n", number1);
    }


return 0;
}
