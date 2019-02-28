// David Nguyen z5166106
// 15/4/18

#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "fruit_bot.h"

void print_player_name(void);
void print_move(struct bot *b);

int main(int argc, char *argv[]) {
    struct bot *me = fruit_bot_input(stdin);
    if (me == NULL) {
        print_player_name();
    } else {
        print_move(me);
    }

    return 0;
}

void print_player_name(void) {
    printf("West McWesty");

}

void print_move(struct bot *b) {
	char action[100];
	int value;
	int move = 0;

		if (strcmp(b->location->fruit, "Electricity") == 0) {
			if (b->battery_level != b->battery_capacity && b->location->
				quantity >= (b->battery_capacity - b->battery_level)) {
				printf("Buy %d\n", b->battery_capacity - b->battery_level);
			} else {
				printf("Move -%d\n", b->maximum_move);
				move++;
			}
		} else if (strcmp(b->location->fruit, "Apples") == 0) {
			if (b->location->price < 0) { // Buying
				if (b->fruit_kg != b->maximum_fruit_kg && b->location->
					quantity >= (b->maximum_fruit_kg - b->fruit_kg) && 
					b->fruit_kg == 0){
					printf("Buy %d\n", b->maximum_fruit_kg - b->fruit_kg);
				} else if (b->location->quantity 
					< (b->maximum_fruit_kg - b->fruit_kg)){
					printf("Buy %d\n", b->location->quantity);
				} else {
					printf("Move -%d\n", b->maximum_move);
				}
			} else if (b->location->price > 0) { // Selling
				if (b->location->quantity >= b->fruit_kg && b->fruit_kg != 0) {
					printf("Sell %d\n", b->fruit_kg);
				} else {
					printf("Move -%d\n", b->maximum_move);
				}
			} else {
				printf("Move -%d\n", b->maximum_move);
			}
		} else {
			printf("Move -%d\n", b->maximum_move);
		}

}
