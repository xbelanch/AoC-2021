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
    printf("line size: %ld\n", line_size);
    fclose(fp);

    // Extract binary numbers considering the first bit of each numbers
    char *binary_number[line_size];
    for (size_t j = 0; j < strlen(line[0]); ++j) {
        binary_number[j] = malloc(sizeof(char) * 1024);
        for (size_t i = 0; i < line_size; ++i) {
            binary_number[j][i] = line[i][j];
        }
        binary_number[j][line_size] = '\0';
    }

    // Save that information in a simple array
    int count_one = 0;
    int count_zero = 0;
    char *bit_criteria = malloc(sizeof(char) * 1028);
    for (size_t j = 0; j < strlen(line[0]); ++j) {
        for (size_t i = 0; i < strlen(binary_number[j]); ++i)
            binary_number[j][i] == '1' ? count_one++ : count_zero++;

        if (count_one > count_zero) {
            bit_criteria[j] = '1';
        } else {
            bit_criteria[j] = '0';
        }
        count_one = 0;
        count_zero = 0;
    }

    printf("bit_criteria: %s\n", bit_criteria);
    // Duplicate the input array of binary numbers;
    char *stack[line_size];
    for (size_t  i = 0; i < line_size; ++i) {
        stack[i] = line[i];
    }

    // First iteration. Example
    size_t stack_size = line_size;
    for (size_t i = 0; i < line_size; ++i) {
        if (stack[i] == NULL)
            break;
        if (stack[i][strlen(stack[i] - 1)] != '1') {
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

    // Then consider the second bit of the 7 remaining numbers
    count_one = 0; count_zero = 0;
    for (size_t i = 0; i < stack_size; ++i) {
        stack[i][1] == '1' ? count_one++ : count_zero++;
    }
    count_one > count_zero ? printf("Winner is 1\n") : printf("Winner is 0\n");

    // Second iteration (second position)
    for (size_t i = 0; i < stack_size; ++i) {
        if (stack[i] == NULL)
            break;
        if (stack[i][1] != '0') {
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

    // Then consider the second bit of the 4 remaining numbers
    count_one = 0; count_zero = 0;
    char winner_bit = '1';
    for (size_t i = 0; i < stack_size; ++i) {
        stack[i][2] == '1' ? count_one++ : count_zero++;
    }
    if (count_zero > count_one)
        winner_bit = '0';

    // third iteration (third position)
    for (size_t i = 0; i < stack_size; ++i) {
        if (stack[i] == NULL)
            break;
        if (stack[i][2] != winner_bit) {
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

    // Then consider the second bit of the 3 remaining numbers
    count_one = 0; count_zero = 0;
    winner_bit = '1';
    for (size_t i = 0; i < stack_size; ++i) {
        stack[i][3] == '1' ? count_one++ : count_zero++;
    }
    if (count_zero > count_one)
        winner_bit = '0';

    // Fourth iteration (fourth position)
    for (size_t i = 0; i < stack_size; ++i) {
        if (stack[i] == NULL)
            break;
        if (stack[i][3] != winner_bit) {
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

// Then consider the second bit of the 2 remaining numbers
    count_one = 0; count_zero = 0;
    winner_bit = '1';
    for (size_t i = 0; i < stack_size; ++i) {
        stack[i][4] == '1' ? count_one++ : count_zero++;
    }
    if (count_zero > count_one)
        winner_bit = '0';

    // Fifth iteration (fifth position)
    for (size_t i = 0; i < stack_size; ++i) {
        if (stack[i] == NULL)
            break;
        if (stack[i][3] != winner_bit) {
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

// Then consider the second bit of the 2 remaining numbers
    count_one = 0; count_zero = 0;
    winner_bit = '1';
    for (size_t i = 0; i < stack_size; ++i) {
        stack[i][5] == '1' ? count_one++ : count_zero++;
    }
    if (count_zero > count_one)
        winner_bit = '0';

    // Fifth iteration (fifth position)
    for (size_t i = 0; i < stack_size; ++i) {
        if (stack[i] == NULL)
            break;
        if (stack[i][3] != winner_bit) {
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
    for (size_t i = 0; i < stack_size; ++i) {
        printf("%s\n", stack[i]);
    }


    // determine the oxygen generator rating




    unsigned long long oxygen_generator_rating = 0;
    unsigned long long co2_scrubber_rating = 0;





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