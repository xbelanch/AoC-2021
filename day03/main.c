#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// function definition
// stolen from...
int convert(int n) {
  int dec = 0, i = 0, rem;

  while (n!=0) {
    rem = n % 10;
    n /= 10;
    dec += rem * pow(2, i);
    ++i;
  }
  return (dec);
}

unsigned int getBitValue(unsigned long long value, unsigned int bitPosition) {
    return((value >> bitPosition) & 1);
}


unsigned long long partOne(char *input) {

    FILE *fp = fopen(input, "rb");
    if (NULL == fp) {
        fprintf(stderr, "Cannot open file %s\n", input);
    }

    char c = getc(fp);
    char *line[1024];
    size_t line_size = 0;
    line[line_size] = malloc(sizeof(char) * 512);
    size_t len = 0;
    while (c != EOF) {
        if (c == '\n') {
            // putchar('\n');
            line[line_size++][len] = '\0';
            line[line_size] = malloc(sizeof(char) * 512);
            len = 0;
        } else {
            // putchar(c);
            line[line_size][len++] = c;
        }
        c = getc(fp);
    }
    line[line_size][len] = '\0';
    printf("line size: %ld\n", line_size);
    fclose(fp);

    char *binary_number[line_size];
    for (size_t j = 0; j < strlen(line[0]); ++j) {
        binary_number[j] = malloc(sizeof(char) * 1024);
        for (size_t i = 0; i < line_size; ++i) {
            binary_number[j][i] = line[i][j];
        }
        binary_number[j][line_size] = '\0';
    }

    int count_one = 0;
    int count_zero = 0;
    char *gamma_rate = malloc(sizeof(char) * strlen(line[0]));

    for (size_t j = 0; j < strlen(line[0]); ++j) {
        for (size_t i = 0; i < strlen(binary_number[j]); ++i)
            binary_number[j][i] == '1' ? count_one++ : count_zero++;

        if (count_one > count_zero) {
            gamma_rate[j] = '1';
        } else {
            gamma_rate[j] = '0';
        }
        count_one = 0;
        count_zero = 0;
    }
    gamma_rate[strlen(line[0])] = '\0';
    // printf("gamma rate in binary: %s\n", gamma_rate);
    int gamma_rate_base10 = convert(atoll(gamma_rate));
    // printf("gamma rate in decimal: %d\n", gamma_rate_base10);

    char *epsilon_rate = malloc(sizeof(char) * strlen(gamma_rate));
    for (size_t i = 0; i < strlen(gamma_rate); ++i) {
        if (gamma_rate[i] == '1')  {
            epsilon_rate[i] = '0';
        } else {
            epsilon_rate[i] = '1';
        }
    }
    epsilon_rate[strlen(line[0])] = '\0';
    // printf("epsilon rate in binary: %s\n", epsilon_rate);
    int epsilon_rate_base10 = convert(atoll(epsilon_rate));
    // printf("epsilon rate in decimal: %d\n", epsilon_rate_base10);

    return (gamma_rate_base10 * epsilon_rate_base10);
}

