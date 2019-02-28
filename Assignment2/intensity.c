// intensity.c
// Assignment 2, COMP1511 18s1: Intensity
//
// Hoai Bao David Nguyen (z5166106)
//
// Version 1.0.1: Minor changes to wording of comments.
// Version 1.0.0: Assignment released.

#include <stdio.h>
#include <assert.h>

// SOME USEFUL #defines - YOU WILL NEED MORE

#define ACTION_PLAYER_NAME    0
#define ACTION_DISCARD        1
#define ACTION_PLAY_CARD      2
#define ACTION_UNIT_TESTS     3

#define N_CARDS              40
#define N_CARDS_INITIAL_HAND 10
#define N_PLAYERS             4
#define N_CARDS_DISCARDED     3

#define CARD_MIN             10
#define CARD_MAX             49


// ADD EXTRA #defines HERE

#define MAX_DISCARD           3
#define MAX_PREVIOUS_PLAYED   4 
#define MAX_CARD_POOL         40
#define LAST_CARD             0

#define TRUE                  1
#define FALSE                 0

void print_player_name(void);
void choose_discards(void);
void choose_card_to_play(void);
void run_unit_tests(void);

// ADD PROTOTYPES FOR YOUR FUNCTIONS HERE

int buffalo_hunter       (int hand[], int cardhand);
int check_high_discards  (int startinghand[N_CARDS_INITIAL_HAND], int j);
int check_low_discards   (int startinghand[N_CARDS_INITIAL_HAND], int k);
int check_calf_buffalo   (int hand[], int cardhand);
int check_calf_all_rounds(int previous[], int cardhand, int hand[]);
int check_calf_in_hand   (int hand[], int cardhand);
int play_card_not_first (int cardhand, int hand[], int cardplayed, int 
                          played[]);
int play_card_first     (int cardhand, int hand[], int previous[]);
void print_discards      (int discards[]);

// UNIT TEST FUNCTIONS

int check_duplicates     (int testarray1[], int size);
int check_I_cards        (int testarray1[], int size);
int check_discards       (int testarray1[], int size);

// You should not need to change this main function

int main(void) {

    int which_action = 0;
    scanf("%d", &which_action);
    if (which_action == ACTION_PLAYER_NAME) {
        print_player_name();
    } else if (which_action == ACTION_DISCARD) {
        choose_discards();
    } else if (which_action == ACTION_PLAY_CARD) {
        choose_card_to_play();
    } else {
        run_unit_tests();
    }

    return 0;
}

void print_player_name(void) {
    printf("Shreko\n");
}

void choose_discards() {
    int i = 0;
    int j = 0;
    int k = 0;
    int startinghand[N_CARDS_INITIAL_HAND] = {0};
    int discards[3] = {0};

    // Reads the starting hand and puts it into an array
    while (i != N_CARDS_INITIAL_HAND){ 
        scanf("%d", &startinghand[i]);
        assert(startinghand[i] >= 10 && startinghand[i] <= 49); // Make sure the cards exist
        i++;
    }

    i = 0;

    // Selects which cards to discard, prioritises high value cards

    while (i != MAX_DISCARD) {

        while (j != N_CARDS_INITIAL_HAND){
            if (check_high_discards (startinghand, j) == 1) { // If there is a high card, then discard it
                discards[i] = startinghand[j]; // Saves that high card in the discard array
                i++;
                j++;
                if (i == MAX_DISCARD) { // Breaks the loop when enough discards are found
                    break;
                }
            } else {
                j++;
            }
        }

        if (i == MAX_DISCARD) { // Breaks the loop if there are enough discards (Occurs when there are < 3 high discards from first loop)
            break;
        }

        while (k != N_CARDS_INITIAL_HAND) {
            if (check_low_discards (startinghand, k) == 1) { // Selects preferred low discards to discard
                discards[i] = startinghand[k];
                i++;
                k++;
                if (i == MAX_DISCARD) {
                    break;
                }
            } else {
                k++;
            }
        }
    }

    // Prints the discarded cards
    print_discards (discards);
    assert(check_discards(discards, MAX_DISCARD) == TRUE);

}

