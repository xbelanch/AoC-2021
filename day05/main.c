#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define SAMPLE "sample.txt"
#define SAMPLE2 "sample2.txt"
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
size_t *diagram;
int diagram_max_number;
int diagram_min_number;

void dumpPuzzleInput()
{
    for (size_t i = 0; i < size_input; ++i) {
        printf("%lu: %s", i, puzzle_input[i]);
    }
}

void dumpLine(Line line)
{
        printf("%d,%d -> %d,%d\n",
               line.p1.x,
               line.p1.y,
               line.p2.x,
               line.p2.y);
}

void showDiagram(size_t max_col)
{
    for (size_t i = 0; i < max_col * max_col; ++i) {
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
    int x1, y1, x2, y2;
    for (size_t i = 0; i < size_input; ++i) {
        sscanf(puzzle_input[i], "%d,%d -> %d,%d", &x1, &y1, &x2, &y2);
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

    printf("diagram_max_number: %d\n", diagram_max_number);
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

int diagramUpdate(size_t *diagram, int x, int y)
{
    int val = 0;
    if (diagram[y * diagram_max_number + x] == 1)
        val++;

    diagram[y * diagram_max_number + x]++;

    return val;
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

    // TODO: Solve this solution
    for (size_t i = 0; i < size_input; ++i) {
        Line line = lines[i];
        if (line.p1.x == line.p2.x) {
            int x = line.p1.x;
            int y0, y1;
            if (line.p2.y > line.p1.y) {
                y1 = line.p2.y;
                y0 = line.p1.y;
            } else {
                y1 = line.p1.y;
                y0 = line.p2.y;
            }

            for (int y = y0; y <= y1; ++y) {
                solution += diagramUpdate(diagram, x, y);
            }

        } else if (line.p1.y == line.p2.y) {
            int y = line.p1.y;
            int x0, x1;
            if (line.p2.x > line.p1.x) {
                x1 = line.p2.x;
                x0 = line.p1.x;
            } else {
                x1 = line.p1.x;
                x0 = line.p2.x;
            }

            for (int x = x0; x <= x1; ++x) {
                solution += diagramUpdate(diagram, x, y);
            }
        }
    }

    showDiagram(10);

    return (solution);
}

int main(int argc, char *argv[])
{
    (void) argc;
    (void) argv[0];

    printf("Solution for the example part One of Day 5: %lu\n", partOne(SAMPLE));
    printf("Solution for the example part One of Day 5: %lu\n", partOne(SAMPLE2));
    printf("Solution for the part One of Day 5: %lu\n", partOne(INPUT));

    return (0);
}