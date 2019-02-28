// Swaps upper to lower and vice versa
// David Nguyen z5166106
// 9/4/2018

#include <stdio.h>

#define ARRAY_SIZE 1000

int swap_case(int character);

int main (void) {

    int character = getchar();

  
    while (character != EOF) {
        if (swap_case (character) == 0){
        character = character - 32;
        putchar(character);
        character = getchar();
        } else if (swap_case (character) == 2){
        character = character + 32;
        putchar(character);
        character = getchar();
        } else {
        putchar(character);
        character = getchar();
        }
    }

return 0;
}

int swap_case(int character) {
    int i = 1;
    if (character >= 'a' && character <= 'z'){
        i = 0;
    } else if (character >= 'A' && character <= 'Z'){
        i = 2;
    } else {
        i = 1;
    }
    return i;
}  