void choose_card_to_play(void) {
    int hand[N_CARDS_INITIAL_HAND]    = {0};
    int played[MAX_PREVIOUS_PLAYED]   = {0};
    int previous[MAX_CARD_POOL]       = {0};
    int discard[MAX_DISCARD]          = {0};
    int receivediscard[MAX_DISCARD]  = {0};

    int cardhand      = 0;
    int cardplayed    = 0;
    int tableposition = 0;

    int i     = 0;
    int j     = 0;

    // How many cards are in my hand
    // How many cards played already and table position
    scanf("%d", &cardhand);
    scanf("%d", &cardplayed);
    scanf("%d", &tableposition);

    // CODE TO READ THE CARDS OF YOUR HAND INTO AN ARRAY USING SCANF
    
    while (i != cardhand) {
        scanf("%d", &hand[i]); // Scans the value of those cards into an array
        i++;
    }

    // CODE TO READ THE CARDS PLAYED THIS ROUND INTO AN ARRAY USING SCANF
    i = 0;
    if (cardplayed >= 1) {
        while (i != cardplayed) { // While it does not equal to the cards in play
            scanf("%d", &played[i]); // Saves the value of those cards to an array
            i++;
        }
    }   

    // CODE TO READ THE CARDS PREVIOUSLY PLAYED LAST ROUND INTO AN ARRAY USING SCANF
    i = 0;

    if (cardhand != CARD_MIN) { 
        while (i != 4 * (N_CARDS_INITIAL_HAND - cardhand)) { // Scans how many previous cards so far
            scanf("%d", &previous[i]); // Scans what the values of these previous cards are
            i++;
        }
    } 

    // CODE TO SCAN DISCARDS AND SCAN RECEIVED FROM DISCARDS

    i = 0;

    while (i != MAX_DISCARD) { // Scans discards
        scanf("%d", &discard[i]);
        i++;
    }

    i = 0;

    while (i != MAX_DISCARD) { // Scans received discards
        scanf("%d", &receivediscard[i]);
        i++;
    }

    // CODE TO CHOOSE AND PRINT THE CARD I WISH TO PLAY
    while (j != cardhand) {
        if (cardplayed == 0) {
            // Selects the first card to play in the round
            printf("%d\n", hand[play_card_first (cardhand, hand, previous)]);
            break;
        } else {
            // Selects card to play if it's not the first round
            printf("%d\n", hand[play_card_not_first 
                            (cardhand, hand, cardplayed, played)]);
            break; 
        }
    }

}

// My strategy is to maintain low card values in my hand in order to avoid 
// winning. This prevents me from receiving penalty points. 
// I achieve this by checking through all the cards in my hand, and then using
// a strategy to select what to play. (Passive Strategy)

