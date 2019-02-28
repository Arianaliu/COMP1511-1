//David Nguyen z5166106

#include <stdio.h>

int main(void) {


    int year;

    printf("Enter Year: ");
    scanf("%d", &year);

    int a = year%19;
    int b = year/100;
    int c = year%100;
    int d = b/4;
    int e = b%4;
    int f = (b+8)/25;
    int g = (b-f+1)/3;
    int h = (19*a+b-d-g+15)%30;
    int i = c/4;
    int k = c%4;
    int l = (32+2*e+2*i-h-k)%7;
    int m = (a+11*h+22*l)/451;

    //1 = jan 2 = march 3 = april
    int month =(h+l-7*m+114)/31;
    int p = (h+l-7*m+114)%31;

    //day in easter month
    int date = p+1;

    if (month == 3) {
    printf("Easter is March %d in %d. \n", date, year);
    } else {
    printf("Easter is April %d in %d. \n", date, year);
    } 









return 0;
}
