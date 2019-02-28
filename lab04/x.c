// David Nguyen z5166106
// 19/3/18

#include <stdio.h>

int main (void) {

    int col=1, row=1, i=1, size;

    printf("Enter size: ");
    scanf("%d", &size);
       
    int j = size;

    while (row <= size) {
    
       while (i<=size) {

            if ( col == row ) {
                printf("*");
                if ( row == size-((size-1)/2)) {
                	j = size-((size-1)/2)-1;
                }
            } else if ( col == j ) {
            	printf("*");
            	j--;
            } else {
                printf("-");
            }
            
            i++;
            col++;
       }

        row++;
        printf("\n");
        i = 1;
        col = 1;    
       
    }


return 0;
}
