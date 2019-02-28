// fruit_bot.c
// Assignment 3, COMP1511 18s1: Fruit Bot
//
// This program by David Nguyen (z5166106) on 25/5/18
//
// Version 1.0.0: Assignment released.
// Version 1.0.1: minor bug in main fixed

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <math.h>

#include "fruit_bot.h"

// DEFINES

#define BIG_NUMBER 1000
#define FALSE 0
#define TRUE 1

void print_player_name(void);
void print_move(struct bot *b);
void run_unit_tests(void);

// ADD PROTOTYPES FOR YOUR FUNCTIONS HERE

int nearest_electricity (struct bot *b);
int move_to_buy         (struct bot *b, int price, char location[]);
int move_to_sell        (struct bot *b, int price, char location2sell[]);
char fruit_to_buy       (struct bot *b, char fruit[]);
int buy_to_budget       (struct bot *b);
int fruit_to_sell_price (struct bot *b);
int fruit_to_buy_price  (struct bot *b, char fruit[]);
int buyers_for_fruit    (struct bot *b, struct location *temp);
char fruit_location_buy (struct bot *b, char location[]);
char fruit_location_sell (struct bot *b, char location2sell[]);
int purchase_enough     (struct bot *b);
int check_electricity   (struct bot *b);
int move_and_buy_conditions (struct bot *b, int price);

// YOU SHOULD NOT NEED TO CHANGE THIS MAIN FUNCTION

int main(int argc, char *argv[]) {

    if (argc > 1) {
        // supply any command-line argument to run unit tests
        run_unit_tests();
        return 0;
    }

    struct bot *me = fruit_bot_input(stdin);
    if (me == NULL) {
        print_player_name();
    } else {
        print_move(me);
    }

    return 0;
}

void print_player_name(void) {
    printf("Mr. Meeseeks");
}

// print_move - should print a single line indicating
//              the move your bot wishes to make
//
// This line should contain only the word Move, Sell or Buy
// followed by a single integer

void print_move(struct bot *b) {

    char fruit[BIG_NUMBER] = {'a'}; 
    char location[BIG_NUMBER] = {'a'};
    *location =     fruit_location_buy(b, location);
    *fruit =        fruit_to_buy(b, fruit);
    int price = fruit_to_buy_price(b, fruit);

    if (b->battery_level <= sqrt(b->battery_capacity) && b->turns_left >= 5 &&
        check_electricity(b) == 1 && b->cash > 10) { // Seek and buy electricity if i'm half empty
        if (strcmp(b->location->fruit, "Electricity") != 0) {
            if (b->maximum_move < nearest_electricity(b)) {
                printf("Move %d\n", b->maximum_move);
            } else {
                printf("Move %d\n", nearest_electricity(b));
            }
        } else if ((b->battery_capacity - b->battery_level)*(-1*b->location->
                   price > b->cash)) {
            printf("Buy %d\n", b->battery_capacity - b->battery_level/2);
        } else {
            printf("Buy %d\n", b->battery_capacity - b->battery_level);
        }
    } else if (b->fruit_kg > 0) { // Sell
        int sellprice = fruit_to_sell_price(b);
        char location2sell[BIG_NUMBER] = {'a'};
        *location2sell = fruit_location_sell(b, location2sell);
        if ((strcmp(b->location->fruit, b->fruit) != 0 || b->location->price < 
            0) || b->location->quantity == 0) {
            if (b->maximum_move < move_to_sell(b, sellprice, location2sell)) {
                printf("Move %d\n", b->maximum_move);
            } else {
                printf("Move %d\n", move_to_sell(b, sellprice, location2sell));
            }
        } else if (b->fruit_kg >= b->location->quantity) {
            printf("Sell %d\n", b->location->quantity);
        } else if (b->fruit_kg < b->location->quantity) {
            printf("Sell %d\n", b->fruit_kg);
        }
    } else if (move_and_buy_conditions(b, price) == TRUE) { // Buy
        if ((strcmp(b->location->fruit, fruit) != 0 || b->location->price > 0) 
            || b->location->quantity == 0 ) {
            if (b->maximum_move < move_to_buy(b, price, location)) {
                printf("Move %d\n", b->maximum_move);
            } else {
                printf("Move %d\n", move_to_buy(b, price, location));
            }
        } else if (b->location->quantity > purchase_enough(b) && b->cash >= 
                   -1*(purchase_enough(b)*b->cash)) { // Buy enough to sell out a buyer
            printf("Buy %d\n", purchase_enough(b));
        } else if (b->location->quantity < b->maximum_fruit_kg - b->fruit_kg // Buy all quantity if i have the money
                && b->cash >= -1*(b->location->quantity*b->location->price)) {
            printf("Buy %d\n", b->location->quantity);
        } else if (b->location->quantity >= b->maximum_fruit_kg - b->fruit_kg // Buy as much as i can carry
                   && b->cash >= -1*(b->maximum_fruit_kg - b->fruit_kg)*b->
                   location->price) {
            printf("Buy %d\n", b->maximum_fruit_kg - b->fruit_kg);
        } else if (b->cash < -1*(b->maximum_fruit_kg - b->fruit_kg)*b->location
                   ->price) { // Buy as much as i can afford
            printf("Buy %d\n", buy_to_budget(b));
        }
    } else {
        printf("Move 0\n");
    }
}


