//David Nguyen z5166106
//15/03/2018

#include <stdio.h>

int main(void) {

    double ger1, ger2, ger3;

    printf("Please enter three numbers: ");
    scanf("%lf %lf %lf", &ger1, &ger2, &ger3);

    if ((ger1+ger2) > ger3 && (ger2+ger3) > ger1 && (ger1+ger3) > ger2) {

    printf("triangle \n");

    } else {

    printf("not a triangle \n");

    }




return 0;
}
