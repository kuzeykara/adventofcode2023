#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

#define N 1000

struct t_conversions {
    long int nums[N/10];
    int count;
};

struct t_map {
    long int *dest_starts;
    long int *source_starts;
    long int *range_lengths;
    int count;
};

struct t_almanac {
    struct t_map *maps;
    long int *seeds;
    int seed_count;
};

struct t_almanac read_file(FILE *);
long int arr_to_int(long int[10], int);
struct t_conversions read_conversions(char *);

long int part1(char *filename) {
    FILE *fp;
    struct t_almanac almanac;
    struct t_map curr_map;
    long int curr_num, min_location = LONG_MAX;

    if ((fp = fopen(filename, "r")) == NULL) {
        fprintf(stderr, "Error opening file %s", filename);
    }
    almanac = read_file(fp);

    // for every seed
    for (int i=0; i<almanac.seed_count; i++) {
        curr_num = almanac.seeds[i];
        for (int j=0; j<7; j++) { // for every map
            curr_map = almanac.maps[j];
            for (int k=0; k<curr_map.count; k++) { // for every pair
                if (curr_map.source_starts[k] <= curr_num && 
                    curr_map.source_starts[k]+curr_map.range_lengths[k] >= curr_num) {
                    curr_num -= curr_map.source_starts[k] - curr_map.dest_starts[k];
                    k=curr_map.count;
                }
            }
        }
        //printf("LOCATION: %ld\n", curr_num);
        if (curr_num < min_location) {
            min_location = curr_num;
        }
    }

    return min_location;
}


int part2(char *filename) {
    FILE *fp;

    if ((fp = fopen(filename, "r")) == NULL) {
        fprintf(stderr, "Error opening file %s", filename);
    }

    printf("Part 2!\n");

    return 0;
}


struct t_almanac read_file(FILE *fp) {
    struct t_almanac almanac;
    struct t_conversions conversions;
    char *buff, currLine[N];
    
    almanac.seeds = malloc(sizeof(long int)*N/10);
    almanac.maps = malloc(sizeof(struct t_map)*7);
    for (int i=0; i<7; i++) {
        almanac.maps[i].dest_starts = malloc(sizeof(long int)*N/10);
        almanac.maps[i].source_starts = malloc(sizeof(long int)*N/10);
        almanac.maps[i].range_lengths = malloc(sizeof(long int)*N/10);
    }
    buff = malloc(sizeof(char) * N);

    fgets(buff, N, fp);
    buff = strtok(buff, ":");
    buff = strtok(NULL, ":");

    // reading seeds
    conversions = read_conversions(buff);
    almanac.seed_count = conversions.count;
    for (int i=0; i<conversions.count; i++) {
        almanac.seeds[i] = conversions.nums[i];
    }

    do {
        fgets(currLine, N, fp);
    } while(strcmp(currLine, "seed-to-soil map:\n"));

    
    almanac.maps[0].count = 0;
    while(strcmp(fgets(currLine, N, fp), "soil-to-fertilizer map:\n")) {
        //seed to soil
        if (strlen(currLine) > 1) {
            conversions = read_conversions(currLine);
            almanac.maps[0].dest_starts[almanac.maps[0].count] = conversions.nums[0];
            almanac.maps[0].source_starts[almanac.maps[0].count] = conversions.nums[1];
            almanac.maps[0].range_lengths[almanac.maps[0].count] = conversions.nums[2];
            almanac.maps[0].count++;
        }
    }
    
    almanac.maps[1].count = 0;
    while(strcmp(fgets(currLine, N, fp), "fertilizer-to-water map:\n")) {
        //soil to fertilizer
        if (strlen(currLine) > 1) {
            conversions = read_conversions(currLine);
            almanac.maps[1].dest_starts[almanac.maps[1].count] = conversions.nums[0];
            almanac.maps[1].source_starts[almanac.maps[1].count] = conversions.nums[1];
            almanac.maps[1].range_lengths[almanac.maps[1].count] = conversions.nums[2];
            almanac.maps[1].count++;
        }
    }