void run_unit_tests(void) {
    int size = 0;

    // 2. Checks if there are any duplicate cards in play (FALSE)
    int testarray1[N_CARDS_INITIAL_HAND] = {10, 19, 11, 12, 13, 14, 15, 16, 17,
                                            18};
    assert(check_duplicates(testarray1, N_CARDS_INITIAL_HAND) == FALSE);
    // 3. Checks if there are any duplicate cards in play (TRUE)
    int testarray2[N_CARDS_INITIAL_HAND] = {10, 10, 11, 11, 12, 14, 15, 16, 17,
                                            18};
    assert(check_duplicates(testarray2, N_CARDS_INITIAL_HAND) == TRUE);
    // 4. Checks if there are 3 duplicates in hand (TRUE)
    int testarray3[N_CARDS_INITIAL_HAND] = {10, 10, 11, 11, 12, 14, 15, 16, 17,
                                            10};
    assert(check_duplicates(testarray3, N_CARDS_INITIAL_HAND) == TRUE);           
    // 5. Checks if there any duplicate high cards in hand (FALSE)
    int testarray4[N_CARDS_INITIAL_HAND] = {31, 33, 36, 41, 42, 44, 45, 46, 47,
                                            49};
    assert(check_duplicates(testarray4, N_CARDS_INITIAL_HAND) == FALSE);
    // 6. Checks if there are any duplicates in the deck (FALSE)
    int testarray5[N_CARDS] = {10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21,
                               22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 33, 34,
                               35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46,
                               47, 48, 49};
    assert(check_duplicates(testarray5, N_CARDS) == FALSE);
    // 7. Checks if there are cards higher than 49 in play (TRUE)
    int testarray10[N_CARDS] = {10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21,
                               22, 23, 55, 78, 26, 27, 28, 29, 30, 31, 33, 34,
                               35, 36, 37, 38, 39, 40, 102, 41, 43, 44, 45, 46,
                               47, 48, 49};
    assert(check_I_cards(testarray10, N_CARDS) == TRUE);
    // 8. Checks if there are cards lower than 10 in play (TRUE)
    int testarray11[N_CARDS] = {10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21,
                               22, 23, -1, 4, 26, 27, 28, 29, 30, 31, 33, 34,
                               35, 36, 37, 38, 39, 40, 2, 41, 43, 44, 9, 46,
                               47, 48, 49};
    assert(check_I_cards(testarray11, N_CARDS) == TRUE);
    // 9. Checks if only 3 cards are discarded during discard round (TRUE)
    int testarray13[MAX_DISCARD] = {10, 11, 12};
    assert(check_discards(testarray13, MAX_DISCARD) == TRUE);
    // 10. If there are more than 3 cards discarded 
    int testarray14[MAX_DISCARD+2] = {10, 11, 12, 13, 14};
    assert(check_discards(testarray14, MAX_DISCARD+2) == FALSE);
    // 11. If there are less than 3 cards discarded
    int testarray15[MAX_DISCARD-1] = {10, 11};
    assert(check_discards(testarray15, MAX_DISCARD-1) == FALSE);
    // 12. Checks if high_discard selecter function works 
    int testarray17[N_CARDS_INITIAL_HAND] = {10, 19, 11, 12, 13, 14, 15, 16, 17,
                                            18};
    assert(check_high_discards(testarray17, 1) == TRUE);
    // 13. Checks if high_discard function doesnt select low cards
    int testarray18[N_CARDS_INITIAL_HAND] = {10, 19, 11, 12, 13, 14, 15, 16, 17,
                                            18};
    assert(check_high_discards(testarray17, 0) == FALSE);
    // 14. Checks if low discard function selects lower cards
    int testarray19[N_CARDS_INITIAL_HAND] = {10, 19, 11, 12, 13, 14, 15, 16, 17,
                                            18};
    assert(check_low_discards(testarray19, 6) == TRUE);
    // 15. Checks if low discard function doesnt select high cards
    int testarray20[N_CARDS_INITIAL_HAND] = {10, 19, 11, 12, 13, 14, 15, 16, 17,
                                            18};
    assert(check_low_discards(testarray20, 1) == FALSE);
    // 16. Checks calf all rounds function
    int testarray21[N_CARDS_INITIAL_HAND] = {10, 11, 12, 13, 14, 15, 16, 35,
                                            32};
    int testprevious1[4] = {21, 22, 23, 24};
    assert(check_calf_all_rounds(testprevious1, 9, testarray21) == 0);  
    // 17. Checks calf in hand function
    int testarray22[3] = {10, 11, 31};      
    assert(check_calf_in_hand (testarray22, 3) == TRUE);        
    // 18. Checks if there is no calf in (calf in hand function)
    int testarray23[3] = {10, 11, 12};
    assert(check_calf_in_hand (testarray23, 3) == FALSE);  
    // 19. Checks the play card not first function
    int testarray24[3] = {10, 11, 24};
    int testcardplayed1[1] = {21};
    assert(play_card_not_first(3, testarray24, 1, testcardplayed1) == 2);
    // 20. Checks the play card not first function (if i dont have a legal card)
    int testarray25[3] = {20, 35, 37};
    int testcardplayed2[1] = {11};
    assert(play_card_not_first(3, testarray25, 1, testcardplayed2) == 0);
    // 21. Tests if i play the last card for play card not first function
    int testarray26[1] = {15};
    int testcardplayed3[3] = {20, 23, 35};
    assert(play_card_not_first(1, testarray26, 3, testcardplayed3) == 0);
    // 22. Tests if i play the buffalo if the conditions for it exist
    int testarray27[3] = {17, 23, 47};
    int testcardplayed4[3] = {49, 42, 44};
    assert(play_card_not_first(3, testarray27, 3, testcardplayed4) == 2);
    // 23. Tests the play first function (Plays the last card in hand)
    int testarray28[1] = {15};
    int testprevious2[36] = {0};
    assert(play_card_first(1, testarray28, testprevious2) == 0);
    // 24. Plays a low calf if a calf is legal
    int testarray29[9] = {11, 14, 16, 17, 18, 19, 31, 39, 40};
    int testprevious3[4] = {10, 22, 33, 45};
    assert(play_card_first(9, testarray29, testprevious3) == 6);
    // 25. Plays a legal card in hand otherwise
    int testarray30[9] = {11, 14, 16, 17, 18, 19, 31, 39, 40};
    int testprevious4[4] = {10, 22, 23, 24};
    assert(play_card_first(9, testarray30, testprevious4) == 0);
    // 26. Plays a legal card with no calfs in hand
    int testarray31[9] = {11, 14, 16, 17, 18, 19, 21, 22, 40};
    int testprevious5[4] = {10, 24, 25, 26};
    assert(play_card_first(9, testarray31, testprevious5) == 0);
    // 27. Tests buffalo hunter function (Buffalo existo)
    int testarray32[9] = {11, 14, 16, 17, 18, 19, 21, 22, 47};
    assert(buffalo_hunter(testarray32, 9) == 8);
    // 28. Buffalo does not exist in buffalo hunter
    int testarray33[9] = {11, 14, 16, 17, 18, 19, 21, 22, 42};
    assert(buffalo_hunter(testarray33, 9) == 0);
    // 1. 

}   

