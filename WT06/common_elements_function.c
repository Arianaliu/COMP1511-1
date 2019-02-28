// David Nguyen z5166106
// 26/4/18

#include <stdio.h>

int common_elements(int length, int source1[length], int source2[length], int 
					destination[length]);

int main (int argc, char *argv[]){

	int source1[100]     = {0};
	int source2[100]     = {0};
	int destination[100] = {0};
	int length        =  0;
	int i             =  0;

	printf("Enter length: ");
	scanf("%d", &length);
	
	printf("Source1 = ");
	while (i < length){
		scanf("%d", &source1[i]);
		i++;
	}

	i = 0;
	printf("Source2 = ");
	while (i < length){
		scanf("%d", &source2[i]);
		i++;
	}

	int result = common_elements(length, source1, source2, destination);

	printf("%d\n", result);

	return 0;
}

int common_elements(int length, int source1[length], int source2[length], int 
					destination[length]){
	int copied = 0;
	int i      = 0;
	int j      = 0;
	int k      = 0;

	while (i < length){
		j = 0;
		while (j < length){
			if (source1[i] == source2[j] && source2[j] != 0 && source1[i] != 0){
				destination[k] = source1[i];
				//printf("destination[%d] = %d\n", k, destination[k]);
				copied++;
				k++;
				break;
			} else {
				j++;
			}
		}
		i++;
	}

	return copied;
}