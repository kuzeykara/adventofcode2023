#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int part1(char *filename) {
    FILE *fp;

    if ((fp = fopen(filename, "r")) == NULL) {
        fprintf(stderr, "Error opening file %s", filename);
    }

    printf("Part 1!\n");

    return 0;
}


int part2(char *filename) {
    FILE *fp;

    if ((fp = fopen(filename, "r")) == NULL) {
        fprintf(stderr, "Error opening file %s", filename);
    }

    printf("Part 2!\n");

    return 0;
}


int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <1|2> <inputfile>\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "1") == 0) {
        printf("Result: %d\n", part1(argv[2]));
    } else if (strcmp(argv[1], "2") == 0) {
        printf("Result: %d\n", part2(argv[2])); 
    } else {
        fprintf(stderr, "Usage: %s <1|2> <inputfile>\n", argv[0]);
        return 1;
    }

    return 0;
}
