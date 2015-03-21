#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct roll{
    int arraySize, addedValue;
    int *arrayOfValues;
    struct roll *next;
};

int syntax(char *input, struct roll ***head, int commaCount);
void cleanSpaces(char *input, int len);
void randNums(struct roll *temp, int modulus);
void highLow(struct roll *temp, char hOrL, char operation);
struct roll *newRoll(int numRolls);
struct roll *newInt(int value);
void insertNewRoll(struct roll ***tail, struct roll **end, int numRolls);
void insertNewInt(struct roll ***tail, struct roll **end, int numRolls);
void displayRolls(struct roll ***head, int commaCount);
int countCommas(char *input);
