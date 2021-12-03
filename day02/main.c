#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_SIZE_LINES 2048
char *lines[MAX_SIZE_LINES];
int lines_size = 0;

int partOne(char *input) {
    int horizontal_position = 0;
    int depth = 0;

    FILE *fp = fopen(input, "rb");
    if (NULL == fp) {
        fprintf(stderr, "File not found\n");
        return (1);
    }

    lines[lines_size] = (char*)malloc(sizeof(char) * 32);
    int len = 0;
    char chr;
    while (chr != EOF) {
        chr = fgetc(fp);
        if (chr == '\n') {
            lines[lines_size][len] = '\0';
            lines_size += 1;
            lines[lines_size] = (char*)malloc(sizeof(char) * 32);
            len = 0;
        } else {
            lines[lines_size][len++] = chr;
        }
    }

    lines[lines_size][len - 1] = '\0';
    fprintf(stdout, "Number of lines: %d\n", lines_size);

    for (int i = 0; i < lines_size; ++i) {
            char *units = strchr(lines[i], ' ');
            int value = atoi(&units[1]);
            if (lines[i][0] == 'f') { // forward
                horizontal_position += value;
            } else if (lines[i][0] == 'd') { // down
                depth += value;
            } else if (lines[i][0] == 'u') { // up
                depth -= value;
            }
    }

    fclose(fp);
    return (horizontal_position * depth);
}

unsigned long long partTwo() {
    unsigned long long horizontal_position = 0;
    unsigned long long depth = 0;
    unsigned long long aim = 0;

    for (int i = 0; i < lines_size; ++i) {
            char *units = strchr(lines[i], ' ');
            int value = atoi(&units[1]);
            if (lines[i][0] == 'f') { // forward
                horizontal_position += value;
                depth += value * aim;
            } else if (lines[i][0] == 'd') { // down
                aim += value;
            } else if (lines[i][0] == 'u') { // up
                aim -= value;
            }
    }

    return (horizontal_position * depth);
}


int main(int argc, char *argv[])
{
    (void) argc;
    (void) argv[0];

    printf("Solution for part One: %d\n", partOne("input.txt"));
    printf("Solution for part Two: %lld\n", partTwo());
    return (0);
}