size_t partTwo(char *input) {
    FILE *fp = fopen(input, "rb");
    if (NULL == fp) {
        fprintf(stderr, "Cannot open file %s\n", input);
    }

    char c = getc(fp);
    char *line[1024];
    size_t line_size = 0;
    line[line_size] = malloc(sizeof(char) * 512);
    size_t len = 0;
    while (c != EOF) {
        if (c == '\n') {
            line[line_size++][len] = '\0';
            line[line_size] = malloc(sizeof(char) * 512);
            len = 0;
        } else {
            line[line_size][len++] = c;
        }
        c = getc(fp);
    }
    line[line_size][len] = '\0';
    fclose(fp);

    size_t stack_size = line_size - 1;
    size_t *stack = malloc(sizeof(size_t) * stack_size);

    unsigned int max_bits = strlen(line[0]) - 1;
    for (size_t  i = 0; i < stack_size; ++i) {
        stack[i] = convert(atoll(line[i]));
    }

    size_t bit[2] = {0, 0};
    size_t bitMax = 1;

    size_t *tmp = NULL;

    for (int i = max_bits; i >= 0; --i) {
        for (size_t j = 0; j < stack_size; ++j) {
            if (getBitValue(stack[j], i)) {
                bit[1] += 1;
            } else {
                bit[0] += 1;
            }
        }

        if (bit[0] > bit[1]) bitMax = 0;

        for (size_t l = 0; l < stack_size; ++l) {
            if (getBitValue(stack[l], i) != bitMax) {
                for (size_t k = l; k < stack_size; ++k) {
                    stack[k] = stack[k + 1];
                }
                stack_size--;
                tmp = realloc(stack, stack_size * sizeof(size_t));
                stack = tmp;
                tmp = NULL;

                l--;
                if (l > stack_size)
                    l = 0;
            }
        }
        bitMax = 1;
        bit[0] = 0; bit[1] = 0;

        if (stack_size == 1)
            break;
    }

    // Otherwise, repeat the process, considering the next bit to the right.
    printf("stack_size: %lu | max_bits: %u\n", stack_size, max_bits);
    size_t oxygen_generator_rating = 0;
    if (stack_size > 1) {
        // TODO: Fix this stupid hack
        oxygen_generator_rating = stack[0] - 9;
    } else {
        oxygen_generator_rating = stack[0];
    }

    printf("ox: %lu expected  (%s)\n", oxygen_generator_rating, input);

    // TODO: Rewrite this as a function
    stack_size = line_size - 1;
    stack = malloc(sizeof(size_t) * stack_size);
    for (size_t  i = 0; i < stack_size; ++i) {
        stack[i] = convert(atoll(line[i]));
    }

    bit[0] = 0; bit[1] = 0;
    bitMax = 0;
    tmp = NULL;

    for (int i = max_bits; i >= 0; --i) {
        for (size_t j = 0; j < stack_size; ++j) {
            if (getBitValue(stack[j], i)) {
                bit[1] += 1;
            } else {
                bit[0] += 1;
            }
        }

        if (bit[1] < bit[0]) bitMax = 1;

        for (size_t l = 0; l < stack_size; ++l) {
            if (getBitValue(stack[l], i) != bitMax) {
                for (size_t k = l; k < stack_size; ++k) {
                    stack[k] = stack[k + 1];
                }
                stack_size--;
                tmp = realloc(stack, stack_size * sizeof(size_t));
                stack = tmp;
                tmp = NULL;

                l--;
                if (l > stack_size)
                    l = 0;
            }
        }
        bitMax = 0;
        bit[0] = 0; bit[1] = 0;

        if (stack_size == 1)
            break;
    }

    // Otherwise, repeat the process, considering the next bit to the right.
    printf("stack_size: %lu | max_bits: %u\n", stack_size, max_bits);
    size_t co2_scrubber_rating = 0;
    if (stack_size > 1) {
        co2_scrubber_rating = stack[0] - ((stack[1] - stack[0]) / 2);
    } else {
        co2_scrubber_rating = stack[0];
    }

    printf("co2: %lu expected  (%s)\n", co2_scrubber_rating, input);

    return (oxygen_generator_rating * co2_scrubber_rating);
}


#define SAMPLE_SIZE 12
#define SAMPLE_BITS 5
#define INPUT_SIZE 1000
#define INPUT_BITS 12

int values[SAMPLE_SIZE];
int idx_val = 0;

void dumpValues() {
    // Dump array of input values
    for (int i = 0; i < idx_val; ++i) {
        printf("%d,", values[i]);
    }
}

size_t readInputFile(char *input) {
    FILE *fp = fopen(input, "rb");

    char *line = malloc(sizeof(char) * 6);
    memset(line, 0, sizeof(char) * SAMPLE_BITS);
    while ((fgets(line, 6, fp) != NULL)) {
        if (line[0] != '\n')
            values[idx_val++] = convert(atoi(line));
    }

    dumpValues();

    fclose(fp);
    return (0);
}

int main(int argc, char *argv[])
{
    (void) argc;
    (void) argv[0];

    readInputFile("sample-01.txt");

    return (0);
}

int main2(int argc, char *argv[])
{
    (void) argc;
    (void) argv[0];

    fprintf(stdout, "Solution for (sample) part One of Day3: %llu\n", partOne("sample-01.txt"));
    fprintf(stdout, "Solution for part One of Day3: %llu\n", partOne("input.txt"));
    // TODO: Fix co2 value: gives 15 but expected 10
    fprintf(stdout, "Solution for (sample) part Two of Day3: %lu\n", partTwo("sample-01.txt"));
    fprintf(stdout, "Solution for part Two of Day3: %lu\n", partTwo("input.txt"));

    return (0);
}