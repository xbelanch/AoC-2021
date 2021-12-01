#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE_NUMBER 4

int depth[2001];
int depth_size = 0;

int partOne() {
    int increases = 0;
    for (int i = 1; i < depth_size; ++i) {
        if (depth[i - 1] < depth[i]) {
            increases++;
        }
    }
    return increases;
}

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
            number[index] = '\0';
            depth[depth_size++] = atoi(number);
            index = 0;
        } else {
            number[index++] = c;
        }
    }
    depth[depth_size++] = atoi(number);
    fclose(file);
    return (0);
}

int main(int argc, char *argv[])
{
    (void) argc;
    (void) argv[0];
    // parse_input_file("sample-01.txt");
    parse_input_file("input-01.txt");
    fprintf(stdout, "Solution part One: %d\n", partOne());

    return (0);
}