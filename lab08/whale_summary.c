// David Nguyen z5166106
// Starting code for COMP1511 lab exercises
// 30/4/18

#include <stdio.h>
#include <string.h>

#define MAX_SPECIES_NAME_LENGTH  128
#define MAX_SIGHTINGS           10000
#define MAX_WHALE_SPECIES         256

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
    struct date when;
    int         how_many;
    char        species[MAX_SPECIES_NAME_LENGTH];
};


int read_sightings_file(char filename[], int len, struct pod sightings[len]);
int read_sighting(FILE *f, struct pod *w);
int read_date(FILE *f, struct date *d);

void whale_summary(int n_sightings, struct pod sightings[n_sightings]);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file> <species>\n", argv[0]);
        return 1;
    }

    struct pod whale_sightings[MAX_SIGHTINGS];
    int n_sightings = read_sightings_file(argv[1], MAX_SIGHTINGS, whale_sightings);

    if (n_sightings < 1) {
        return 1;
    }

    whale_summary(n_sightings, whale_sightings);

    return 0;
}

// number of pods of the specified species assigned to *n_pods
// total number of whales of the specified species assigned to *n_whales

struct tally {
    int  pods;
    int  whales;
    char species[MAX_SPECIES_NAME_LENGTH];
};

//
// print a summary of all whale sightings
//

void whale_summary(int n_sightings, struct pod sightings[n_sightings]) {

    struct tally tallyho[MAX_SIGHTINGS] = {0};

    int count = 0;
    int whalepop = 0;
    int i     = 0;
    int counter[1000] = {0};
    
    // Creates the summary
    while (i < MAX_WHALE_SPECIES){
        int j = 0;
        count = 0;
        tallyho[i].pods = count;
        while (j < n_sightings){
            if (strcmp(sightings[i].species, sightings[j].species) == 0){
                tallyho[i].pods++;
                tallyho[i].whales = tallyho[i].whales + sightings[j].how_many;
                strcpy(tallyho[i].species, sightings[j].species);
                j++;
            } else {
                j++;
            }
        }
        i++;
    }

    // Prints the summary
    i = 0;

    while (i < MAX_WHALE_SPECIES){
        int j = 0;
        while (j < n_sightings){
            if (strcmp(sightings[i].species, sightings[j].species) == 0){
                if (counter[j] == 0){
                    printf("%d %s pods containing %d whales\n", tallyho[i].pods, tallyho[i].species
                  , tallyho[i].whales);
                    counter[j]++;
                    i++;
                    break;
                } else {
                    i++;
                    break;
                }
            } else {
                j++;
            }
        }
    }

}


//
// DO NOT CHANGE THE FUNCTION BELOW HERE
//

// return number of sightings read from filename
// -1 is returned if there is an error

int read_sightings_file(char filename[], int len, struct pod sightings[len]) {
    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        fprintf(stderr,"error: file '%s' can not open\n", filename);
        return -1;
    }

    int n_sightings = 0;
    while (read_sighting(f, &sightings[n_sightings]) == 1 && n_sightings < len) {
        n_sightings = n_sightings + 1;
    }

    fclose(f);
    return n_sightings;
}


// return 1 if a sighting can be read, 0 otherwise

int read_sighting(FILE *f, struct pod *s) {
    if (read_date(f, &(s->when)) != 1) {
        return 0;
    }
    if (fscanf(f, "%d", &(s->how_many)) != 1) {
        return 0;
    }
    fgetc(f);
    if (fgets(s->species, MAX_SPECIES_NAME_LENGTH, f) == NULL) {
        return 0;
    }
    char *newline_ptr = strchr(s->species, '\n');
    if (newline_ptr != NULL) {
        *newline_ptr = '\0';
    }
    return 1;
}


// return 1 if a date can be read, 0 otherwise

int read_date(FILE *f, struct date *d) {
    int n_scanned = fscanf(f, "%d/%d/%d", &(d->year), &(d->month), &(d->day));
    return n_scanned == 3;
}