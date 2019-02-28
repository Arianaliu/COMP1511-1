//David Nguyen z5166106
//12/3/18


#include <stdio.h>

int isLeapYear (int year);

 
int main() {
 
	int year;

 	printf("Enter year: ");
	scanf("%d", &year);

    int year1 = isLeapYear (year);

    if (year1 == 1) {

    	printf("%d is a leap year. \n", year);

    } else {

    	printf("%d is not a leap year. \n", year);

    }

    return 0;
}
 
int isLeapYear (year) {

	

	if  (year%400 == 0) {

		return 1;

	} else if (year%100 == 0 ) {

		return 0;
 
	} else if (year%4 == 0) {

		return 1;

	} else {

		return 0;

	}

}