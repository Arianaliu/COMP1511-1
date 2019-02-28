//David Nguyen z5166106
//11/3/18

#include <stdio.h>

int main(void) {

int ger1, ger2, ger3;

printf("Enter integer: ");
scanf("%d", &ger1);

printf("Enter integer: ");
scanf("%d", &ger2);

printf("Enter integer: ");
scanf("%d", &ger3);

printf("The integers in order are: ");

//Integer 1 is the smallest

	if (ger1<=ger2 && ger1<=ger3) {

		printf("%d ", ger1);

		if (ger2>=ger3) {

			printf("%d %d \n", ger3, ger2);

		} else {

			printf("%d %d \n", ger2, ger3);

		}
	

//Integer 2 is the smallest

	} else if (ger2<=ger1 && ger2<=ger3){

		printf("%d ", ger2);

		if (ger1>=ger3){

			printf("%d %d \n", ger3, ger1);

		} else {

		printf("%d %d \n", ger1, ger3);

		}
	

	//Integer 3 is the smallest	

	} else {

		printf("%d ", ger3);

		if (ger2>=ger1) {

			printf("%d %d \n", ger1, ger2);

		} else {

			printf("%d %d \n", ger2, ger1);

		}

	}

return 0;

}

