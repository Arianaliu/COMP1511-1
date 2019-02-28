#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_SPECIES_NAME_LENGTH 4096

// a struct to represent the date
// a whale pod sighting was made

struct date {
    int year;
    int month;
    int day;
};

// a struct to represent a sighting
// of a pod (group) of whales

struct pod {
    struct pod  *next;
    struct date *when;
    int         how_many;
    char        *species;
};


struct pod *read_sightings_file(char filename[]);
struct pod *read_sighting(FILE *f);
struct date *read_date(FILE *f);
struct date *string_to_date(char *s);

void between_days_whales(struct pod *first_pod, struct date *start_day, struct date *finish_day);

// PUT YOUR FUNCTION DEFINITONS HERE
int same_year (struct pod *first_pod, struct date *start_day, struct date *finish_day);
int diff_year (struct pod *first_pod, struct date *start_day, struct date *finish_day);
int checker (struct pod *first_pod, struct date *start_day, struct date *finish_day);
void print_outcome (struct pod *first_pod);

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <file> <start-day> <finish-day>\n", argv[0]);
        return 1;
    }

    struct pod *first_pod = read_sightings_file(argv[1]);
    struct date *start_day = string_to_date(argv[2]);
    struct date *finish_day = string_to_date(argv[3]);

    between_days_whales(first_pod, start_day, finish_day);

    return 0;
}


// Print the whale sightings between start_day and finish_day inclusive.
// One line containing number of whales and species is printed for each sighting.

void between_days_whales(struct pod *first_pod, struct date *start_day, struct 
                        date *finish_day) {

  int sightings = 0;

    while (first_pod != NULL){
        if (start_day -> year == finish_day -> year){
            if (same_year(first_pod, start_day, finish_day) == 1){
                print_outcome(first_pod);
            }
            first_pod = first_pod -> next;
        } else if (start_day -> year != finish_day -> year) {
            if (diff_year(first_pod, start_day, finish_day) == 1) {
                print_outcome(first_pod);
            }
            first_pod = first_pod -> next;
        } else {
            first_pod = first_pod -> next;
        }
    }
}

// PUT YOUR FUNCTIONS HERE

int same_year (struct pod *first_pod, struct date *start_day, struct date 
                *finish_day){
    int result = 0;

    if (first_pod->when->year >= start_day->year && first_pod->when->year
        <= finish_day->year){ // If it's within the year
        if ( (first_pod->when->month >= start_day->month && first_pod->when
            ->month <= finish_day->month)) { // If it's within the month
            if (first_pod->when->month == start_day->month){ // If it's in the first month
                if (start_day->month == finish_day->month){
                    if (first_pod->when->day >= start_day->day && first_pod->when
                        ->day <= finish_day->day){
                        result = 1;
                    }
                } else if (first_pod->when->day >= start_day->day ){ // Must be larger than or equal to that day
                    result = 1;
                }
            } else if (first_pod->when->month == finish_day->month) {
                if (first_pod->when->day <= finish_day->day){ // Must be smaller than or equal to that day
                    result = 1;
                } 
            } else {
                result = 1;
            }
        }
    }

    return result;
}

int diff_year (struct pod *first_pod, struct date *start_day, struct date *finish_day){
     int result = 0;

    if (first_pod->when->year >= start_day->year && first_pod->when->year
        <= finish_day->year){ // If it's within the year
        if (checker(first_pod, start_day, finish_day)) { // If it's within the month
            if (first_pod->when->month == start_day->month){ // If it's in the first month
                if (start_day->month == finish_day->month){
                    if (first_pod->when->day >= start_day->day && first_pod->when
                        ->day <= finish_day->day){
                        result = 1;
                    }
                } else if (first_pod->when->day >= start_day->day ){ // Must be larger than or equal to that day
                    result = 1;
                }
            } else if (first_pod->when->month == finish_day->month) {
                if (first_pod->when->day <= finish_day->day){ // Must be smaller than or equal to that day
                    result = 1;
                } 
            } else {
                result = 1;
            }
        }
    }

    return result;
}

