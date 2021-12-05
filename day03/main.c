#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// function definition
// stolen from...
unsigned long long convert(unsigned long long n) {
  int dec = 0, i = 0, rem;

  while (n!=0) {
    rem = n % 10;
    n /= 10;
    dec += rem * pow(2, i);
    ++i;
  }
  return dec;
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

unsigned long long partTwo(char *input) {
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
    // printf("line size: %ld\n", line_size);
    fclose(fp);

    char *stack[line_size];
    size_t stack_size = line_size;
    for (size_t  i = 0; i < line_size; ++i) {
        stack[i] = line[i];
    }

    size_t count_one = 0;
    size_t count_zero = 0;
    char winner_bit = '1';

    // determine the oxygen generator rating
    for (size_t bit = 0; bit < strlen(stack[0]); ++bit) {
        if (stack_size == 1) break;
        for (size_t i = 0; i < stack_size; ++i) {
            stack[i][bit] == '1' ? count_one++ : count_zero++;
        }
        if (count_zero > count_one) {
            winner_bit = '0';
        } else {
            winner_bit = '1';
        }
        for (size_t i = 0; i < stack_size; ++i) {
            if (stack[i] == NULL)
                break;
            if (stack[i][bit] != winner_bit) {
                for (size_t j = i; j < stack_size; ++j) {
                    stack[j] = stack[j + 1];
                }

                stack_size--;
                stack[stack_size] = NULL;

                i--;
                if (i > line_size)
                    i = 0;
            }
        }

        count_one = 0;
        count_zero = 0;
    }

    unsigned long long oxygen_generator_rating = convert(atoll(stack[0]));

    // Log stack
    // for (size_t i = 0; i < stack_size; ++i) {
    //     printf("%s\n", stack[i]);
    // }

    // Start again...
    stack_size = line_size;
    for (size_t  i = 0; i < line_size; ++i) {
        stack[i] = line[i];
    }

    // Determine the oxygen generator rating
    count_one = 0;
    count_zero = 0;
    winner_bit = '0';

    for (size_t bit = 0; bit < strlen(stack[0]); ++bit) {
        if (stack_size == 1) break;
        for (size_t i = 0; i < stack_size; ++i) {
            stack[i][bit] == '1' ? count_one++ : count_zero++;
        }

        if (count_one < count_zero)  winner_bit = '1';
        if (count_one == count_zero) winner_bit = '0';

        for (size_t i = 0; i < stack_size; ++i) {
            if (stack[i] == NULL)
                break;
            if (stack[i][bit] != winner_bit) {
                for (size_t j = i; j < stack_size; ++j) {
                    stack[j] = stack[j + 1];
                }

                stack_size--;
                stack[stack_size] = NULL;

                i--;
                if (i > line_size)
                    i = 0;
            }
        }

        // Log stack
        // putchar('\n');
        // for (size_t i = 0; i < stack_size; ++i) {
        //     printf("%s\n", stack[i]);
        // }

        count_one = 0;
        count_zero = 0;
    }

    unsigned long long co2_scrubber_rating = convert(atoll(stack[0]));;

    return (oxygen_generator_rating * co2_scrubber_rating);
}

int main(int argc, char *argv[])
{
    (void) argc;
    (void) argv[0];

    fprintf(stdout, "Solution for (sample) part One of Day3: %llu\n", partOne("sample-01.txt"));
    fprintf(stdout, "Solution for part One of Day3: %llu\n", partOne("input.txt"));
    fprintf(stdout, "Solution for (sample) part Two of Day3: %llu\n", partTwo("sample-01.txt"));

    return (0);
}