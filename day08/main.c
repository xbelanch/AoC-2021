#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_SIZE_LINE 4096
#define SAMPLE "sample.txt"
#define OUTPUT "ouput.txt"
#define i64 unsigned long long

// Unique
// 1: 2
// 4: 4
// 7: 3
// 8: 7

// Common
// 2: 5
// 3: 5
// 5: 5
// 0: 6
// 6: 6
// 9: 6


i64 partOne(const char *input)
{
    FILE *fp;
    char *s;

    if ((fp = fopen(input, "rb")) == NULL) {
        fprintf(stderr, "File not found: %s\n", input);
        return (1);
    }

    s = malloc(sizeof(char) * MAX_SIZE_LINE);
    char *s0[10];
    char *s1[4];

    for (size_t i = 0; i < 10; ++i) s0[i] = malloc(sizeof(char) * 9);
    for (size_t i = 0; i < 4; ++i) s1[i] = malloc(sizeof(char) * 4);

    i64 count = 0;
    while (fgets(s, MAX_SIZE_LINE, fp) != NULL) {
        sscanf(s, "%s %s %s %s %s %s %s %s %s %s | %s %s %s %s",
               s0[0], s0[1], s0[2], s0[3], s0[4], s0[5], s0[6], s0[7], s0[8], s0[9],
               s1[0], s1[1], s1[2], s1[3]);
        for (size_t i = 0; i < 4; ++i) {
            switch(strlen(s1[i])) {
            case 2: case 4: case 3: case 7:
                count++;
                break;
            }
        }
    }

    fclose(fp);
    return (count);
}

int main(int argc, char *argv[])
{
    (void) argc;
    (void) argv[0];

    printf("Solution for sample of part One of Day 8: %llu", partOne(SAMPLE));

    return (0);
}