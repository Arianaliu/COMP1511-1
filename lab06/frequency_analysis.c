// Frequency 
// David Nguyen z5166106
// 10/4/18

#include <stdio.h>

int sum (int count[], int sum, int j);

int main(void) {
	
	int input = getchar();
	float frequency[26] = {0};
	float count[26] = {0};
	float sum = 0;
	int i = 97;
	int j = 0;

	while (input != EOF){
		if (input == 'a' || input == 'A') {
			count[0]++;  
			input = getchar();
		} else if (input == 'b' || input == 'B'){
			count[1]++;
			input = getchar();
		} else if (input == 'c' || input == 'C'){
			count[2]++;
			input = getchar();
		} else if (input == 'd' || input == 'D'){
			count[3]++;
			input = getchar();
		} else if (input == 'e' || input == 'E'){
			count[4]++;
			input = getchar();
		} else if (input == 'f' || input == 'F'){
			count[5]++;
			input = getchar();
		} else if (input == 'g' || input == 'G'){
			count[6]++;
			input = getchar();
		} else if (input == 'h' || input == 'H'){
			count[7]++;
			input = getchar();
		} else if (input == 'i' || input == 'I'){
			count[8]++;
			input = getchar();
		} else if (input == 'j' || input == 'J'){
			count[9]++;
			input = getchar();
		} else if (input == 'k' || input == 'K'){
			count[10]++;
			input = getchar();
		} else if (input == 'l' || input == 'L'){
			count[11]++;
			input = getchar();
		} else if (input == 'm' || input == 'M'){
			count[12]++;
			input = getchar();
		} else if (input == 'n' || input == 'N'){
			count[13]++;
			input = getchar();
		} else if (input == 'o' || input == 'O'){
			count[14]++;
			input = getchar();
		} else if (input == 'p' || input == 'P'){
			count[15]++;
			input = getchar();
		} else if (input == 'q' || input == 'Q'){
			count[16]++;
			input = getchar();
		} else if (input == 'r' || input == 'R'){
			count[17]++;
			input = getchar();
		} else if (input == 's' || input == 'S'){
			count[18]++;
			input = getchar();
		} else if (input == 't' || input == 'T'){
			count[19]++;
			input = getchar();
		} else if (input == 'u' || input == 'U'){
			count[20]++;
			input = getchar();
		} else if (input == 'v' || input == 'V'){
			count[21]++;
			input = getchar();
		} else if (input == 'w' || input == 'W'){
			count[22]++;	
			input = getchar();
		} else if (input == 'x' || input == 'X'){
			count[23]++;
			input = getchar();
		} else if (input == 'y' || input == 'Y'){
			count[24]++;
			input = getchar();
		} else if (input == 'z' || input == 'Z') {
			count[25]++;
			input = getchar();
		} else {
			input = getchar();
		}

	}

// Keeps count of total letters typed

	while (j < 26){
		sum = sum + count[j];
		j++;
	}
	
	j = 0;

// Frequency
	while (j < 26){
	
		frequency[j] = count[j]/sum;
		j++;
		
	}

	j = 0;

// Prints out letter frequency and count
	while (i <= 122) {
		printf("'%c' %lf %.0lf \n", i, frequency[j], count[j]);
		j++;
		i++;
	}

	return 0;
}