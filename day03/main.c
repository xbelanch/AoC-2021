#include <stdio.h>
#include <stdlib.h>

int partOne(char *input) {

    FILE *fp = fopen(input, "rb");
    if (NULL == fp) {
        fprintf(stderr, "Cannot open file %s\n", input);
    }

    char c = getc(fp);
    char *line[48];
    size_t line_size = 0;
    line[line_size] = malloc(sizeof(char) * 32);
    size_t len = 0;
    while (c != EOF) {
        if (c == '\n') {
            // putchar('\n');
            line[line_size++][len] = '\0';
            line[line_size] = malloc(sizeof(char) * 32);
            len = 0;
        } else {
            // putchar(c);
            line[line_size][len++] = c;
        }
        c = getc(fp);
    }

    fclose(fp);

    for (size_t i = 0; i < line_size; ++i) {
        printf("%s\n", line[i]);
    }

    return (0);
}

int main(int argc, char *argv[])
{
    (void) argc;
    (void) argv[0];

    fprintf(stdout, "Solution for part One of Day3: %d\n", partOne("sample-01.txt"));

    return (0);
}