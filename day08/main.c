#include <stdlib.h>
#include <stdio.h>

#define MAX_SIZE_LINE 4096
#define SAMPLE "sample.txt"
#define OUTPUT "ouput.txt"
#define i64 unsigned long long

int readInput(const char *input)
{
    FILE *fp;
    char *s;

    if ((fp = fopen(input, "rb")) == NULL) {
        fprintf(stderr, "File not found: %s\n", input);
        return (1);
    }

    s = malloc(sizeof(char) * MAX_SIZE_LINE);
    while (fgets(s, MAX_SIZE_LINE, fp) != NULL) {
        printf("%s", s);
    }

    fclose(fp);
    return (0);
}

i64 partOne(const char *input)
{
    readInput(input);
    return (0);
}


int main(int argc, char *argv[])
{
    (void) argc;
    (void) argv[0];

    printf("Solution for sample of part One of Day 8: %llu", partOne(SAMPLE));

    return (0);
}