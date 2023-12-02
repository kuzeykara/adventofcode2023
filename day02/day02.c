#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_LINE 1000


int find_possible(char*);
int is_possible(char *);
int find_power(char*);

int part1(char *filename) {
    FILE *fp;
    char currLine[MAX_LINE];
    int sum = 0;

    if ((fp = fopen(filename, "r")) == NULL) {
        fprintf(stderr, "Error opening file %s", filename);
    }

    while(fgets(currLine, MAX_LINE, fp)) {
        sum += find_possible(currLine);
    }

    fclose(fp);

    return sum;
}


int part2(char *filename) {
    FILE *fp;
    char currLine[MAX_LINE];
    int sum = 0;

    if ((fp = fopen(filename, "r")) == NULL) {
        fprintf(stderr, "Error opening file %s", filename);
    }

    while(fgets(currLine, MAX_LINE, fp)) {
        sum += find_power(currLine);
    }

    fclose(fp);

    return sum;
}


int find_power(char *line) {
    int id, setCount=0, minGreen=0, minRed=0, minBlue=0, cubeCount;
    char linecpy[MAX_LINE], throwaway[MAX_LINE], cubeSets[MAX_LINE][MAX_LINE];
    char *firstPart, *secondPart, *set, *cube, color[6];

    strcpy(linecpy, line);
    firstPart = strtok(linecpy, ":");
    secondPart = strtok(NULL, ":");

    // getting the id
    sscanf(firstPart, "%s %d", throwaway, &id);

    // getting the cube sets
    set = strtok(secondPart, ";");
    while(set != NULL) {
        strcpy(cubeSets[setCount], set);
        setCount++;
        set = strtok(NULL, ";");
    }
    
    // for each set
    for (int i=0; i<setCount; i++) {
        // for each cube group
        cube = strtok(cubeSets[i], ",");
        while(cube != NULL) {
            // get the count and color
            sscanf(cube, "%d %s", &cubeCount, color);
            if (strcmp(color, "red") == 0) {
                if (cubeCount > minRed) {
                    minRed = cubeCount;
                }
            } else if (strcmp(color, "green") == 0) {
                if (cubeCount > minGreen) {
                    minGreen = cubeCount;
                }
            } else if (strcmp(color, "blue") == 0) {
                if (cubeCount > minBlue) {
                    minBlue = cubeCount;
                }
            }
            cube = strtok(NULL, ",");
        }
    }

    return minRed*minGreen*minBlue;
}


int find_possible(char *line) {
    int id, setCount=0;
    char linecpy[MAX_LINE], throwaway[MAX_LINE], cubeSets[MAX_LINE][MAX_LINE];
    char *firstPart, *secondPart, *set, *cube;

    strcpy(linecpy, line);
    firstPart = strtok(linecpy, ":");
    secondPart = strtok(NULL, ":");

    // getting the id
    sscanf(firstPart, "%s %d", throwaway, &id);

    // getting the cube sets
    set = strtok(secondPart, ";");
    while(set != NULL) {
        strcpy(cubeSets[setCount], set);
        setCount++;
        set = strtok(NULL, ";");
    }
    
    // for each set
    for (int i=0; i<setCount; i++) {
        // for each cube group
        cube = strtok(cubeSets[i], ",");
        while(cube != NULL) {
            if (is_possible(cube) == 0) {
                return 0; // impossible!
            }
            cube = strtok(NULL, ",");
        }
    }

    return id;
}


int is_possible(char *group) {
    int count;
    char color[6];

    sscanf(group, "%d %s", &count, color);

    // the bag contains 12 red cubes, 13 green cubes, and 14 blue cubes
    if (strcmp(color, "red") == 0) {
        if (count > 12) {
            return 0;
        }
    } else if (strcmp(color, "green") == 0) {
        if (count > 13) {
            return 0;
        }
    } else if (strcmp(color, "blue") == 0) {
        if (count > 14) {
            return 0;
        }
    }

    return 1;
}


int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <1|2> <inputfile>\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "1") == 0) {
        printf("Sum: %d\n", part1(argv[2]));
    } else if (strcmp(argv[1], "2") == 0) {
        printf("Sum: %d\n", part2(argv[2]));
    } else {
        fprintf(stderr, "Usage: %s <1|2> <inputfile>\n", argv[0]);
        return 1;
    }

    return 0;
}
