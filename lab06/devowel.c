// Devowel 
// David Nguyen z5166106
// 9/4/2018

#include <stdio.h>

int is_vowel (int character);

int main (void) {

    int character = getchar();

    while (character != EOF) {
        if (is_vowel (character) == 0){
        character = getchar();
        } else {
        putchar(character);
        character = getchar();
        }
    }

return 0;
}

int is_vowel (int character) {
    int i = 1;
    if (character == 'a'|| character == 'e' || character == 'i' || 
        character == 'o' ||character == 'u') {
        i = 0;
    } else {
        i = 1;
    }

    return i;
}