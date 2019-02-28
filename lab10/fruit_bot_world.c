// David Nguyen z5166106
// 15/4/18

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "fruit_bot.h"

#define BIG 1000

void print_world(struct bot *b);

int kg_or_kj (struct bot *b);

int main(void) {
    struct bot *b = fruit_bot_input(stdin);
    print_world(b);
    return 0;
}

void print_world(struct bot *b) {
    int count[BIG] = {0};
    int i = 0;

    char temp[BIG];
    strcpy(temp, b->location->name);
    if (b->location->price > 0){
		if (kg_or_kj(b) == 0) {
			printf("%s: will buy %d kg of %s for $%d\n", b->location->name, 
				b->location->quantity, b->location->fruit, b->location->price);
		} else {
			printf("%s: will buy %d kJ of %s for $%d\n", b->location->name, 
				b->location->quantity, b->location->fruit, b->location->price);
		}
	} else if (b->location->price < 0) {
		if (kg_or_kj(b) == 0) {
			printf("%s: will sell %d kg of %s for $%d\n", b->location->name, 
				b->location->quantity, b->location->fruit, -1*b->location->price);
		} else {
			printf("%s: will sell %d kJ of %s for $%d\n", b->location->name, 
				b->location->quantity, b->location->fruit, -1*b->location->price);
		}
	} else if (strcmp(b->location->fruit, "Nothing") == 0 && b->location->price == 0
	&& b->location->quantity == 0) {
		printf("%s: other\n", b->location->name);
	} 

    b->location = b->location->east;

    while (strcmp(temp, b->location->name) != 0) {
    	if (b->location->price > 0){
    		if (kg_or_kj(b) == 0) {
    			printf("%s: will buy %d kg of %s for $%d\n", b->location->name, 
    				b->location->quantity, b->location->fruit, b->location->price);
    		} else {
    			printf("%s: will buy %d kJ of %s for $%d\n", b->location->name, 
    				b->location->quantity, b->location->fruit, b->location->price);
    		}
    	} else if (b->location->price < 0) {
    		if (kg_or_kj(b) == 0) {
    			printf("%s: will sell %d kg of %s for $%d\n", b->location->name, 
    				b->location->quantity, b->location->fruit, -1*b->location->price);
    		} else {
    			printf("%s: will sell %d kJ of %s for $%d\n", b->location->name, 
    				b->location->quantity, b->location->fruit, -1*b->location->price);
    		}
    	} else if (strcmp(b->location->fruit, "Nothing") == 0 && b->location->price == 0
    	&& b->location->quantity == 0) {
    		printf("%s: other\n", b->location->name);
    	} 

		b->location = b->location->east;
	}

}

int kg_or_kj (struct bot *b) {
	int result = 0;

	if (strcmp(b->location->fruit, "Electricity") == 0) {
		result = 1;
	} 

	return result;
}