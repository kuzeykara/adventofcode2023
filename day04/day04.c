#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define N 1000

struct t_scratch_card {
    int id;
    int winningNumCount;
    int winningNumbers[N/2];
    int ownedNumCount;
    int ownedNumbers[N/2];
};

struct t_scratch_card read_scratch(char *);
int find_matches(struct t_scratch_card);
int calculate_points(int);

int part1(char *filename) {
    FILE *fp;
    char currLine[N];
    int sum=0, matches;
    struct t_scratch_card currCard;

    if ((fp = fopen(filename, "r")) == NULL) {
        fprintf(stderr, "Error opening file %s", filename);
    }

    while (fgets(currLine, N, fp)) {
        currCard = read_scratch(currLine);
        matches = find_matches(currCard);
        sum += calculate_points(matches);
    }

    return sum;
}


int part2(char *filename) {
    FILE *fp;
    char currLine[N];
    int sum=0, matches, card_copies[N/2], cardCount=0;
    struct t_scratch_card currCard;

    if ((fp = fopen(filename, "r")) == NULL) {
        fprintf(stderr, "Error opening file %s", filename);
    }

    for (int i=0; i<N/2; i++) {
        card_copies[i] = 1;
    }

    while (fgets(currLine, N, fp)) {
        currCard = read_scratch(currLine);
        cardCount++;
        // find matches and create copies FOR EACH COPY
        for (int j=0; j<card_copies[currCard.id]; j++) {
            matches = find_matches(currCard);
            for (int i=1; i<matches+1; i++) {
                card_copies[cardCount+i]++;
            }
        }
    }

    for (int i=1; i<cardCount+1; i++) {
        sum += card_copies[i];
    }

    return sum;
}


int calculate_points(int matches) {
    int points=0;

    if (matches > 0) {
        points = 1;
        for (int i=1; i<matches; i++) {
            points *= 2;
        }
    }

    return points;
}


int find_matches(struct t_scratch_card card) {
    int matches = 0;

    for (int i=0; i<card.ownedNumCount; i++) {
        for (int j=0; j<card.winningNumCount; j++) {
            if (card.ownedNumbers[i] == card.winningNumbers[j]) {
                // MATCH!
                matches++;
            }
        }
    }

    return matches;
}


struct t_scratch_card read_scratch(char *line) {
    struct t_scratch_card card;
    char *buff1, *buff2, *num;
    int winC=0, ownC=0;

    buff1 = strtok(line, ":");
    buff2 = strtok(NULL, ":");
    
    buff1 = strtok(buff1, " ");
    buff1 = strtok(NULL, " ");
    sscanf(buff1, "%d", &card.id);

    buff1 = strtok(buff2, "|");
    buff2 = strtok(NULL, "|");
    
    num = strtok(buff1, " ");
    while (num != NULL) {
        sscanf(num, "%d", &card.winningNumbers[winC]);
        winC++;
        num = strtok(NULL, " ");
    }
    card.winningNumCount = winC;

    num = strtok(buff2, " ");
    while (num != NULL) {
        sscanf(num, "%d", &card.ownedNumbers[ownC]);
        ownC++;
        num = strtok(NULL, " ");
    }
    card.ownedNumCount = ownC;

    return card;
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
