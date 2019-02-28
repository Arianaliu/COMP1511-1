// Perform the ROT13 algorithm on a string
// Completed by
//  ... (z0000000)
//  ... (z0000000)
// Commpleted on 2017-08-??
// Tutor's name (day_hH-lab)

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 256

// Add your own #defines here

void rotate_thirteen(char *string);
char rotate_one(char c);
void rotate_thirteen(char *string);
int strings_equal(char *string1, char *string2);

// Add your own function porototypes here

int main(int argc, char *argv[]) {
    // Example tests
    char test_a[MAX_LENGTH] = "Hello, world!";
    rotate_thirteen(test_a);
    assert(strings_equal("Uryyb, jbeyq!", test_a));

    char test_b[MAX_LENGTH] = "abcdefghijklmnopqrstuvwxyz";
    rotate_thirteen(test_b);
    assert(strings_equal("nopqrstuvwxyzabcdefghijklm", test_b));

    char test_c[MAX_LENGTH] = "The quick brown fox jumped over the lazy dog.";
    rotate_thirteen(test_c);
    assert(strings_equal("Gur dhvpx oebja sbk whzcrq bire gur ynml qbt.", test_c));

    // Add your own tests here

    char test_d[MAX_LENGTH] = "hello";
    rotate_thirteen(test_d);
    assert(strings_equal("uryyb", test_d));

    printf("All tests passed. You are awesome!\n");

    return 0;
}

void rotate_thirteen(char *string) {
    int i = 0;
    int length = strlen(string);

    while (i != length) {
        if (string[i] >= 'A' && string[i] <= 'Z') {
            int j = 0;
            while (j < 13){ 
                string[i] += 1;
                if (string[i] > 'Z'){
                    string[i] = 'A';
                    j++;
                } else {
                    j++;
                }
            }
            i++;
        } else if (string[i] >= 'a' && string[i] <= 'z') {
            int j = 0;
            while (j < 13){ 
                string[i] += 1;
                if (string[i] > 'z'){
                    string[i] = 'a';
                    j++;
                } else {
                    j++;
                }
            }
            i++;
        } else {
            i++;
        }
    }
}

char rotate_one(char c) {

if (c >= 'A' && c <= 'Z') {
    int j = 0;
    while (j != 1) {
        if (c > 90) {
            c = 'A';
            j++;
        } else {
            c += j;
            j++;
        }
    }
} else if (c >= 'a' && c <= 'z') {
    int j = 0;
    while (j != 1) {
        if (c+j > 122) {
            c = 'a';
            j++;
        } else {
            c += j;
            j++;
        }
    }
}

    return c;
}

int strings_equal(char *string1, char *string2) {
    int result = strcmp(string1, string2);

    if (result == 0) {
        result = 1;
    } else if (result > 0 || result < 0) {
        result = 0;
    } 

    return result;
}