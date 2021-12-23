#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define SAMPLE "sample.txt"
#define INPUT "input.txt"
#define MAX_SIZE_LINE 1024
#define MAX_SIZE_LANTERFISHES 1024 * 1024

size_t days;
size_t *lanterfishes;
size_t size_lanterfishes;

void dump()
{
    for (size_t i = 0; i < size_lanterfishes - 1; ++i) {
        printf("%lu,", lanterfishes[i]);
    }

    printf("%lu", lanterfishes[size_lanterfishes - 1]);
    putchar('\n');
}

void printInitialState()
{
    printf("Initial state: ");
    dump();
}

void printDay(size_t day)
{
    char plural[2] = {' ', 's'};
    printf("After\t %lu day%c:", day, day > 1 ? plural[1] : plural[0]);
    dump();
}

int readInput(char *input)
{
    FILE *fp = fopen(input, "rb");
    if (fp == NULL) {
        fprintf(stderr, "File not found: %s\n", input);
        return (1);
    }

    lanterfishes = malloc(sizeof(size_t) * MAX_SIZE_LANTERFISHES);
    size_lanterfishes = 0;

    char line[MAX_SIZE_LINE];
    while (fgets(line, MAX_SIZE_LINE, fp)) {
        char *chr = line;
        while (*chr != '\n') {
            if (*chr == ',')
                chr++;

            lanterfishes[size_lanterfishes++] = atoll(chr);
            chr++;
        }
    }

    fclose(fp);
    return (0);
}

size_t partOne(char *input)
{
    days = 0;
    size_t newfishes = 0;
    readInput(input);
    printInitialState();

    while (days < 80) {
        days++;

        for (size_t i = 0; i < size_lanterfishes; ++i) {
            if (lanterfishes[i] == 0) {
                newfishes++;
                lanterfishes[i] = 6;
            } else {
                lanterfishes[i]--;
            }
        }

        if (newfishes > 0) {
            for (size_t i = size_lanterfishes; i < (size_lanterfishes + newfishes); ++i) {
                lanterfishes[i] = 8;
            }
            size_lanterfishes += newfishes;
            newfishes = 0;
        }

        // printDay(days);
    }

    return (size_lanterfishes);
}


int main(int argc, char *argv[])
{
    (void) argc;
    (void) argv[0];

    printf("Solution for sample of part One of Day 6: %lu", partOne(SAMPLE));

    return (0);
}