// Firstly, i started simple. Used silly strategies in order to get a sense of
// how to go about with this bot. I made sure the bot printed our variables such as
// (Buy %d, Move %d, Sell %d, Variables from my functions) and made sure my functions 
// returned what i wanted them to return
// e.g. fruit_to_buy returns "Apples", fruit_location_buy returns "Kensington Apple Farm"
// This is to make sure the bot followed my strategy that i implemented.
// I ran many simulations in tiny, medium and large worlds in order to make sure my bot
// was consistent with the profits made. These many simulations helped me further refine my testing strategy
// There were some implications like; getting stuck at a location for 50 turns,
// buying fruit when i have no cash, buying electricity till i became broke
// , not buying fruit at all in the simulation and not making profit at all.
// As a result, i devised functions or added conditions to rectify these errors
// For instance; i only buy electricity if there are suppliers in the world.
// Overall, my testing strategy was simply to work slowly and weed out the bugs.

void run_unit_tests(void) {
    // All my functions use structs and pointers :(
}

// ADD YOUR FUNCTIONS HERE

// Function to move to the most profitable fruit from fruit_to_buy
int move_to_buy (struct bot *b, int price, char location[]) {
    int moveeast = 0;
    int movewest = 0;
    int move = 0;
    struct location *east = b->location;
    struct location *west = b->location;

    // Uses location of the fruit from fruit_to_buy to find the route
    // To the the location

    while (strcmp(east->name, location) != 0) { // Checks easterly
        east = east->east;
        moveeast++;
    }

    while (strcmp(west->name, location) != 0) { // Checks westerly
        west = west->west;
        movewest++;
    }

    if (movewest < moveeast) { // Sees which route is the fastest to buy
        move = -1*movewest;
    } else {
        move = moveeast;
    }

    return move;
}

// Finding the best fruit to buy
char fruit_to_buy (struct bot *b, char fruit[]) {
    int     cheapest = -20;
    struct  location *temp = b->location;
    struct  location *save = b->location;

    // Finds the most profitable fruit to buy and returns the name of the fruit
    if (temp->price < cheapest && temp->price < 0 && strcmp(temp->fruit,
        "Electricity") != 0 && strcmp(temp->fruit, "Nothing") != 0 && 
        temp->quantity > 0 && buyers_for_fruit(b, temp) == 1) { // Make sure to avoid nothing and electricity
        cheapest = temp->price;
        strcpy(fruit, temp->fruit);
        temp = temp->east;
    } else {
        temp = temp->east;
    }

    while (save->name != temp->name) {
        if (temp->price < cheapest && temp->price < 0 && strcmp(temp->fruit,
            "Electricity") != 0 && strcmp(temp->fruit, "Nothing") != 0 &&
            temp->quantity > 0 && buyers_for_fruit(b, temp) == 1) {
            cheapest = temp->price;
            strcpy(fruit, temp->fruit);
            temp = temp->east;
        } else {
            temp = temp->east;
        }
    }

    cheapest = -100;
    temp = save;

    // If a profitable fruit wasnt found to be more expensive than $20 
    // Then find the next profitable fruit
    if (strcmp(fruit, "a") == 0) {
        if (temp->price > cheapest && temp->price < 0 && strcmp(temp->fruit,
        "Electricity") != 0 && strcmp(temp->fruit, "Nothing") != 0 && 
        temp->quantity > 0 && buyers_for_fruit(b, temp) == 1) {
        cheapest = temp->price;
        strcpy(fruit, temp->fruit);
        temp = temp->east;
        } else {
            temp = temp->east;
        }

        while (save->name != temp->name) {
            if (temp->price > cheapest && temp->price < 0 && strcmp(temp->fruit,
                "Electricity") != 0 && strcmp(temp->fruit, "Nothing") != 0 &&
                temp->quantity > 0 && buyers_for_fruit(b, temp) == 1) {
                cheapest = temp->price;
                strcpy(fruit, temp->fruit);
                temp = temp->east;
            } else {
                temp = temp->east;
            }
        }
    }

    return *fruit;
}

