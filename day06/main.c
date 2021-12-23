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

void printInitialState()
{
    printf("Initial state: ");
    for (size_t i = 0; i < size_lanterfishes - 1; ++i) {
        printf("%lu,", lanterfishes[i]);
    }

    printf("%lu", lanterfishes[size_lanterfishes - 1]);
    putchar('\n');
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
    readInput(input);
    printInitialState();

    return (size_lanterfishes);
}


int main(int argc, char *argv[])
{
    (void) argc;
    (void) argv[0];

    printf("Solution for sample of part One of Day 6: %lu", partOne(SAMPLE));

    return (0);
}