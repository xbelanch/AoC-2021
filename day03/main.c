#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


int bin2dec(int n) {
  int dec = 0, i = 0, rem;
  while (n!=0) {
    rem = n % 10;
    n /= 10;
    dec += rem * pow(2, i);
    ++i;
  }
  return (dec);
}

void dec2bin(size_t c)
{
   int i = 0;
   for(i = 31; i >= 0; i--){
     if((c & (1 << i)) != 0){
       printf("1");
     }else{
       printf("0");
     }
   }
   putchar('\n');
}

// TODO: Rewrite this shit from scratch
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
    int gamma_rate_base10 = bin2dec(atoll(gamma_rate));
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
    int epsilon_rate_base10 = bin2dec(atoll(epsilon_rate));
    // printf("epsilon rate in decimal: %d\n", epsilon_rate_base10);

    return (gamma_rate_base10 * epsilon_rate_base10);
}

#define SAMPLE_SIZE 12
#define SAMPLE_BITS 5
#define INPUT_SIZE 1000
#define INPUT_BITS 12
#define TRUE 1
#define FALSE 0

unsigned int getBit(int value, int bitPosition) {
    return((value >> bitPosition) & 1);
}

unsigned int getCommonBit(size_t *arr, size_t size, int bitPosition, int bitCriteria) {
    unsigned bit[2] = {0, 0};
    for (size_t i = 0; i < size; ++i) {
        if (getBit(arr[i], bitPosition)) { // 1
            bit[1]++;
        } else {
            bit[0]++;
        }
    }

    if (bitCriteria == 1) {
        if (bit[1] > bit[0] || bit[1] ==  bit[0]) {
            return 1;
        } else {
            return 0;
        }
    }

    if (bitCriteria == 0) {
        if (bit[1] > bit[0] || bit[1] ==  bit[0]) {
            return 0;
        } else {
            return 1;
        }
    }

    return (99);
}

int values[SAMPLE_SIZE];
int idx_val = 0;

size_t readInputFile(char *input) {
    FILE *fp = fopen(input, "rb");

    char *line = malloc(sizeof(char) * 6);
    memset(line, 0, sizeof(char) * SAMPLE_BITS);
    while ((fgets(line, 6, fp) != NULL)) {
        if (line[0] != '\n')
            values[idx_val++] = bin2dec(atoi(line));
    }

    fclose(fp);
    return (0);
}

void dumpValues(size_t *values, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        dec2bin(values[i]);
    }
}

size_t getOGR(size_t *bit_criteria, size_t left, int checkBit)
    {
        size_t ogr = 0;
        size_t *tmp;
        while (left > 1) {

            // set 1 for OGR
            unsigned int commonBit = getCommonBit(bit_criteria, left, checkBit, 1);
            // printf("common bit: %d\n", commonBit);

            size_t tmp_size = 0;
            for (size_t i = 0; i < left; ++i) {
                if (getBit(bit_criteria[i], checkBit) != commonBit) {
                    bit_criteria[i] = FALSE;
                } else {
                    tmp_size++;
                }
            }

            // printf("tmp_size: %lu\n", tmp_size);
            tmp = malloc(sizeof(size_t) * tmp_size);
            int j = 0;
            for (size_t i = 0; i < left; ++i) {
                if (bit_criteria[i] != FALSE) {
                    tmp[j++] = bit_criteria[i];
                }
            }

            left = tmp_size;
            bit_criteria = tmp;
            // dumpValues(bit_criteria, left);
            checkBit--;
            if (checkBit < 0)
                checkBit = SAMPLE_BITS - 1;

            if (left == 1)
                ogr = bit_criteria[left - 1];
        }
        return ogr;
    } // end of while

size_t getCO2(size_t *bit_criteria, size_t left, int checkBit)
    {
        size_t co2 = 0;
        size_t *tmp;
        while (left > 1) {

            // set 0 for CO2
            unsigned int commonBit = getCommonBit(bit_criteria, left, checkBit, 0);
            // printf("common bit: %d\n", commonBit);

            size_t tmp_size = 0;
            for (size_t i = 0; i < left; ++i) {
                if (getBit(bit_criteria[i], checkBit) != commonBit) {
                    bit_criteria[i] = FALSE;
                } else {
                    tmp_size++;
                }
            }

            // printf("tmp_size: %lu\n", tmp_size);
            tmp = malloc(sizeof(size_t) * tmp_size);
            int j = 0;
            for (size_t i = 0; i < left; ++i) {
                if (bit_criteria[i] != FALSE) {
                    tmp[j++] = bit_criteria[i];
                }
            }

            left = tmp_size;
            bit_criteria = tmp;
            // dumpValues(bit_criteria, left);
            checkBit--;
            if (checkBit < 0)
                checkBit = SAMPLE_BITS - 1;

            if (left == 1)
                co2 = bit_criteria[left - 1];
        }
        return co2;
    } // end of while

size_t partTwo() {
    readInputFile("sample-01.txt");

    size_t ogr = 0;
    size_t co2 = 0;

    size_t *bit_criteria = malloc(sizeof(size_t) * SAMPLE_SIZE);
    for (size_t i = 0; i < SAMPLE_SIZE; ++i) {
        bit_criteria[i] = values[i];
    }

    ogr = getOGR(bit_criteria, SAMPLE_SIZE, SAMPLE_BITS - 1);

    bit_criteria = malloc(sizeof(size_t) * SAMPLE_SIZE);
    for (size_t i = 0; i < SAMPLE_SIZE; ++i) {
        bit_criteria[i] = values[i];
    }

    co2 = getCO2(bit_criteria, SAMPLE_SIZE, SAMPLE_BITS - 1);

    return (ogr * co2);
}

int main(int argc, char *argv[])
{
    (void) argc;
    (void) argv[0];

    printf("Solution for part Two of Day 3: %lu", partTwo());

    return (0);
}