int checker (struct pod *first_pod, struct date *start_day, struct date *finish_day){
    int result = 0;

    if ((first_pod->when->month >= start_day->month && first_pod->when
        ->month <= finish_day->month) || ((first_pod->when->year >=
        start_day->year) && ((first_pod->when->month <= finish_day->month) ||
        first_pod->when->month >= start_day->month) )){
        result = 1;
    }

    return result;
}

void print_outcome (struct pod *first_pod){
    printf("%02d/%02d/%02d %2d %s\n", first_pod->when->day, first_pod->
            when->month, first_pod->when->year, first_pod->how_many, 
            first_pod->species);
}
//
// DO NOT CHANGE THE FUNCTIONS BELOW HERE
//

// return linked list of sightings read from filename
// exit called if there is an error

struct pod *read_sightings_file(char filename[]) {
    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        fprintf(stderr,"error: file '%s' can not open\n", filename);
        exit(1);
    }

    struct pod *first_sighting = NULL;
    struct pod *last_sighting = NULL;

    struct pod *sighting = read_sighting(f);
    while (sighting != NULL) {
        if (first_sighting == NULL) {
            first_sighting = sighting;
            first_sighting->next = NULL;
        } else {
            last_sighting->next = sighting;
        }
        last_sighting = sighting;
        sighting = read_sighting(f);
    }

    return first_sighting;
}


// read a whale sighting (date, number of whales, whale species)
// return a pointer to a malloced struct containing thes edetails
// return NULL if a sighting can not be read

struct pod *read_sighting(FILE *f) {
    struct pod *p = malloc(sizeof (struct pod));
    if (p == NULL) {
        fprintf(stderr, "out of memory\n");
        exit(1);
    }

    p->next = NULL;

    p->when = read_date(f);
    if (p->when == NULL) {
        free(p);
        return NULL;
    }

    int n_scanned = fscanf(f, "%d", &(p->how_many));
    if (n_scanned != 1) {
        free(p);
        return NULL;
    }

    fgetc(f);
    char species_buffer[MAX_SPECIES_NAME_LENGTH];
    if (fgets(species_buffer, MAX_SPECIES_NAME_LENGTH, f) == NULL) {
        free(p);
        return NULL;
    }
   // finish string at '\n' if there is one
    char *newline_ptr = strchr(species_buffer, '\n');
    if (newline_ptr != NULL) {
        *newline_ptr = '\0';
    }

    // also finish string at '\r' if there is one - files from Windows  will
    newline_ptr = strchr(species_buffer, '\r');
    if (newline_ptr != NULL) {
        *newline_ptr = '\0';
    }

    // malloc a chararray long enough to hold species name
    // and copy species to it
    p->species = malloc(strlen(species_buffer) + 1);
    if (p->species == NULL) {
        fprintf(stderr, "out of memory\n");
        exit(1);
    }
    strcpy(p->species, species_buffer);

    return p;
}


// read a date in day/month/year format from stream f
// return a pointer to a malloced date struct containing them
//  return NULL if a date can not be read

struct date *read_date(FILE *f) {
    struct date *d = malloc(sizeof (struct date));
    if (d == NULL) {
        fprintf(stderr, "out of memory\n");
        exit(1);
    }
    int n_scanned = fscanf(f, "%d/%d/%d", &(d->day), &(d->month), &(d->year));
    if (n_scanned != 3) {
        free(d);
        return NULL;
    }
    return d;
}


// given a string containing a date in day/month/year format
// return a pointer to a malloced date struct containing them
// return NULL if a date can not be read

struct date *string_to_date(char *s) {
    struct date *d = malloc(sizeof (struct date));
    if (d == NULL) {
        fprintf(stderr, "out of memory\n");
        exit(1);
    }
    int n_scanned = sscanf(s, "%d/%d/%d", &(d->day), &(d->month), &(d->year));
    if (n_scanned != 3) {
        free(d);
        return NULL;
    }
    return d;
}