// How long is a (piece of) string?
// Created by
//  ... (z0000000)
//  ... (z0000000)
// Created on 2017-08-??
// Tutor's name (dayHH-lab)

#include <assert.h>
#include <stdio.h>
#include <string.h>

int string_length(char *string);

int main(int argc, char *argv[]) {

    // Some simple assert-based tests.
    // You probably want to write some more.
    assert(string_length("") == 0);
    assert(string_length("!") == 1);
    assert(string_length("Hello, world!") == 13);
    assert(string_length("17... seventeen.\n") == 17);

    printf("All tests passed.  You are awesome!\n");

    return 0;
}

// Takes a string and finds its length, excluding the null-terminator.
int string_length(char *string) {
    int length = strlen(string);

    return length;
}