#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define SAMPLE "sample.txt"
#define INPUT "input.txt"
#define MAX_SIZE_LINE 32
#define MAX_SIZE_INPUT 500

char *puzzle_input[MAX_SIZE_INPUT];
size_t size_input;

void dump()
{
    for (size_t i = 0; i < size_input; ++i) {
        printf("%lu: %s", i, puzzle_input[i]);
    }
}

int readInput(char *input)
{
    FILE *fp = fopen(input, "rb");
    if (fp == NULL) {
        fprintf(stderr, "File not found: %s\n", input);
        return (1);
    }

    char line[MAX_SIZE_LINE];
    size_input = 0;
    while (fgets(line, MAX_SIZE_LINE, fp)) {
        puzzle_input[size_input] = malloc(sizeof(char) * MAX_SIZE_LINE);
        memcpy(puzzle_input[size_input++], line, MAX_SIZE_LINE);
    }

    fclose(fp);
    return (0);
}

size_t partOne(char *input)
{
    readInput(input);
    dump();
    return (0);
}

int main(int argc, char *argv[])
{
    (void) argc;
    (void) argv[0];

    printf("Solution for the example part One of Day 5: %lu", partOne(INPUT));

    return (0);
}