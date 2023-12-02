#include <stdlib.h>
#include <stdio.h>
#include <string.h>


void part1(char *filename) {
    printf("Part 1!\n");
}


void part2(char *filename) {
    printf("Part 2!\n");
}


int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <1|2> <inputfile>\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "1") == 0) {
        part1(argv[2]);
    } else if (strcmp(argv[1], "2") == 0) {
        part2(argv[2]);
    } else {
        fprintf(stderr, "Usage: %s <1|2> <inputfile>\n", argv[0]);
        return 1;
    }

    return 0;
}
