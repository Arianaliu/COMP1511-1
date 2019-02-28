 //David Nguyen 5166106
 //6/3/18

#include <stdio.h> 

int main(void) {

	int ger1, ger2;
	int i, j;

  const char *a[21];
  	a[0] = "negative ten";
  	a[1] = "negative nine";
  	a[2] = "negative eight";
  	a[3] = "negative seven";
  	a[4] = "negative six";
  	a[5] = "negative five";
  	a[6] = "negative four";
  	a[7] = "negative three";
  	a[8] = "negative two";
  	a[9] = "negative one";
  	a[10] = "zero";
  	a[11] = "one";
  	a[12] = "two";
  	a[13] = "three";
  	a[14] = "four";
  	a[15] = "five";
  	a[16] = "six";
    a[17] = "seven";
    a[18] = "eight";
    a[19] = "nine";
    a[20] = "ten";
    
    
    printf("Please enter two integers: ");
    scanf("%d %d", &ger1, &ger2);

    
    
    if (ger1<11 && ger1>-11) {
    
//  Prints word (one...)
    		for (i=-10; i<=ger1; i++) {
    		    if (i==ger1) {
    			printf("%s + ", a[i+10]);
    			break;
    			} 
   		     }
   		     
// If ger1>10 or ger1<-10 (print number)   		     
	} else if (ger1>10) {
	printf("%d + ", ger1);
	} else if (ger1<-10) {
	printf("%d + ", ger1);
	}
	
	
	if (ger2<11 && ger2>-11) {
	
//  Prints word (one...)	
	         for (j=-10; j<=ger2; j++) {
  		  		if (j==ger2) {
  				printf("%s = ", a[j+10]);
  				break;
  				} 
   			 }
   			 
//  If  ger2>10 or ger2<-10 (print number)
	} else if (ger2>10) {
 	printf("%d = ", ger2);
    } else if (ger2<-10) {
    printf("%d = ", ger2);
    }


//  Word solution
	if (ger1+ger2<=10 && ger1+ger2>=-10){
		if (ger1>10) {
	
		int ger3 = ger1+ger2;
		int k;
	
		for (k=-10; k<=ger3; k++) {
			if (k==ger3) {
			printf("%s\n", a[k+10]);
			}
		}
		} else {
		printf("%s\n", a[i+j+10]);
		}
	}

//  Number solution
	if (ger1+ger2>10) {
	printf("%d \n", ger1+ger2);
	} else if (ger1+ger2<-10) {
	printf("%d \n", ger1+ger2);
	}


return 0;
}