    almanac.maps[2].count = 0;
    while(strcmp(fgets(currLine, N, fp), "water-to-light map:\n")) {
        //fertilizer to water
        if (strlen(currLine) > 1) {
            conversions = read_conversions(currLine);
            almanac.maps[2].dest_starts[almanac.maps[2].count] = conversions.nums[0];
            almanac.maps[2].source_starts[almanac.maps[2].count] = conversions.nums[1];
            almanac.maps[2].range_lengths[almanac.maps[2].count] = conversions.nums[2];
            almanac.maps[2].count++;
        }
    }

    almanac.maps[3].count = 0;
    while(strcmp(fgets(currLine, N, fp), "light-to-temperature map:\n")) {
        //water to light
        if (strlen(currLine) > 1) {
            conversions = read_conversions(currLine);
            almanac.maps[3].dest_starts[almanac.maps[3].count] = conversions.nums[0];
            almanac.maps[3].source_starts[almanac.maps[3].count] = conversions.nums[1];
            almanac.maps[3].range_lengths[almanac.maps[3].count] = conversions.nums[2];
            almanac.maps[3].count++;
        }
    }

    almanac.maps[4].count = 0;
    while(strcmp(fgets(currLine, N, fp), "temperature-to-humidity map:\n")) {
        //light to temperature
        if (strlen(currLine) > 1) {
            conversions = read_conversions(currLine);
            almanac.maps[4].dest_starts[almanac.maps[4].count] = conversions.nums[0];
            almanac.maps[4].source_starts[almanac.maps[4].count] = conversions.nums[1];
            almanac.maps[4].range_lengths[almanac.maps[4].count] = conversions.nums[2];
            almanac.maps[4].count++;
        }
    }

    almanac.maps[5].count = 0;
    while(strcmp(fgets(currLine, N, fp), "humidity-to-location map:\n")) {
        //temperature to humidity
        if (strlen(currLine) > 1) {
            conversions = read_conversions(currLine);
            almanac.maps[5].dest_starts[almanac.maps[5].count] = conversions.nums[0];
            almanac.maps[5].source_starts[almanac.maps[5].count] = conversions.nums[1];
            almanac.maps[5].range_lengths[almanac.maps[5].count] = conversions.nums[2];
            almanac.maps[5].count++;
        }
    }

    almanac.maps[6].count = 0;
    while(fgets(currLine, N, fp) != NULL) {
        //humidity to location
        if (strlen(currLine) > 1) {
            conversions = read_conversions(currLine);
            almanac.maps[6].dest_starts[almanac.maps[6].count] = conversions.nums[0];
            almanac.maps[6].source_starts[almanac.maps[6].count] = conversions.nums[1];
            almanac.maps[6].range_lengths[almanac.maps[6].count] = conversions.nums[2];
            almanac.maps[6].count++;
        }
    }

    return almanac;
}


long int arr_to_int(long int arr[10], int digits) {
    long int result = 0;

    for (int i=0; i<digits; i++) {
        result = result*10 + arr[i];
    }

    return result;
}


struct t_conversions read_conversions(char *line) {
    struct t_conversions conversions;
    int digitCount, c=0;
    long int digits[10];
    char *buff;

    // WARNING: bad code ahead!
    buff = strtok(line, " ");
    while (buff != NULL) {
        digitCount = strlen(buff);
        for (int i=0; i<digitCount; i++) {
            if (buff[i] == '\n') {
                digitCount--;
            } else {
                digits[i] = buff[i] - '0';
            }
        }
        conversions.nums[c] = arr_to_int(digits, digitCount);
        c++;
        buff = strtok(NULL, " ");
    }
    conversions.count = c;

    return conversions;
}


int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <1|2> <inputfile>\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "1") == 0) {
        printf("Result: %ld\n", part1(argv[2]));
    } else if (strcmp(argv[1], "2") == 0) {
        printf("Result: %d\n", part2(argv[2])); 
    } else {
        fprintf(stderr, "Usage: %s <1|2> <inputfile>\n", argv[0]);
        return 1;
    }

    return 0;
}