// Function of the name of the locatino to buy fruit
char fruit_location_buy (struct bot *b, char location[]){
    int     cheapest = -20;
    struct  location *temp = b->location;
    struct  location *save = b->location;

    // Same idea as fruit_to_buy except returns the location of that fruit
    if (temp->price < cheapest && temp->price < 0 && strcmp(temp->fruit,
        "Electricity") != 0 && strcmp(temp->fruit, "Nothing") != 0 && 
        temp->quantity > 0 && buyers_for_fruit(b, temp) == 1) {
        cheapest = temp->price;
        strcpy(location, temp->name);
        temp = temp->east;
    } else {
        temp = temp->east;
    }

    while (save->name != temp->name) {
        if (temp->price < cheapest && temp->price < 0 && strcmp(temp->fruit,
            "Electricity") != 0 && strcmp(temp->fruit, "Nothing") != 0 &&
            temp->quantity > 0 && buyers_for_fruit(b, temp) == 1) {
            cheapest = temp->price;
            strcpy(location, temp->name);
            temp = temp->east;
        } else {
            temp = temp->east;
        }
    }
    // If no fruit was found more expensive than $20 then lower standards to
    // other fruits
    if (cheapest == -20) {
        cheapest = -100;
        // Lowers standards to any fruit price rather than larger than $20
        if (temp->price > cheapest && temp->price < 0 && strcmp(temp->fruit,
        "Electricity") != 0 && strcmp(temp->fruit, "Nothing") != 0 && 
        temp->quantity > 0 && buyers_for_fruit(b, temp) == 1) {
        cheapest = temp->price;
        strcpy(location, temp->name);
        temp = temp->east;
        } else {
            temp = temp->east;
        }

        while (save->name != temp->name) {
            if (temp->price > cheapest && temp->price < 0 && strcmp(temp->fruit,
                "Electricity") != 0 && strcmp(temp->fruit, "Nothing") != 0 &&
                temp->quantity > 0 && buyers_for_fruit(b, temp) == 1) {
                cheapest = temp->price;
                strcpy(location, temp->name);
                temp = temp->east;
            } else {
                temp = temp->east;
            }
        }
    }

    return *location;
}

