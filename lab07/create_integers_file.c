// Create file of third arg
// David Nguyen z5166106
// 17/4/18

#include <stdio.h>
#include <stdlib.h>

void genesis (char *argv[], FILE *fptr);

int main (int argc, char *argv[]){

  if (argc > 4){ // More than 3 arguments is an error
    printf("Error! More than 3 arguments entered.\n");
    return 1;
  }

  FILE *fptr;
  fptr = fopen (argv[3], "w");

  if (fptr == NULL) {
      perror(argv[0]);
      return 1;
  }

  genesis (argv, fptr);

  fclose(fptr);

	return 0;
}

void genesis (char *argv[], FILE *fptr){
  int i = atoi(argv[1]);

  while (i <= atoi(argv[2])){
    fprintf(fptr, "%d\n", i);
    i++;
  }
}