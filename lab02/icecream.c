//David Nguyen z5166106

#include <stdio.h>

int main(void) {
    
    int money1 = 10;
    int scoops;
    int price;
    
    printf("How many scoops?  How many dollars does each scoop cost?  ");
    scanf("%d %d", &scoops, &price);

    int finalprice =scoops*price;
    
    if (money1>=finalprice) {
    printf("You have enough money!\n");
    } else {
    printf("Oh no, you don't have enough money :( \n");
    }

    


return 0;
}
