#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define N 1000


struct t_coords {
    int coords[8][2];
};

int is_digit(char);
int check_vicinity(char[][N], char[][N], int, int, int);
int check_boundries(int, int, int, int);
int arr_to_int(int[10], int);
int find_gear_ratio(char[][N], int, int, int, int);
struct t_coords coordsToCheck(int, int, int, int);
int get_num(char[][N], int, int);

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


int part2(char *filename) {
    FILE *fp;
    char map[N][N];
    int sum=0, lineLength, lineC=0;

    if ((fp = fopen(filename, "r")) == NULL) {
        fprintf(stderr, "Error opening file %s", filename);
    }

    // map the map to 2d array
    while(fgets(map[lineC], N, fp) != NULL) {
        lineC++;
    }
    lineLength = strlen(map[0]) - 1; // need to exclude the new line character

    for (int i=0; i<lineC; i++) {
        for (int j=0; j<=lineLength; j++) {
            if (map[i][j] == '*') {
                sum += find_gear_ratio(map, j, i, lineLength, lineC);
            }
        }
    }

    return sum;
}


int find_gear_ratio(char map[][N], int x, int y, int lineLength, int lineC) {
    struct t_coords toCheck;
    int curr_x, curr_y, num, num_length, numArr[10], start_x, full_num, k, found;
    int fullNumArr[8];
    
    toCheck = coordsToCheck(x, y, lineLength, lineC);
    found = 0;
    for (int i=0; i<8; i++) {
        curr_x = toCheck.coords[i][0];
        curr_y = toCheck.coords[i][1];
        num = get_num(map, curr_x, curr_y);
        if ((curr_x != -1 || curr_y != -1) && num != -1) {
            // check its left
            num_length = 1;
            while (check_boundries(curr_x-num_length, curr_y, lineLength, lineC) 
                    && is_digit(map[curr_y][curr_x-num_length])) {
                num_length++;
            }
            start_x = curr_x - num_length + 1;
            // check its right
            k=1;
            while (check_boundries(curr_x+k, curr_y, lineLength, lineC) 
                    && is_digit(map[curr_y][curr_x+k])) {
                num_length++;
                k++;
            }
            // extract the full number and flag any potential duplicates
            for (int a=0; a<num_length; a++) {
                for (int j=0; j<8; j++) {
                    if (toCheck.coords[j][0] == start_x+a &&
                        toCheck.coords[j][1] == curr_y) {
                            toCheck.coords[j][0] = toCheck.coords[j][1] = -1;
                    }
                }
                numArr[a] = get_num(map, start_x+a, curr_y);
            }
            full_num = arr_to_int(numArr, num_length);
            fullNumArr[found] = full_num;
            found++;
        }
    }

    if (found == 2) {
        return fullNumArr[0] * fullNumArr[1];
    }

    return 0;
}


int get_num(char map[][N], int x, int y) {
    if (x == -1 || y == -1) {
        return -1;
    }
    if (is_digit(map[y][x])) {
        return map[y][x] - '0';
    }

    return -1;
}


struct t_coords coordsToCheck(int x, int y, int lineLength, int lineC) {
    struct t_coords to_check;

    for (int i=0; i<8; i++) {
        to_check.coords[i][0] = -1;
        to_check.coords[i][1] = -1;
    }

    if (check_boundries(x-1, y, lineLength, lineC)) { // left
        to_check.coords[3][0] = x-1;
        to_check.coords[3][1] = y;
    }
    if (check_boundries(x+1, y, lineLength, lineC)) { // right
        to_check.coords[4][0] = x+1;
        to_check.coords[4][1] = y;
    }
    if (check_boundries(x, y-1, lineLength, lineC)) { // top
        to_check.coords[1][0] = x;
        to_check.coords[1][1] = y-1;
    }
    if (check_boundries(x, y+1, lineLength, lineC)) { // bottom
        to_check.coords[6][0] = x;
        to_check.coords[6][1] = y+1;
    }
    if (check_boundries(x-1, y-1, lineLength, lineC)) { // top-left
        to_check.coords[0][0] = x-1;
        to_check.coords[0][1] = y-1;
    }
    if (check_boundries(x+1, y-1, lineLength, lineC)) { // top-right
        to_check.coords[2][0] = x+1;
        to_check.coords[2][1] = y-1;
    }
    if (check_boundries(x-1, y+1, lineLength, lineC)) { // bottom-left
        to_check.coords[5][0] = x-1;
        to_check.coords[5][1] = y+1;
    }
    if (check_boundries(x+1, y+1, lineLength, lineC)) { // bottom-right
        to_check.coords[7][0] = x+1;
        to_check.coords[7][1] = y+1;
    }

    return to_check;
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
        printf("Sum: %d\n", part2(argv[2]));
    } else {
        fprintf(stderr, "Usage: %s <1|2> <inputfile>\n", argv[0]);
        return 1;
    }

    return 0;
}
