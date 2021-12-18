#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define SAMPLE "sample.txt"
#define INPUT "input.txt"
#define MAX_SIZE_LINE 32
#define MAX_SIZE_INPUT 500
#define COL_SIZE 32
#define ROW_SIZE 32

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

size_t diagram[COL_SIZE * ROW_SIZE];

void dumpPuzzleInput()
{
    for (size_t i = 0; i < size_input; ++i) {
        printf("%lu: %s", i, puzzle_input[i]);
    }
}

void dumpLine(size_t idx)
{
        printf("%d,%d -> %d,%d\n",
               lines[idx].p1.x,
               lines[idx].p1.y,
               lines[idx].p2.x,
               lines[idx].p2.y);
}

void showDiagram()
{
    for (size_t i = 0; i < COL_SIZE * ROW_SIZE; ++i) {
        if (i % COL_SIZE == 0)
            putchar('\n');
        if (diagram[i] == 0) {
            putchar('.');
        } else if (diagram[i] == 1) {
            putchar('1');
        } else if (diagram[i] == 2) {
            putchar('2');
        } else {
            putchar('?');
        }
    }
    putchar('\n');
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
    size_t solution = 0;
    readInput(input);
    parse();

    for (size_t i = 0; i < ROW_SIZE * COL_SIZE; ++i) {
        diagram[i] = 0;
    }

    for (size_t i = 0; i < size_input; ++i) {
        if (lines[i].p1.x == lines[i].p2.x) {
            if (lines[i].p2.y > lines[i].p1.y) {
                for (int j = lines[i].p1.y; j <= lines[i].p2.y; ++j)
                    diagram[j * ROW_SIZE + lines[i].p1.x] += 1;
            }
            if (lines[i].p2.y < lines[i].p1.y) {
                for (int j = lines[i].p1.y; j >= lines[i].p2.y; --j) {
                    diagram[j * ROW_SIZE + lines[i].p1.x] += 1;
                }
            }
        }

        if (lines[i].p1.y == lines[i].p2.y) {
            if (lines[i].p2.x > lines[i].p1.x) {
                for (int k = lines[i].p1.x; k <= lines[i].p2.x; ++k)
                    diagram[lines[i].p1.y * ROW_SIZE + k] += 1;
            }

            if (lines[i].p2.x < lines[i].p1.x) {
                for (int k = lines[i].p1.x; k >= lines[i].p2.x; --k)
                    diagram[lines[i].p1.y * ROW_SIZE + k] += 1;
            }
        }
    }

    for (size_t i = 0; i < ROW_SIZE * COL_SIZE; ++i) {
        if (diagram[i] == 2)
            solution++;
    }
    showDiagram();
    return (solution);
}

int main(int argc, char *argv[])
{
    (void) argc;
    (void) argv[0];

    printf("Solution for the example part One of Day 5: %lu", partOne(SAMPLE));

    return (0);
}