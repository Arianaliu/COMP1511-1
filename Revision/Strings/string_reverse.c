// CONVERT A STRING TO UPPERCASE
// CREATED BY
//  ... (Z0000000)
//  ... (Z0000000)
// CREATED ON 2017-08-??
// TUTOR'S NAME (DAYHH-LAB)

#include <stdio.h>
#include <string.h>

/// THIS WON'T WORK!
///
/// str only points to a string literal, which it is not legal to change.
/// If you attempt to modify it on Linux you will get a runtime error.
//
// char *str = "Hello!"
// string_reverse(str)

void string_reverse(char *buffer);

int main(int argc, char *argv[]) {
    char str[] = ".'neetneves' :egassem terces A";
    string_reverse(str);
    printf("%s\n", str);
    return 0;
}

// Takes a string in `buffer`, and reverses it in-place.
void string_reverse(char *buffer) {
   int length = strlen(buffer);
   char template[1000];
   strcpy(template, buffer);
   int i = length-1;
   int j = 0;

   while (j != length) {
   		buffer[j] = template[i];
   		i--;
   		j++;
   }

}