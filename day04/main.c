#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_SIZE_LINE 1024
#define MAX_SIZE_BOARDS 128
#define SAMPLE_INPUT "sample-01.txt"
#define INPUT_FILE "input.txt"

char *draw_numbers;
char *board[MAX_SIZE_BOARDS];
size_t board_size = 0;

void dumpBoards() {
    for (size_t i = 0; i < board_size; ++i) {
        printf("%lu: %s\n", i, board[i]);
    }
}

size_t partOne(char *input) {
    size_t solution = 0;
    FILE *fp = fopen(input, "rb");
    if (fp == NULL)
        return(1);

    char *line = malloc(sizeof(char) * MAX_SIZE_LINE);
    size_t number_line = 0;
    int count = 0;

    board[board_size] = malloc(sizeof(char) * MAX_SIZE_LINE);
    // end = board[board_size];
    while (fgets(line, MAX_SIZE_LINE, fp)) {

        if (line[0] == '\n')
            continue;

        // get random draw numbers (firs line of input file)
        if (number_line == 0) {
            line[strlen(line) - 1] = '\0'; // remove newline
            size_t len = strlen(line);
            draw_numbers = malloc(sizeof(char) * len);
            memcpy(draw_numbers, line, len);
            printf("%s\n", draw_numbers);
        } else

        // get boards
        {
            if (line[strlen(line) - 1] == '\n')
                line[strlen(line) - 1] = '\0';

            size_t len = strlen(line);
            size_t len2 = strlen(board[board_size]);
            char *end = &board[board_size][len2];
            memcpy(end, line, len);
            end = &board[board_size][len2];
            memcpy(end, " ", 1);
            count++;
            if (count % 5 == 0) {
                count = 0;
                board_size++;
                board[board_size] = malloc(sizeof(char) * MAX_SIZE_LINE);
            }
        }

        number_line++;
    }

    dumpBoards();

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