// Function to find what the profitable fruits price was
int fruit_to_buy_price (struct bot *b, char fruit[]) {
    int     cheapest = -20;
    struct  location *temp = b->location;
    struct  location *save = b->location;

    // Makes sure the price and the fruit is the same when searcing for the price
    if (temp->price < cheapest && temp->price < 0 && strcmp(temp->fruit,
        "Electricity") != 0 && strcmp(temp->fruit, "Nothing") != 0 && temp->
        quantity > 0 && strcmp(fruit, temp->fruit) == 0) { // Should return the price of the fruit found in fruit_to_buy function
        cheapest = temp->price;
        temp = temp->east;
    } else {
        temp = temp->east;
    }

    // Same as the if and else above, but in a loop
    while (save->name != temp->name) {
        if (temp->price < cheapest && temp->price < 0 && strcmp(temp->fruit,
            "Electricity") != 0 && strcmp(temp->fruit, "Nothing") != 0 &&
            temp->quantity > 0 && strcmp(fruit, temp->fruit) == 0) { // Make sure fruit is not nothing or electricity
            cheapest = temp->price;
            temp = temp->east;
        } else {
            temp = temp->east;
        }
    }

    // If cheapest didnt change, i.e. didnt work for the above loop then lower standards for price
    if (cheapest == -20) {
        cheapest = -100;
        if (temp->price > cheapest && temp->price < 0 && strcmp(temp->fruit,
        "Electricity") != 0 && strcmp(temp->fruit, "Nothing") != 0 && temp->
        quantity > 0 && strcmp(fruit, temp->fruit) == 0) {
        cheapest = temp->price;
        temp = temp->east;
        } else {
            temp = temp->east;
        }

        while (save->name != temp->name) {
            if (temp->price > cheapest && temp->price < 0 && strcmp(temp->fruit,
                "Electricity") != 0 && strcmp(temp->fruit, "Nothing") != 0 &&
                temp->quantity > 0 && strcmp(fruit, temp->fruit) == 0) {
                cheapest = temp->price;
                temp = temp->east;
            } else {
                temp = temp->east;
            }
        }
    }
    // Returns the price of what the fruit i was intending to buy was
    return cheapest;
}

// Function to see if there are buyers for the fruit
int buyers_for_fruit (struct bot *b, struct location *temp){
    int result = FALSE;

    struct location *temporary = temp;
    struct location *temporary2 = temp;
    struct location *save = temp;

    // Checks if there are buyers for the fruit, so i don't make a pointless purchase
    if (strcmp(temp->fruit, temporary->fruit) == 0 && temporary->price > 0 
        && (temporary->quantity >= buy_to_budget(b) || temporary->quantity
        >= b->maximum_fruit_kg - b->fruit_kg || temporary->quantity >= 
        temp->quantity) && temporary->quantity >= temp->quantity)
        {
        result = TRUE;
        return result; // Returns true if there was a buyer
    } else {
        temporary = temporary->east;
    }

    // Checks the rest of the locations if there are buyers
    while (strcmp(temporary->name, save->name) != 0) {
        if (strcmp(temp->fruit, temporary->fruit) == 0 && temporary->price > 0 
            && (temporary->quantity >= buy_to_budget(b) || temporary->quantity
            >= b->maximum_fruit_kg - b->fruit_kg || temporary->quantity >= 
            temp->quantity) && temporary->quantity >= temp->quantity)
            {
            result = TRUE;
            return result;
        } else {
            temporary = temporary->east;
        }
    }

    // Last condition if that locations quantity is less than the buying fruit quantity
    // E.g. Fruit to buy = mangoes 12kg, Potential buyer = mangoes 5kg only
    if (strcmp(temp->fruit, temporary2->fruit) == 0 && temporary2->price > 0 
        && temporary2->quantity < temp->quantity && temporary2->quantity != 0) {
        result = TRUE;
        return result;
    } else {
        temporary2 = temporary2->east;
    }

    // Checks the rest of the locations for potential buyers for the last condition
    while (strcmp(temporary2->name, save->name) != 0) {
        if (strcmp(temp->fruit, temporary2->fruit) == 0 && temporary2->price > 0 
            && temporary2->quantity < temp->quantity && temporary2->quantity != 0) {
            result = TRUE;
            return result;
        } else {
            temporary2 = temporary2->east;
        }
    }

    return result;
}

// Function to buy stock that equals to the buyers demand
int purchase_enough (struct bot *b) {
    int quantity = BIG_NUMBER;

    struct location *temporary2 = b->location;
    struct location *save = b->location;

    if (strcmp(b->location->fruit, temporary2->fruit) == 0 && temporary2->
        price > 0 && temporary2->quantity < b->location->quantity && temporary2
        ->quantity != 0) { // Searches for buyers for the fruit i am going to buy
        quantity = temporary2->quantity;
        return quantity; // If successful return the amount i should buy
    } else {
        temporary2 = temporary2->east;
    }

    // Same as the if and else above but in a loop to search the remaining locations
    while (strcmp(temporary2->name, save->name) != 0) {
        if (strcmp(b->location->fruit, temporary2->fruit) == 0 && temporary2->
            price > 0 && temporary2->quantity < b->location->quantity && 
            temporary2->quantity != 0) {
            quantity = temporary2->quantity;
            return quantity;
        } else {
            temporary2 = temporary2->east;
        }
    }
    // Returns the quantity to buy in order to sell out the buyer
    return quantity;
}

