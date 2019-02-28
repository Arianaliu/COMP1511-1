// Most frequent integer
// David Nguyen z5166106
// 20/4/18

#include <stdio.h>

#define VERY_BIG_NUMBER 1000

int frequency (int num[], int length, int array[], int count[]);
int holder (int length, int count[], int array[]);

int main (int argc, char *argv[]){

	int num[VERY_BIG_NUMBER] = {0};
	int array[VERY_BIG_NUMBER] = {0};
	int i = 0;

	while (i < VERY_BIG_NUMBER) { // Scans input into an array
		if (scanf("%d", &num[i]) != 1) {
 			break;
		} else {
			i++;
		}
	}

	int length = i; // length - 1 should be the last element
	//printf("Length = %d\n", length);
	int count[VERY_BIG_NUMBER] = {1};
	count[0] = 0;  // To account for an abornamility in the code

	i = 0;

	while (i != length){ // Makes a copy of the array
		array[i] = num[i];
		i++;
	}

	int result = frequency (num, length, array, count);

	printf("%d\n", result);
	
	return 0;
}

int frequency (int num[], int length, int array[], int count[]){

	//Remove duplicates from the array
	int i = 0;
	int j = 0;
	int k = 0;
	int oglength = length;

	while (i < length){

		if (i+1 == length+1){
			break;
		} else {
		j = i+1;
		}

		while (j < length){
			if (array[i] == array[j] && array[i] != 0 && array[j] != 0){
				k = j;
				while (k < length){ // Makes the duplicate = next element in array
					if (k+1 == length){ // If it equals the element after the end breaks loop
						break;
					} else {
					array[k] = array[k+1];
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
	j = 0;

	// Records frequency of each element in original array
	while (i < length) {
		if (array[i] == num[j]){ // Checks frequency for each element
			count[i]++;
			j++;
		} else if (j == oglength){
			j = 0;
			i++;
		} else {
			j++;
		}
	}

	int final = holder (length, count, array);

	return array[final];
}

int holder (int length, int count[], int array[]){
	int i = 0;
	int result = 0;
	int memory = 0;

	while (i < length){ // Determines result
		if (count[i] > result){ // Saves frequency into result
			result = count[i];
			memory = i;			// Memory is now the I as placeholder
			i++;
		} else if (count[i] == result){ // If another frequency = result
			if (array[i] > array[memory]){ // Changes the result to the larger integer
				result = count[i];
				memory = i;
				i++;
			}  else { // Else if the integer is the same, just increment
				i++;
			}
		} else {
			i++;
		}
	}
	return memory;
}
