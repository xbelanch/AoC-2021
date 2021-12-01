#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE_NUMBER 4

int arr[2048];
int arr_size = 0;

int partOne() {
    int increases = 0;
    for (int i = 1; i < arr_size; ++i) {
        if (arr[i - 1] < arr[i]) {
            increases++;
        }
    }
    return (increases);
}

int partTwo() {
    int increases = 0;
    // We don't count the last three numbers of the array
    for (int i = 0; i < arr_size - (3); ++i) {
        int curr = arr[i] + arr[i + 1] + arr[i + 2];
        int next = arr[i + 1] + arr[i + 2] + arr[i + 3];
        if (next > curr)
            increases++;
    }
    fprintf(stdout, "arr_size: %d\n", arr_size);
    return(increases);
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
            arr[arr_size++] = atoi(number);
            index = 0;
        } else {
            number[index++] = c;
        }
    }
    arr[arr_size] = atoi(number);
    fclose(file);
    return (0);
}

int main(int argc, char *argv[])
{
    (void) argc;
    (void) argv[0];
    // parse_input_file("sample-01.txt");
    parse_input_file("input.txt");
    fprintf(stdout, "Solution part One: %d\n", partOne());
    fprintf(stdout, "Solution part Two: %d\n", partTwo());

    return (0);
}