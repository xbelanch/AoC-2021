#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SAMPLE "sample.txt"
#define INPUT "input.txt"
#define MAX_SIZE_LINE 4096
#define i64 unsigned long long

int hp[4096];

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
        if (hp[i] > 0) {
            cost += abs(i - fuel) * hp[i];
        }
    }
    return (cost);
}

i64 outcomeV2(int fuel)
{
    size_t cost = 0;
    for (int i = 0; i < 2048; ++i) {
        if (hp[i] > 0) {
            int start;
            int end;

            if (i > fuel) {
                start = fuel;
                end = i;
            } else {
                start = i;
                end = fuel;
            }
            // printf("start: %d, end: %d", start, end);
            int res = 0;
            for (int k = 1, j = start; j < end ; ++j, ++k) {
                res += k;
            }
            // printf(": %d fuel\n", res);
            cost += res * hp[i];
        }
    }
    return (cost);
}

i64 cheapestFuel()
{
    i64 cheap = 9999999;
    i64 cost;
    for (int i = 0; i < 8192; ++i) {
        cost = outcome(i);
        if (cost < cheap)
            cheap = cost;
    }
    return (cheap);
}

i64 cheapestFuelV2()
{
    // TODO: Need to fix this limit value
    // Sure there's a better way to do that
    // Brute force approach at this moment
    i64 cheap = 999999999999;
    i64 cost;
    for (int i = 0; i < 512; ++i) {
        cost = outcomeV2(i);
        if (cost < cheap)
            cheap = cost;
    }
    return (cheap);
}

i64 partOne(const char *input)
{
    memset(hp, 0, sizeof hp);
    readInput(input);
    // dumpInput();
    return (cheapestFuel());
}

i64 partTwo(const char *input)
{
    memset(hp, 0, sizeof hp);
    readInput(input);
    return (cheapestFuelV2());
}

int main(int argc, char *argv[])
{
    (void) argc;
    (void) argv[0];

    printf("Solution for sample of part One of Day 7: %llu\n", partOne(SAMPLE));
    printf("Solution for part One of Day 7: %llu\n", partOne(INPUT));
    printf("Solution for sample of part Two of Day 7: %llu\n", partTwo(SAMPLE));
    printf("Solution for part Two of Day 7: %llu\n", partTwo(INPUT));
    return (0);
}