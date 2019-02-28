//David Nguyen z5166106
//15/03/2018

#include <stdio.h>

int main(void) {

    int ger1, ger2;
    

    scanf("%d %d", &ger1, &ger2);

    if (ger1>ger2) {
   
    printf("%d \n", ger1-ger2);

    } else if (ger2>ger1) {

    printf("%d \n", ger2-ger1);

    } else {

    printf("equal \n");

    }
    


return 0;
}
