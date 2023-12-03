#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define N 1000


int is_digit(char);
int check_vicinity(char[][N], char[][N], int, int, int);
int check_boundries(int, int, int, int);
int arr_to_int(int[10], int);

int part1(char *filename) {
    FILE *fp;
    char map[N][N], foundNumberPos[N][N];
    int sum=0, lineC=0, lineLength, digitNum=0, numberArr[10], x, y;

    if ((fp = fopen(filename, "r")) == NULL) {
        fprintf(stderr, "Error opening file %s", filename);
    }

    // map the map to 2d array
    while(fgets(map[lineC], N, fp) != NULL) {
        lineC++;
    }
    lineLength = strlen(map[0]) - 1; // need to exclude the new line character

    for (int i=0; i<lineC; i++) {
        for (int k=0; k<=lineLength; k++) {
            // finding the positions of the numbers (all digits)
            if (is_digit(map[i][k])) {
                sprintf(foundNumberPos[digitNum], "%d %d", i, k);
                digitNum++;
            } else {
                if (digitNum!=0) {
                    // NUMBER END FOUND
                    if (check_vicinity(map, foundNumberPos, digitNum, lineC, lineLength)) {
                        // ELIGIBLE NUMBER FOUND
                        // extracting the number
                        for (int j=0; j<digitNum; j++) {
                            sscanf(foundNumberPos[j], "%d %d", &y, &x);
                            numberArr[j] = map[y][x] - '0';
                        }
                        sum += arr_to_int(numberArr, digitNum);
                    }

                    digitNum=0;
                }
            }
        }
    }

    return sum;
}


void part2(char *filename) {
    FILE *fp;

    if ((fp = fopen(filename, "r")) == NULL) {
        fprintf(stderr, "Error opening file %s", filename);
    }

    printf("Part 2!\n");
}


int check_vicinity(char map[][N], char numPositions[][N], int numLength,
                    int lineC, int lineLength) {
    int y, x;

    for (int i=0; i<numLength; i++) {
        sscanf(numPositions[i], "%d %d", &y, &x);

        // left
        if (check_boundries(x-1, y, lineLength, lineC)) {
            if (map[y][x-1] != '.' && !is_digit(map[y][x-1])) {
                return 1;
            }
        }
        // right
        if (check_boundries(x+1, y, lineLength, lineC)) {
            if (map[y][x+1] != '.' && !is_digit(map[y][x+1])) {
                return 1;
            }
        }
        // top
        if (check_boundries(x, y-1, lineLength, lineC)) {
            if (map[y-1][x] != '.' && !is_digit(map[y-1][x])) {
                return 1;
            }
        }
        // bottom
        if (check_boundries(x, y+1, lineLength, lineC)) {
            if (map[y+1][x] != '.' && !is_digit(map[y+1][x])) {
                return 1;
            }
        }
        // top-right
        if (check_boundries(x+1, y-1, lineLength, lineC)) {
            if (map[y-1][x+1] != '.' && !is_digit(map[y-1][x+1])) {
                return 1;
            }
        }
        // top-left
        if (check_boundries(x-1, y-1, lineLength, lineC)) {
            if (map[y-1][x-1] != '.' && !is_digit(map[y-1][x-1])) {
                return 1;
            }
        }
        // bottom-left
        if (check_boundries(x-1, y+1, lineLength, lineC)) {
            if (map[y+1][x-1] != '.' && !is_digit(map[y+1][x-1])) {
                return 1;
            }
        }
        // bottom-right
        if (check_boundries(x+1, y+1, lineLength, lineC)) {
            if (map[y+1][x+1] != '.' && !is_digit(map[y+1][x+1])) {
                return 1;
            }
        }
    }

    return 0;
}


int is_digit(char c) {
    if (c>=48 && c<=57) {
        return 1;
    }
    return 0;
}


int check_boundries(int x, int y, int lineLength, int lineC) {
    if (x<0 || y<0 || x>=lineLength || y>=lineC) {
        return 0;
    }

    return 1;
}


int arr_to_int(int arr[10], int digits) {
    int result = 0;

    for (int i=0; i<digits; i++) {
        result = result*10 + arr[i];
    }

    return result;
}


int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <1|2> <inputfile>\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "1") == 0) {
        printf("Sum: %d\n" , part1(argv[2]));
    } else if (strcmp(argv[1], "2") == 0) {
        part2(argv[2]);
    } else {
        fprintf(stderr, "Usage: %s <1|2> <inputfile>\n", argv[0]);
        return 1;
    }

    return 0;
}
