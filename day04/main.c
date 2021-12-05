#include <stdlib.h>
#include <stdio.h>

#define SAMPLE_INPUT "sample-01.txt"
#define INPUT_FILE "input.txt"

size_t partOne(char *input) {
    size_t solution = 0;
    FILE *fp = fopen(input, "rb");
    if (fp == NULL)
        return(1);

    char *line = malloc(sizeof(char) * 2048);
    while (fgets(line, 2048, fp)) {
        if (line[0] != '\n') {
            printf("%s", line);
        }
    }

    fclose(fp);
    return(solution);
}

int main(int argc, char *argv[])
{
    (void) argc;
    (void) argv[0];
    printf("Solution for the part One of Day 4 (%s): %lu", SAMPLE_INPUT, partOne(SAMPLE_INPUT));

    return (0);
}