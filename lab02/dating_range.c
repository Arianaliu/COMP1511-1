//David Nguyen 5166106

#include <stdio.h>

int main(void) {

    int age;
    
    printf("Enter your age: ");
    scanf("%d", &age);

    if (age<18) {
    printf("You are too young to be dating. \n");
    } else if (age>=18) { 
    printf("Your dating range is %d to %d years old. \n", (age/2) +7, (age-7)*2);
    }




return 0;
}
