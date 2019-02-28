 // Encryption by substitution cypher
// David Nguyen z5166106
// 11/4/2018

#include <stdio.h>

#define ALPHABET_SIZE 26

int encrypt_caps (int character, int decap[], int cap[]);
int encrypt_notcaps (int character, int denotcap[], int notcap[]);

int main(int argc, char *argv[]) {
	char *code = argv[1];
	int character = getchar();

	int i = 0;
	int capscount = 65;

	int j = 0;;
	int notcapscount = 97;

	int count = 0;
	int decap[ALPHABET_SIZE] = {0};
	int cap[ALPHABET_SIZE] = {0};
	int denotcap[ALPHABET_SIZE] = {0};
	int notcap[ALPHABET_SIZE] = {0};

	count = 0;

	// To set the bounds of the array (Normal Alphabet)
	while (i < 26){
		cap[i] = capscount;
		decap[i] = capscount;
		notcap[i] = notcapscount;
		denotcap[i] = notcapscount;
		capscount++;
		notcapscount++;
		i++;
	}

	i = 0;

	while (i < ALPHABET_SIZE){ // Inserts the code for caps
		cap[i] = code[count] - 32; // 'a' = 97 so 97 - 32 = 'A' for new code
		count++;
		i++;
	}

	i = 0;
	count = 0;

	while (j < ALPHABET_SIZE){ // Inserts code for noncaps
		notcap[j] = cap[i] + 32;
		i++;
		count++;
		j++;
	}

	while (character != EOF){
		if (character >= 'A' && character <= 'Z'){
			character = encrypt_caps(character, decap, cap);
		} else if (character >= 'a' && character <= 'z'){
			character = encrypt_notcaps(character, denotcap, notcap);
		} else {
			putchar(character);
			character = getchar();
		}
	}
	return 0;
}

int encrypt_caps (int character, int decap[], int cap[]){
	int i = 0;
	while (i < ALPHABET_SIZE) {
		if (decap[i] == character){
			putchar(cap[i]);
			character = getchar();
			break;
		} else {
			i++;
		}
	}
	return character;
}

int encrypt_notcaps (int character, int denotcap[], int notcap[]){
	int i = 0;
	while (i < ALPHABET_SIZE) {
		if (denotcap[i] == character){
			putchar(notcap[i]);
			character = getchar();
			break;
		} else {
			i++;
		}
	}
	return character;
}