#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define SAMPLE "sample.txt"
#define INPUT "input.txt"
#define MAX_SIZE_LINE 32
#define MAX_SIZE_INPUT 500

typedef struct point {
    size_t x;
    size_t y;
} Point;

typedef struct line {
    Point p1;
    Point p2;
} Line;

// typedef struct diagram {
//     size_t *cell;
//     size_t size;
// } Diagram;

char *puzzle_input[MAX_SIZE_INPUT];
size_t size_input;
Line *lines;
size_t *diagram;
size_t diagram_max_number;

void dumpPuzzleInput()
{
    for (size_t i = 0; i < size_input; ++i) {
        printf("%lu: %s", i, puzzle_input[i]);
    }
}

void dumpLine(size_t idx)
{
        printf("%lu,%lu -> %lu,%lu\n",
               lines[idx].p1.x,
               lines[idx].p1.y,
               lines[idx].p2.x,
               lines[idx].p2.y);
}

void showDiagram(size_t max_col)
{
    for (size_t i = 0; i < diagram_max_number * diagram_max_number; ++i) {
        if (i % max_col == 0)
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
    size_t x1, y1, x2, y2;
    for (size_t i = 0; i < size_input; ++i) {
        sscanf(puzzle_input[i], "%lu,%lu -> %lu,%lu", &x1, &y1, &x2, &y2);
        lines[i].p1 = (Point) {.x = x1, .y = y1};
        lines[i].p2 = (Point) {.x = x2, .y = y2};
    }

    // Find highest number
    diagram_max_number = 0;
    for (size_t i = 0; i < size_input; ++i) {
        if (lines[i].p1.x > diagram_max_number)
            diagram_max_number = lines[i].p1.x;

        if (lines[i].p1.y > diagram_max_number)
            diagram_max_number = lines[i].p1.y;

        if (lines[i].p2.x > diagram_max_number)
            diagram_max_number = lines[i].p2.x;

        if (lines[i].p2.y > diagram_max_number)
            diagram_max_number = lines[i].p2.y;
    }

    diagram_max_number += 1;
    printf("diagram_max_number: %lu\n", diagram_max_number);
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

    diagram = malloc(sizeof(size_t) * diagram_max_number * diagram_max_number);
    for (size_t i = 0; i < diagram_max_number * diagram_max_number ; ++i) {
        diagram[i] = 0;
    }

    for (size_t i = 0; i < size_input; ++i) {
        if (lines[i].p1.x == lines[i].p2.x) {
            if (lines[i].p2.y > lines[i].p1.y) {
                for (size_t j = lines[i].p1.y; j <= lines[i].p2.y; ++j)
                    diagram[j * diagram_max_number + lines[i].p1.x] += 1;
            }
            if (lines[i].p2.y < lines[i].p1.y) {
                for (size_t j = lines[i].p1.y; j >= lines[i].p2.y; --j) {
                    diagram[j * diagram_max_number + lines[i].p1.x] += 1;
                }
            }
        }

        if (lines[i].p1.y == lines[i].p2.y) {
            if (lines[i].p2.x > lines[i].p1.x) {
                for (size_t j = lines[i].p1.x; j <= lines[i].p2.x; ++j)
                    diagram[lines[i].p1.y * diagram_max_number + j] += 1;
            }

            if (lines[i].p2.x < lines[i].p1.x) {
                for (size_t j = lines[i].p1.x; j >= lines[i].p2.x; --j)
                    diagram[lines[i].p1.y * diagram_max_number + j] += 1;
            }
        }
    }

    showDiagram(diagram_max_number);

    for (size_t i = 0; i < diagram_max_number * diagram_max_number; ++i) {
        if (diagram[i] == 2)
            solution++;
    }

    return (solution);
}

int main(int argc, char *argv[])
{
    (void) argc;
    (void) argv[0];

    printf("Solution for the example part One of Day 5: %lu\n", partOne(SAMPLE));
    // printf("Solution for the part One of Day 5: %lu\n", partOne(INPUT));

    return (0);
}