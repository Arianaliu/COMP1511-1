// Remove duplicates from array
// David Nguyen z5166106
// 20/4/18

#include <stdio.h>

#define BIG_NUM 1000

int remove_duplicates(int length, int source[length], int destination[length]);

int main (int argc, char *argv[]){

	int length;
	int i = 0;

	printf("Enter length of array: ");
	scanf("%d", &length);

	int source[BIG_NUM] = {0};
	int destination[BIG_NUM] = {0};

	while (i < length){
		scanf("%d",&source[i]);
		i++;
	}

	i = 0;

	int result = remove_duplicates(length, source, destination);

	printf("Copied: %d\n", result);

return 0;
}

int remove_duplicates(int length, int source[length], int destination[length]){
	int i = 0;
	int j = 0;
	int k = 0;
	int copied = 0;

	while (i < length){

		if (i+1 == length+1){
			break;
		} else {
		j = i+1;
		}

		while (j < length){
			if (source[i] == source[j] && source[i] != 0 && source[j] != 0){
				k = j;
				while (k < length){ // Makes the duplicate = next element in array
					if (k+1 == length){ // If it equals the element after the end breaks loop
						break;
					} else {
					source[k] = source[k+1];
					k++;
					}
				}
				length--; // Shortens the array to account for the deletion of the duplicate
			} else 
				j++;
		}

		i++;
	}

	i = 0;

	// Copies the pure source into the destination array
	while (i < length){
		destination[i] = source[i];
		i++;
		copied++;
	}

	return copied;
}