// UNIT TEST FUNCTIONS

// Checks if there are any duplicates in the card pile
int check_duplicates (int testarray1[], int size) {
    int result = FALSE; // 0 Means no duplicates, 1 means duplicates
    int i      = 0;

    while (i != size) {
        int j = 0;
        while (j != size) {
            if (testarray1[i] == testarray1[j] && i != j) { // Checks for duplicates whilst i cannot be j
                result = TRUE; 
                break;
            } else if (j == size - 1) { // If it equals the last element, then there were no duplicates
                break;
            } else {
                j++;
            }
        }
        if (result == TRUE) { // Breaks the first loop if a duplicate was found
            break;
        }
        i++;
    }

    return result;
}

// Checks if any imaginary cards exist (non existant cards in the game)
int check_I_cards (int testarray1[], int size){
    int result = FALSE;
    int i      = 0;

    while (i != size) {
        if (testarray1[i] > 49 || testarray1[i] < 10) { // Imaginary cards are larger than 49 or less than 10
            result = TRUE;
            break;
        } else {
            i++;
        }
    }

    return result;
}

// Function to check if discards are 3
int check_discards (int testarray1[], int size){
    int result = FALSE;
    int i      = 0;

    while (i != size) { // While it is not equal to the size of the array
        if (testarray1[i] >= 10 && testarray1[i] <= 49) { // If the card exists
            result = TRUE;
            i++;
        } else {
            i++;
        }
    }

    if (i == MAX_DISCARD) { // If it equals to the max number of discards (3) then return true
        result = TRUE;
    } else {
        result = FALSE; // False if it is less than 3 or larger than 3
    }

    return result;
}

//
// END OF UNIT TEST FUNCTIONS
// 

// Checks if i have any high cards to discard
int check_high_discards (int startinghand[N_CARDS_INITIAL_HAND], int j){
    int result = 0;

    // Checks if i have cards from (7 - 9)
    if (startinghand[j]%10 == 9 || startinghand[j]%10 == 8 || 
        startinghand[j]%10 == 7) { // Discards preferred carsd that have 9, 8 or 7 in them
        result = 1;
    }

    return result;
}

// Checks if i have any low cards to discard
int check_low_discards (int startinghand[N_CARDS_INITIAL_HAND], int k){
    int result = 0;

    // Checks if i have cards from (3 - 6)
    if (startinghand[k]%10 == 6 || startinghand[k]%10 == 5 ||
        startinghand[k]%10 == 4 || startinghand[k]%10 == 3) { // Discards preferred carsd that have 3-6 in them
        result = 1;
    }

    return result;
}

// Prints the chosen discarded cards
void print_discards (int discards[]){
    int i = 0;

    while (i != MAX_DISCARD){  // Prints out 3 cards that were discarded
        printf("%d ", discards[i]);
        i++;
    }

    assert(check_discards(discards, MAX_DISCARD) == TRUE); // Asserts that 3 cards were discarded

    puts("\n");
}

// Checks if a calf has been played in previous rounds
int check_calf_all_rounds (int previous[], int cardhand, int hand[]) {
    int result     = 0;
    int lowestcalf = 40;
    int i          = 0;

    // Checks if any calfs were played in the previous round
    while (i != 4 * (N_CARDS_INITIAL_HAND - cardhand)) {
        if ((previous[i]/10)%10 == 3) { // If the first digit is a 3, it's a calf
            result = 1;
            break;
        } else {
            i++;
        }
    }

    int j = 0;

    // To know where the calf is in my hand
    if (result == 1) { // If there was a calf previously played, then looks for where the calf is in my hand
        while (j != cardhand) {
            if ((hand[j]/10)%10 == 3) {
                if (hand[j] < lowestcalf) { // Statement to keep track of the lowest calf value and location
                    lowestcalf = hand[j];
                    result     = j; // Result = to the location of the calf
                } else {
                    j++;
                }
            } else {
                j++;
            }
        }
    }
    // returns the location of the calf element in the array
    return result;
}

