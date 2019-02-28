// Encryption by Caesar Cypher 
// David Nguyen z5166106
// 11/4/2018

#include <stdio.h>
#include <stdlib.h> 

int encrypt_cap(int character, int shift, int i);
int encrpyt_noncap(int character, int shift, int i);

int main(int argc, char *argv[]) {

    int character = getchar();
    int shift = atoi(argv[1]);

    while (character != EOF) {
    	int i = 0;
        if (character >= 'A' && character <= 'Z'){ // For caps only
	        character = encrypt_cap(character, shift, i);
        } else if (character >= 'a' && character <= 'z') { // For non caps only
	        character = encrpyt_noncap(character, shift, i);
        } else { // If it isn't a character, puts it 
	        putchar(character); 
	        character = getchar();
        }
    }

return 0;
}
 
int encrypt_cap(int character, int shift, int i){
	if (shift > 0) {	// For upwards only
    	while (i < shift){ // Will increment upwards and reset everytime > 'Z'
    		character = character + 1;
    		if (character > 'Z'){
    			character = 'A';
    			i++;
    		} else {
    			i++;
    		}
    	}
	} else if (shift < 0){ // For downwards only
		while (i > shift){ // Will increment downwards and reset everytime < 'A'
    		character = character - 1;
    		if (character < 'A'){
    			character = 'Z';
    			i--;
    		} else {
    			i--;
    		}
    	}
	}
    putchar(character);
    character = getchar();
    return character;
}

int encrpyt_noncap(int character, int shift, int i){
	if (shift > 0) {	// For upwards only
    	while (i < shift){ 
    		character = character + 1;
    		if (character > 'z'){
    			character = 'a';
    			i++;
    		} else {
    			i++;
    		}
    	}
	} else if (shift < 0){ // For downwards only
		while (i > shift){ 
    		character = character - 1;
    		if (character < 'a'){
    			character = 'z';
    			i--;
    		} else {
    			i--;
    		}
    	}
	}
    putchar(character);
    character = getchar();
    return character;
}
