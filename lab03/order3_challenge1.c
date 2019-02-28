//David Nguyen z5166106
//12/03/18

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
    // ger4 = smallest , ger5 = middle , ger6 = largest   
    // ger4  - (ger3<ger1 && ger3<ger2)*ger1 - (ger2<ger1 && ger2<ger3)*ger1
    // ger6   - (ger3>ger1 && ger3>ger2)*ger1

    int ger4 =  ((ger1==ger2 && ger2==ger3)*-ger1*2) + (ger1==ger2)*((ger1==ger2)*ger1 - (ger3<ger1 && ger3<ger2)*ger1 - (ger2<ger1 && ger2<ger3)*ger1) + (ger1==ger3)*((ger1==ger3)*ger3-(ger2<ger1 && ger2<ger3)*ger3) + (ger2==ger3)*((ger2==ger3)*ger2 - (ger1<ger2 && ger1<ger3)*ger2) + (ger1<ger2 && ger1<ger3)*ger1 + (ger2<ger1 && ger2<ger3)*ger2 + (ger3<ger1 && ger3<ger2)*ger3;
    int ger5 =  ((ger1==ger2 && ger2==ger3)*-ger1*2) + (ger1==ger2)*ger1 + (ger1==ger3)*ger3 + (ger2==ger3)*ger2 + (ger1>ger2 && ger1<ger3)*ger1 + (ger1<ger2 && ger1>ger3)*ger1 + (ger2>ger1 && ger2<ger3)*ger2 + (ger2<ger1 && ger2>ger3)*ger2 + (ger3>ger1 && ger3<ger2)*ger3 + (ger3<ger1 && ger3>ger2)*ger3;
    int ger6 =  ((ger1==ger2 && ger2==ger3)*-ger1*2) + (ger1==ger2)*((ger1==ger2)*ger1-(ger3>ger1 && ger3>ger2)*ger1) + (ger1==ger3)*((ger1==ger3)*ger3 - (ger2>ger1 && ger2>ger3)*ger3) + (ger2==ger3)*((ger2==ger3)*ger2 - (ger1>ger2 && ger1>ger3)*ger2) + (ger1>ger2 && ger1>ger3)*ger1 + (ger2>ger1 && ger2>ger3)*ger2 + (ger3>ger1 && ger3>ger2)*ger3;

    printf("The integers in order are: %d %d %d \n", ger4, ger5, ger6);

return 0;
}