// Function to determine how much i can buy
int buy_to_budget (struct bot *b) {
    int i = 0;
    struct location *temp = b->location;
    int amount = -1*temp->price; // Equals to 1 of the price e.g. 1 of $15
    int numtobuy = 0;

    while (i != BIG_NUMBER) {
        if (b->cash < amount) {
            break;
        } else {
            amount += -1*temp->price; // Using the example, 2 of $15 = $30
            numtobuy++; // Saves the number of fruit i can buy
            i++;
        }
    }

    return numtobuy;
}

// Function to find the price at which i will sell the fruit
int fruit_to_sell_price (struct bot *b){
    int saleprice = 0;
    struct location *temp = b->location;
    struct location *save = b->location;

     if (strcmp(temp->fruit, b->fruit) == 0 && temp->quantity >= b->fruit_kg
        && temp->price > 0) { // If the fruit is what i have 
        if (temp->price > saleprice) { // If the fruits price is large
            saleprice = temp->price; // Saves the price
            temp = temp->east;
        } else {
            temp = temp->east;
        }
    } else if (strcmp(temp->fruit, b->fruit) == 0 && temp->quantity < 
               b->fruit_kg && temp->quantity != 0 && temp->price > 0) { // Else if the quantity is less than what i am carrying, save it
        if (temp->price > saleprice) { // Saves the best price to sell at
            saleprice = temp->price;
            temp = temp->east;
        } else {
            temp = temp->east;
        }
    } else {
        temp = temp->east;
    }

    // Similar to above but in a loop
    while (save->name != temp->name) {
        if (strcmp(temp->fruit, b->fruit) == 0 && temp->quantity >= b->fruit_kg
            && temp->price > 0) {
            if (temp->price > saleprice) {
                saleprice = temp->price;
                temp = temp->east;
            } else {
                temp = temp->east;
            }
        } else if (strcmp(temp->fruit, b->fruit) == 0 && temp->quantity < 
                   b->fruit_kg && temp->quantity != 0 && temp->price > 0) {
            if (temp->price > saleprice) {
                saleprice = temp->price;
                temp = temp->east;
            } else {
                temp = temp->east;
            }
        } else {
            temp = temp->east;
        }
    }

    return saleprice;
}

// Function to return the name of the location to sell to
char fruit_location_sell (struct bot *b, char location2sell[]) {
    int saleprice = 0;
    struct location *temp = b->location;
    struct location *save = b->location; // To ensure my loop ends when the location names are the same

    // Finds the location to sell the fruit to 
    if (strcmp(temp->fruit, b->fruit) == 0 && temp->quantity >= b->fruit_kg
        && temp->price > 0) {
        if (temp->price > saleprice) { // Saleprice must equal to price of fruit to sell
            saleprice = temp->price;
            strcpy(location2sell, temp->name);
            temp = temp->east;
        } else {
            temp = temp->east;
        }
    } else if (strcmp(temp->fruit, b->fruit) == 0 && temp->quantity < 
               b->fruit_kg && temp->quantity != 0 && temp->price > 0) {
        if (temp->price > saleprice) {
            saleprice = temp->price;
            strcpy(location2sell, temp->name);
            temp = temp->east;
        } else {
            temp = temp->east;
        }
    } else {
        temp = temp->east;
    }

    while (save->name != temp->name) {
        if (strcmp(temp->fruit, b->fruit) == 0 && temp->quantity >= b->fruit_kg
            && temp->price > 0) { // If the location fruit is equal to fruit im carrying
            if (temp->price > saleprice) { // If the price is good then save the location
                saleprice = temp->price;
                strcpy(location2sell, temp->name);
                temp = temp->east;
            } else {
                temp = temp->east;
            }
        } else if (strcmp(temp->fruit, b->fruit) == 0 && temp->quantity < 
                   b->fruit_kg && temp->quantity != 0 && temp->price > 0) { // Else if quantity is less than what i have, becomes a potential seller
            if (temp->price > saleprice) {
                saleprice = temp->price;
                strcpy(location2sell, temp->name);
                temp = temp->east;
            } else {
                temp = temp->east;
            }
        } else {
            temp = temp->east;
        }
    }

    return *location2sell;
}

