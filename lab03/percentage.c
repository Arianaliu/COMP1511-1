//David Nguyen z5166106
//12/3/2018

#include <stdio.h>

int main(void) {

    double mark, award;

    printf("Enter the total number of marks in the exam: ");
    scanf("%lf", &mark);

    printf("Enter the number of marks the student was awarded: ");
    scanf("%lf", &award);

    double perc = award/mark;

    printf("The student scored %0.0lf%% in this exam. \n", perc*100);



return 0;
}
