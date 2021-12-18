#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define SAMPLE "sample.txt"
#define INPUT "input.txt"
#define MAX_SIZE_LINE 32
#define MAX_SIZE_INPUT 500

typedef struct point {
    int x;
    int y;
} Point;

typedef struct line {
    Point p1;
    Point p2;
} Line;

char *puzzle_input[MAX_SIZE_INPUT];
size_t size_input;
Line *lines;

void dumpPuzzleInput()
{
    for (size_t i = 0; i < size_input; ++i) {
        printf("%lu: %s", i, puzzle_input[i]);
    }
}

void dumpLines()
{
    for (size_t i = 0; i < size_input; ++i) {
        printf("%d,%d -> %d,%d\n",
               lines[i].p1.x,
               lines[i].p1.y,
               lines[i].p2.x,
               lines[i].p2.y);
    }
}

void parse()
{
    lines = malloc(sizeof(Line) * size_input);
    int x1, y1, x2, y2;
    for (size_t i = 0; i < size_input; ++i) {
        sscanf(puzzle_input[i], "%d,%d -> %d,%d", &x1, &y1, &x2, &y2);
        lines[i].p1 = (Point) {.x = x1, .y = y1};
        lines[i].p2 = (Point) {.x = x2, .y = y2};
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
    parse();
    dumpLines();
    return (0);
}

int main(int argc, char *argv[])
{
    (void) argc;
    (void) argv[0];

    printf("Solution for the example part One of Day 5: %lu", partOne(INPUT));

    return (0);
}