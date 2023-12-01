#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_LINE 100

int is_digit(char*);
char find_digit(char*, int, int);

int part1(char* filename) {
    FILE *fp;
    char currLine[MAX_LINE], twoDigit[3];
    char currChar, firstDigit, lastDigit;
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
    fclose(fp);

    return sum;
}


int part2(char* filename) {
    FILE *fp;
    char currLine[MAX_LINE], twoDigit[3];
    char currChar, firstDigit, lastDigit;
    int i = 0, isFirst = 1, length = 0, foundDigit = -1, sum = 0;
    int calibration_value;


    if ((fp = fopen(filename, "r")) == NULL) {
        fprintf(stderr, "Error opening file %s\n", filename);
        exit(1);
    }

    while(fgets(currLine, MAX_LINE, fp) != NULL) {
        length = strlen(currLine);
        i = 0;
        while(currLine[i] != '\n') {
            currChar = currLine[i];

            if (is_digit(&currChar) == 0) {
                if (isFirst == 1) {
                    firstDigit = currChar;
                    isFirst = 0;
                }
                lastDigit = currChar;
            } else {
                foundDigit = find_digit(currLine, i, length);
                if (foundDigit != '-') {
                    if (isFirst == 1) {
                        firstDigit = foundDigit;
                        isFirst = 0;
                    }
                    lastDigit = foundDigit;
                }
            }

            i++;
        }
        isFirst = 1;
        sprintf(twoDigit, "%c%c", firstDigit, lastDigit);
        sscanf(twoDigit, "%d", &calibration_value);
        //printf("Calibration value: %d\n", calibration_value);
        sum += calibration_value;
    }
    fclose(fp);

    return sum;
}


int is_digit(char* c) {
    if (*c>=48 && *c<=57) {
        return 0;
    }
    return 1;
}


char find_digit(char *line, int pos, int len) {
    if ((len-pos) < 3) {
        return '-';
    }

    char currChar = line[pos];

    if ((len-pos) >= 3) {
        // can be: one two six
        switch(currChar) {
            case 'o':
                if (line[pos+1]=='n' && line[pos+2]=='e') {
                    return '1';
                }
                break;
            case 't':
                if (line[pos+1]=='w' && line[pos+2]=='o') {
                    return '2';
                }
                break;
            case 's':
                if (line[pos+1]=='i' && line[pos+2]=='x') {
                    return '6';
                }
                break;
        }
    } 
    if ((len-pos) >= 4) {
        // can also be: zero four five nine
        switch(currChar) {
            case 'z':
                if (line[pos+1]=='e' && line[pos+2]=='r' && line[pos+3]=='o') {
                    return '0';
                }
                break;
            case 'f':
                if (line[pos+1]=='o' && line[pos+2]=='u' && line[pos+3]=='r') {
                    return '4';
                } else if (line[pos+1]=='i' && line[pos+2]=='v' && line[pos+3]=='e') {
                    return '5';
                }
                break;
            case 'n':
                if (line[pos+1]=='i' && line[pos+2]=='n' && line[pos+3]=='e') {
                    return '9';
                }
                break;
        }
    }
    if ((len-pos) >= 5) {
        // can also be: three seven eight
        switch(currChar) {
            case 't':
                if (line[pos+1]=='h' && line[pos+2]=='r' && line[pos+3]=='e' && line[pos+4]=='e') {
                    return '3';
                }
                break;
            case 's':
                if (line[pos+1]=='e' && line[pos+2]=='v' && line[pos+3]=='e' && line[pos+4]=='n') {
                    return '7';
                }
                break;
            case 'e':
                if (line[pos+1]=='i' && line[pos+2]=='g' && line[pos+3]=='h' && line[pos+4]=='t') {
                    return '8';
                }
                break;
        }
    }

    return '-';
}


int main(int argc, char** argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage: ./day01 <1|2> <inputfile>\n");
        return 1;
    }

    if (strcmp(argv[1], "1") == 0) {
        printf("\nSum: %d\n", part1(argv[2]));
    } else if (strcmp(argv[1], "2") == 0) {
        printf("\nSum: %d\n", part2(argv[2]));
    } else {
        fprintf(stderr, "Usage: ./day01 <1|2> <inputfile>\n");
        return 1;
    }

    return 0;
}
