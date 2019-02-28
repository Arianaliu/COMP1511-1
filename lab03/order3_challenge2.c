//David Nguyen z5166106
//12/03/2018

#include <stdio.h>

int main(void) {
	

 	int ger1,ger2,ger3;

    printf("Enter integer: ");
    scanf("%d", &ger1);
    
    printf("Enter integer: ");
    scanf("%d", &ger2);
   
    printf("Enter integer: ");
    scanf("%d", &ger3);
  
    // 1 = true, 0 = false 

    printf("The integers in order are: %d %d %d \n", ((ger1==ger2 && ger2==ger3)*-ger1*2) + (ger1==ger2)*((ger1==ger2)*ger1 - (ger3<ger1 && ger3<ger2)*ger1 - (ger2<ger1 && ger2<ger3)*ger1) + (ger1==ger3)*((ger1==ger3)*ger3-(ger2<ger1 && ger2<ger3)*ger3) + (ger2==ger3)*((ger2==ger3)*ger2 - (ger1<ger2 && ger1<ger3)*ger2) + (ger1<ger2 && ger1<ger3)*ger1 + (ger2<ger1 && ger2<ger3)*ger2 + (ger3<ger1 && ger3<ger2)*ger3, ((ger1==ger2 && ger2==ger3)*-ger1*2) + (ger1==ger2)*ger1 + (ger1==ger3)*ger3 + (ger2==ger3)*ger2 + (ger1>ger2 && ger1<ger3)*ger1 + (ger1<ger2 && ger1>ger3)*ger1 + (ger2>ger1 && ger2<ger3)*ger2 + (ger2<ger1 && ger2>ger3)*ger2 + (ger3>ger1 && ger3<ger2)*ger3 + (ger3<ger1 && ger3>ger2)*ger3, ((ger1==ger2 && ger2==ger3)*-ger1*2) + (ger1==ger2)*((ger1==ger2)*ger1-(ger3>ger1 && ger3>ger2)*ger1) + (ger1==ger3)*((ger1==ger3)*ger3 - (ger2>ger1 && ger2>ger3)*ger3) + (ger2==ger3)*((ger2==ger3)*ger2 - (ger1>ger2 && ger1>ger3)*ger2) + (ger1>ger2 && ger1>ger3)*ger1 + (ger2>ger1 && ger2>ger3)*ger2 + (ger3>ger1 && ger3>ger2)*ger3);



	return 0;
}