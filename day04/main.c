#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_SIZE_LINE 2048
#define MAX_SIZE_BOARDS 512
#define SIZE_DRAW_NUMBERS 128
#define BOARD_ROW 5
#define BOARD_COL 5
#define SAMPLE_INPUT "sample-01.txt"
#define INPUT_FILE "input.txt"

char *draw_numbers;
size_t draw_numbers_size;
char *board[MAX_SIZE_BOARDS];
size_t board_size;

void dumpBoards() {
    for (size_t i = 0; i < board_size; ++i) {
        printf("%lu: %s\n", i, board[i]);
    }
}

size_t *parseNumbers(char *input, char delimiter) {
    size_t len = strlen(input);
    char number[2];
    size_t j = 0;
    size_t count = 0;
    size_t *numbers = malloc(sizeof(size_t) * draw_numbers_size);
    char prev = delimiter;
    for (size_t i = 0; i < len; ++i) {
        if (input[i] == delimiter && prev == delimiter) {
            prev = delimiter;
            continue;
        } else if (input[i] == delimiter && prev != delimiter) {
            numbers[count++] = atol(number);
            memset(&number, 0, 2);
            prev = delimiter;
            j = 0;
        } else {
            number[j++] = input[i];
            prev = input[i];
        }
    }

    numbers[count] = atol(number);
    return numbers;
}

size_t partOne(char *input) {
    size_t solution = 0;
    FILE *fp = fopen(input, "rb");
    if (fp == NULL) {
        fprintf(stderr, "%s not found\n", input);
        return(1);
    }

    char *line = malloc(sizeof(char) * MAX_SIZE_LINE);
    size_t number_line = 0;
    int count = 0;

    draw_numbers_size = 0;
    board_size = 0;
    board[board_size] = malloc(sizeof(char) * MAX_SIZE_LINE);
    char *tmp;

    while (fgets(line, MAX_SIZE_LINE, fp)) {

        if (line[0] == '\n')
            continue;

        // get random draw numbers (firs line of input file)
        if (number_line == 0) {
            line[strlen(line) - 1] = '\0'; // remove newline
            size_t len = strlen(line);
            draw_numbers = malloc(sizeof(char) * len);
            tmp = (char*)malloc(sizeof(char) * len);
            memcpy(draw_numbers, line, len);
            // get size of draw random numbers
            memcpy(tmp, line, len);
            tmp = strtok(line, ",");
            while (tmp != NULL) {
                tmp = strtok(NULL, ",");
                draw_numbers_size++;
            }
            free(tmp);
            printf("draw_numbers_size: %lu\n", draw_numbers_size);
        }
        else

        // get boards
        {
            if (line[strlen(line) - 1] == '\n')
                line[strlen(line) - 1] = '\0';

            size_t len = strlen(line);
            size_t len2 = strlen(board[board_size]);
            char *end = &board[board_size][len2] + 1;
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

    // Dump random draw numbers
    size_t *dw = parseNumbers(draw_numbers, ',');
    for (size_t i = 0; i < draw_numbers_size; ++i) {
        printf("%lu,", dw[i]);
    }
    putchar('\n');
    // Dump board data
    printf("Boards: \n");
    for (size_t j = 0; j < board_size; ++j) {
        size_t *bd = parseNumbers(board[j], ' ');
        for (size_t i = 0; i < BOARD_COL * BOARD_ROW; ++i) {
            printf("%lu,", bd[i]);
        }
        putchar('\n');
    }


    fclose(fp);
    return(solution);
}

int main(int argc, char *argv[])
{
    (void) argc;
    (void) argv[0];
    printf("Solution for the part One of Day 4 (%s): %lu\n", SAMPLE_INPUT, partOne(SAMPLE_INPUT));
    printf("Solution for the part One of Day 4 (%s): %lu\n", INPUT_FILE, partOne(INPUT_FILE));

    return (0);
}