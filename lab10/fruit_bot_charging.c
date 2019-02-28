// David Nguyen z5166106
// 15/4/18
// Where to charge?

#include <stdio.h>
#include <string.h>
#include <assert.h>

#define BIG 1000

#include "fruit_bot.h"

int nearest_electricity(struct bot *b);
int check_west (struct bot *b);

int main(int argc, char *argv[]) {
    struct bot *me = fruit_bot_input(stdin);

    int distance = nearest_electricity(me);
    printf("Distance to nearest available electricity is %d\n", distance);

    return 0;
}


// return distance to nearest electricity
// if nearest electricity is west return negative int
// if nearest electricity is current location return 0

int nearest_electricity(struct bot *b) {
    // PUT YOUR CODE HERE
    int i = 0;
    int east = 0;
    int result = 0;

    int west = check_west(b);
    struct location *save = b->location;

	while (i != BIG) { // East
		if (strcmp(save->fruit, "Electricity") == 0) {
			break; 
		} else {
			east++;
			save = save->east;
		}
	}	

	if (east <= west) {
		result = east;
	} else {
		result = -west;
	}

    return result;
}

int check_west (struct bot *b){
	int i = 0;
	int west = 0;

	struct location *save = b->location;

	while (i != BIG) { // West
		if (strcmp(save->fruit, "Electricity") == 0) {
			break;
		} else {
			west++;
			save = save->west;
		}
	}

	return west;
}