// Checks if i have a calf or a buffalo card in my hand
int check_calf_in_hand (int hand[], int cardhand){
    int result = 0;
    int i      = 0;
    int j      = 0;

    assert(check_duplicates(hand, cardhand) == FALSE); // Makes sure there are no duplicates in my hand
    assert(check_I_cards(hand, cardhand) == FALSE); // Makes sure there are no imaginary cards in my hand

    while (i != cardhand) {
        while (j != cardhand){
            if (hand[j]%30 >= 0 && hand[j]%30 <= 9) { // Checks if it's a calf
                result = 1;
                i = cardhand; // To break the initial loop
                break;
            } else {
                j++;
            }
        }

        if (j == cardhand) { // Default condition, meaning there's no calfs or buffalo
            break;
        }
    }

    return result;
}

// To find the location of the buffalo in my hand
int buffalo_hunter (int hand[], int cardhand){
    int j = 0;

    while (j != cardhand) {
        if (hand[j] == 47) { // Finds the buffalo and remembers the position
            break;
        } else {
            j++;
        }
    }

    if (j == cardhand) { // If the buffalo didnt exist in the hand
        j = 0;
    }

    return j;
}

// Plays a card if i'm not first to play a card this round
int play_card_not_first (int cardhand, int hand[], int cardplayed, int 
                          played[]){
    int i = 0;
    int j = 0;
    int k = 0;

    assert(check_duplicates(hand, cardhand) == FALSE); // Makes sure there are no duplicates
    assert(check_I_cards(hand, cardhand) == FALSE); // Makes sure there are no imaginary cards in my hand

    while (i != MAX_PREVIOUS_PLAYED) { // While it does not equal to max cards playable
        if (j == cardhand) {
            i++;
            j = 0;
        } if (cardhand == 1) { // If i only have 1 card then play it (because it's the only thing to do)
            j = LAST_CARD;
            break;
        } else if (i == cardplayed){  // If i = cardplayed then i had no playable cards and must play any card
            j = 0;
            break;
        } else if (played[i] > 47 && buffalo_hunter(hand, cardhand) > 0) { // Strategy: plays buffalo if card larger than buffalo already played
            j = buffalo_hunter(hand, cardhand);
            break;
        } else if ((hand[j]/10)%10 == (played[i]/10)%10 ) { // Else plays a legal card from my hand
            break;
        } else {
            j++;
        } 
    }
    return j;
}

// Plays a card if i'm first in the round
int play_card_first (int cardhand, int hand[], int previous[]){
    int i = 0;
    int j = 0;

    assert(check_duplicates(hand, cardhand) == FALSE); // Makes sure there are no duplicates
    assert(check_I_cards(hand, cardhand) == FALSE); // Makes sure there are no imaginary cards in the deck

    while (j != cardhand) {
        if (check_calf_in_hand (hand, cardhand) == 1) {
            // Check if calf played in any other rounds first
            while (j != cardhand) {
                if (cardhand == 1) { // Last card is the only legally playable move
                    j = LAST_CARD;
                    break;
                } else if (check_calf_all_rounds (previous, cardhand, hand) >=
                           1) { // If there was a calf played last round, play a calf
                    j = check_calf_all_rounds(previous, cardhand, hand);
                    break;
                } else if ((hand[j]/10)%10 != 3) { // If it's not a calf then play it
                    break;
                } else if (j == cardhand-1) { // If it reaches the last element then play that card
                    break;
                } else {
                    j++;
                }
            }
            break;
        } else { // Plays a low card in my hand, otherwise plays a high card 
            if (hand[j]%10 == 0 || hand[j]%10 == 1 || hand[j]%10 == 2 
                || hand[j]%10 == 3 ||hand[j]%10 == 4 || hand[j]%10 == 
                5) { // SPecifications for "low" cards
                break;
            } else if (hand[j]%10 == 6 || hand[j]%10 == 7 || 
                hand[j]%10 == 8 || hand[j]%10 == 9) { // Specifications for "high" cards
                break;
            } else {
                j++;
            }
        }
    }
    return j;
}