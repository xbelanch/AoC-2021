#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define SAMPLE "sample.txt"
#define INPUT "input.txt"
#define MAX_SIZE_LINE 1024

int readInput(char *input)
{
    FILE *fp = fopen(input, "rb");
    if (fp == NULL) {
        fprintf(stderr, "File not found: %s\n", input);
        return (1);
    }
    char line[MAX_SIZE_LINE];
    while (fgets(line, MAX_SIZE_LINE, fp)) {
        printf("%s", line);
    }

    fclose(fp);
    return (0);
}

size_t partOne(char *input)
{
    size_t solution = 0;
    readInput(input);
    return (solution);
}


int main(int argc, char *argv[])
{
    (void) argc;
    (void) argv[0];

    printf("Solution for sample of part One of Day 6: %lu", partOne(SAMPLE));

    return (0);
}