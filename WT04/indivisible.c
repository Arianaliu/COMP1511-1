// Prints out indivisible numbers
// David Nguyen z5166106
// 14/4/18

#include <stdio.h>

#define VERY_LARGE_NUMBER 1000

int main (int argc, char *argv[]){

	int num[VERY_LARGE_NUMBER] = {1};
	int i     = 0;
	int j     = 0;  
	int count = 0;
	int store = 0;
	
	while (i < VERY_LARGE_NUMBER) {
		if (scanf("%d", &num[i]) != 1){
			break;
		} else if (num[i] == 1) {
			perror(argv[0]);
			break;
		} else {
			i++;
		}
	}

	count = 0;

	printf("Indivisible numbers: ");
	
	while (count < i){
		if (num[count]%num[j] == 0 && count != j && count != i-1) {
			count++;
			j = 0;
		} else if (count == i-1){ //Last number
			if (num[count]%num[j] == 0 && count != j){
				break;
			} else if (num[count]%num[j] != 0 && j == i-2){
				printf("%d ", num[count]);
				break;
			} else {
				j++;
				if (j == count){
					j = 0;
				}
			}
		} else if (count == j){
			j++;
			if (j > i-1) {
				j = 0;
			}
		} else if (num[count]%num[j] != 0 && count != i-1
				   && j == i-1){ // For not the last
			printf("%d ", num[count]);
			j = 0;
			count++;
		} else {
			j++;
		}
	}

	printf("\n");

	return 0;
}