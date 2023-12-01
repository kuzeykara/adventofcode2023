#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_LINE 100

int is_digit(char*);

int part1(char* filename) {
    FILE *fp;
    char currLine[MAX_LINE];
    char currChar, firstDigit, lastDigit;
    char twoDigit[3];
    int isFirst = 1, sum = 0;
    int calibration_value;

    if ((fp = fopen(filename, "r")) == NULL) {
        fprintf(stderr, "Error opening file %s\n", filename);
        exit(1);
    }

    while(fgets(currLine, MAX_LINE, fp) != NULL) {
        for (int i=0; currLine[i]!='\n'; i++) {
            currChar = currLine[i];
            if (is_digit(&currChar) == 0) {
                if (isFirst == 1) {
                    firstDigit = currChar;
                    isFirst = 0;
                }
                lastDigit = currChar;
            }
        }
        isFirst = 1;
        sprintf(twoDigit, "%c%c", firstDigit, lastDigit);
        sscanf(twoDigit, "%d", &calibration_value);
        //printf("Calibration value: %d\n", calibration_value);
        sum += calibration_value;
    }
    printf("\nSum: %d\n", sum);

    fclose(fp);

    return 0;
}

int part2(char* filename) {
    printf("%s\n", filename);

    return 0;
}

int is_digit(char* c) {
    if (*c>=48 && *c<=57) {
        return 0;
    }
    return 1;
}


int main(int argc, char** argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage: ./day01 <1|2> <inputfile>\n");
        return 1;
    }

    if (strcmp(argv[1], "1") == 0) {
        part1(argv[2]);
    } else if (strcmp(argv[1], "2") == 0) {
        part2(argv[2]);
    } else {
        fprintf(stderr, "Usage: ./day01 <1|2> <inputfile>\n");
        return 1;
    }

    return 0;
}
