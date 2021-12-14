#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

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
bool marked[99];
bool winboards[MAX_SIZE_BOARDS];

void dumpBoards() {
    for (size_t i = 0; i < board_size; ++i) {
        printf("%lu: %s\n", i, board[i]);
    }
}

bool checkHorizontallyWinner(size_t *board)
{
    for (size_t i = 0; i < BOARD_ROW; ++i) {
        if (marked[board[i * BOARD_COL]] &&
            marked[board[i * BOARD_COL + 1]] &&
            marked[board[i * BOARD_COL + 2]] &&
            marked[board[i * BOARD_COL + 3]] &&
            marked[board[i * BOARD_COL + 4]])
            return true;
    }
    return false;
}

bool checkVerticallyWinner(size_t *board)
{
    for (size_t i = 0; i < BOARD_COL; ++i) {
        if (marked[board[i]] &&
            marked[board[i + BOARD_ROW]] &&
            marked[board[i + (BOARD_ROW * 2)]] &&
            marked[board[i + (BOARD_ROW * 3)]] &&
            marked[board[i + (BOARD_ROW * 4)]])
            return true;
    }
    return false;
}

void dumpBingoBoard(size_t *board) {
    for (size_t j = 0; j < BOARD_COL; ++j) {
        for (size_t i = 0; i < BOARD_ROW; ++i) {
            if (marked[board[(j * BOARD_COL) + i]] == true) {
                printf("[%lu]\t\t", board[(j * BOARD_COL) + i]);
            } else {
                printf("%lu\t\t", board[(j * BOARD_COL) + i]);
            }
        }
        putchar('\n');
    }
}

size_t sumAllUnmarkedNumbers(size_t *board)
{
    size_t sum = 0;
    for (size_t j = 0; j < BOARD_COL; ++j) {
        for (size_t i = 0; i < BOARD_ROW; ++i) {
            if (marked[board[(j * BOARD_COL) + i]] == false)
                sum += board[(j * BOARD_COL) + i];
        }
    }
    return (sum);
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

int parseInput(char *input)
{
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

    fclose(fp);
    return(0);
}

size_t partOne(char *input) {
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

    // Initalize marked values to false
    for (size_t i = 0; i < 99; ++i) {
        marked[i] = false;
    }

    // Dump random draw numbers
    size_t *dw = parseNumbers(draw_numbers, ',');
    for (size_t i = 0; i < draw_numbers_size; ++i) {
        marked[dw[i]] = true;
        {
            for (size_t j = 0; j < board_size; ++j) {
                size_t *bd = parseNumbers(board[j], ' ');
                if (checkHorizontallyWinner(bd) ||
                    checkVerticallyWinner(bd)) {
                    printf("Round: %lu\n", i);
                    dumpBingoBoard(bd);
                    printf("^^^^^^^^^^^^^^^^^^^^^^\n");
                    printf("%lu\n", dw[i]);
                    return sumAllUnmarkedNumbers(bd) * dw[i];
                }
            }
        }
    }

    fclose(fp);
    return(0);
}

size_t partTwo(char *input)
{
    parseInput(input);
    // Initalize values to false
    for (size_t i = 0; i < 99; ++i) {
        marked[i] = false;
    }
    for (size_t i = 0; i < board_size; ++i) {
        winboards[board_size] = false;
    }

    // Dump random draw numbers
    size_t last_draw_number;
    size_t sum_last_winboard;
    size_t *bd;
    size_t *dw = parseNumbers(draw_numbers, ',');
    for (size_t i = 0; i < draw_numbers_size; ++i) {
        marked[dw[i]] = true;
        {
            for (size_t j = 0; j < board_size; ++j) {
                if (winboards[j])
                    continue;
                bd = parseNumbers(board[j], ' ');

                if (checkHorizontallyWinner(bd) ||
                    checkVerticallyWinner(bd)) {
                    winboards[j] = true;
                    printf("draw number: %lu winboard: %lu\n", dw[i], j);
                    sum_last_winboard = sumAllUnmarkedNumbers(bd);
                    last_draw_number = dw[i];
                }
            }
        }
    }

    return sum_last_winboard * last_draw_number;
}

int main(int argc, char *argv[])
{
    (void) argc;
    (void) argv[0];
    printf("Solution for the part One of Day 4 (%s): %lu\n", SAMPLE_INPUT, partOne(SAMPLE_INPUT));
    printf("Solution for the part One of Day 4 (%s): %lu\n", INPUT_FILE, partOne(INPUT_FILE));
    printf("Solution for the part Two of Day 4 (%s): %lu\n", SAMPLE_INPUT, partTwo(SAMPLE_INPUT));

    return (0);
}