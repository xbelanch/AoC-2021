#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SAMPLE "sample.txt"
#define INPUT "input.txt"
#define MAX_SIZE_LINE 2048
#define i64 unsigned long long

int hp[2048];

void dumpInput()
{
    for (size_t i = 0; i < 2048; ++i) {
        if (hp[i] > 0)
            printf("hp[%lu] = %d\n", i, hp[i]);
    }
}

int readInput(const char *input)
{
    FILE *fp;
    char *s;
    char *start;
    char *end;
    char *num;
    size_t len;
    int idx;

    if ((fp = fopen(input, "rb")) == NULL) {
        fprintf(stderr, "File not found: %s\n", input);
        return (1);
    }

    s = (char*)malloc(sizeof(char) * MAX_SIZE_LINE);
    num = (char*)malloc(sizeof(char) * 4); // max number allowed 9999
    start = s;
    end = start;
    while (fgets(s, MAX_SIZE_LINE, fp) != NULL) {
        while (*end != '\n') {
            if (*end == ',') {
                len = end - start;
                memcpy(num, start, len);
                idx = atoi(num);
                hp[idx]++;
                // printf("%lu\n", idx);
                end++;
                start = end;
                memset(num, 0, 4);
            } else {
                end++;
            }
        }
        // collect last number
        len = end - start;
        memcpy(num, start, len);
        idx = atol(num);
        hp[idx]++;
        // printf("%lu\n", idx);
    }

    fclose(fp);
    return (0);
}

i64 outcome(int fuel)
{
    size_t cost = 0;
    for (int i = 0 ; i < 2048; ++i) {
        if (hp[i] >= 0) {
            cost += abs(i - fuel) * hp[i];
        }
    }
    return (cost);
}

i64 partOne(const char *input)
{
    memset(hp, 0, sizeof hp);
    readInput(input);
    dumpInput();
    return (outcome(2));
}


int main(int argc, char *argv[])
{
    (void) argc;
    (void) argv[0];

    printf("Solution for sample of part One of Day 7: %llu", partOne(SAMPLE));

    return (0);
}