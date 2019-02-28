// David Nguyen z5166106
// 19/5/18

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct node {
    struct node *next;
    int          data;
};

int most_frequent(struct node *head);
struct node *strings_to_list(int len, char *strings[]);

// DO NOT CHANGE THIS MAIN FUNCTION

int main(int argc, char *argv[]) {
    // create linked list from command line arguments
    struct node *head = strings_to_list(argc - 1, argv + 1);

    int result = most_frequent(head);
    printf("%d\n", result);

    return 0;
}


// return the value which occurs most frequently in a linked list
// if several values are equally most frequent
// the value that occurs earliest in the list is returned
int most_frequent(struct node *head) {

	int memory1 = 0;
	int memory2 = 0;

	struct node *save = head; // Pointer to the start
	struct node *temp = head;

	while (head != NULL) {
		if (head->next == NULL) {
			break;
		}
		save = head->next;
		int i = head->data;
		int count = 1;
		while (save != NULL) {
			if (save->data == i) {
				count++;
				if (count > memory2) {
					memory1 = i;
					memory2 = count;
				} 
				save = save->next;
			} else {
				save = save->next;
			}
		}
		head = head->next;	
	}

	save = temp;
	int j = temp->data;
	int counter = 1;

	if (memory1 == 0) {
		memory1 = j;
		memory2 = counter;
	}

    // PUT YOUR CODE HERE (change the next line!)
    return memory1;

}


// DO NOT CHANGE THIS FUNCTION

// create linked list from array of strings
struct node *strings_to_list(int len, char *strings[]) {
    struct node *head = NULL;
    for (int i = len - 1; i >= 0; i = i - 1) {
        struct node *n = malloc(sizeof (struct node));
        assert(n != NULL);
        n->next = head;
        n->data = atoi(strings[i]);
        head = n;
    }
    return head;
}