// Function to move to best spot to sell fruit
int move_to_sell (struct bot *b, int price, char location2sell[]){
    int move = 0;
    int moveeast = 0;
    int movewest = 0;
    struct location *east = b->location;
    struct location *west = b->location;

    while (strcmp(east->name, location2sell) != 0) { // Checks how many moves eastway
        //printf("EAST NAME IS %s\n", east->name);
        east = east->east;
        moveeast++;
    }

    while (strcmp(west->name, location2sell) != 0) { // Checks how many moves westway
        //printf("wEST NAME IS %s\n", west->name);
        west = west->west;
        movewest++;
    }

    if (movewest < moveeast) { // Checks which move is the fastest
        move = -1*movewest;
    } else {
        move = moveeast;
    }

    return move;
}

// Function to find the nearest electricity supplier
int nearest_electricity(struct bot *b) {
    int east = 0;
    int west = 0;
    int move = 0;

    struct location *temp1 = b->location;
    struct location *temp2 = b->location;
    struct location *save1 = b->location;
    struct location *save2 = b->location;

    if (strcmp(temp1->fruit, "Electricity") == 0 && temp1->quantity >= 1) { // If i'm already at an electricity supplier return 0
        return move;
    } else {
        temp1 = temp1->east;
        east++;
    }

    while (strcmp(temp1->name, save1->name) != 0) { // Checks East for electricity
        if (strcmp(temp1->fruit, "Electricity") == 0 && temp1->quantity >= 1) {
            break;
        } else {
            temp1 = temp1->east;
            east++;
        }
    }  

    // Checks west direction for elec suppliers
    if (strcmp(temp2->fruit, "Electricity") == 0 && temp2->quantity >= 1) { // If i'm already at an electricity supplier return 0
        return move;
    } else {
        temp2 = temp2->west;
        west++;
    }

    while (strcmp(save2->name, temp2->name) != 0) { // Checks west for electricity
        if (strcmp(temp2->fruit, "Electricity") == 0 && temp2->quantity >= 1) {
            break;
        } else {
            temp2 = temp2->west;
            west++;
        }
    }  

    if (west < east) { // Determines if east or west is the fastest route
        move = -1*west;
    } else {
        move = east;
    }

    return move;
}

// Function to check if the eletrcitiy areas have electricity to sell
int check_electricity   (struct bot *b) {
    int result = FALSE;

    struct location *temp = b->location;
    struct location *save = b->location;

    if (strcmp(temp->fruit, "Electricity") == 0 && temp->quantity >= 1) { // If electricity exists then return true
        result = TRUE;
        return result;
    } else {
        temp = temp->east;
    }

    while (strcmp(save->name, temp->name) != 0) { // If electricity exists in the world returns TRUE
        if (strcmp(temp->fruit, "Electricity") == 0 && temp->quantity >= 1) {
            result = TRUE;
            break;
        } else {
            temp = temp->east;
        }
    }  

    return result;
}

// Conditions needed to buy or move to buy
int move_and_buy_conditions (struct bot *b, int price) {
    int result = FALSE;

    // If i'm not carrying the max fruit kg, i can afford at least 1 quantity
    // of the fruit, if my battery is larger than sqrt of capacity + 4, 
    // and if turns is larger than 3 than return true to buy and move fruit
    if (b->fruit_kg != b->maximum_fruit_kg && (b->cash >= -1*(b->
       location->quantity*b->location->price) || b->cash >= -1*
       (b->maximum_fruit_kg - b->fruit_kg)*b->location->price ||
       b->cash < -1*(b->maximum_fruit_kg - b->fruit_kg)*b->location
       ->price) && b->cash >= -1*price && b->turns_left > 3 && 
       b->battery_level > sqrt(b->battery_capacity)+4) {
        result = TRUE;
    }

    return result;
}
