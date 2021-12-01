#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE_NUMBER 4

int parse_input_file(char *filename)
{
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        fprintf(stderr, "Cannot open file: %s\n", filename);
        return (1);
    }

    int c;
    int index = 0;
    char *number = malloc(sizeof(char) * MAX_SIZE_NUMBER + 1);
    while ((c = getc(file)) != EOF) {
        if (c == '\n') {
            fprintf(stdout, "%s", number);
            number[index] = '\0';
            printf("-");
            index = 0;
        } else {
            number[index++] = c;
        }
    }
    // print last number
    fprintf(stdout, "%s", number);

    fclose(file);
    return (0);
}

int main(int argc, char *argv[])
{
    (void) argc;
    (void) argv[0];
    parse_input_file("sample-01.txt");
    parse_input_file("input-01.txt");

    return (0);
}