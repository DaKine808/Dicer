struct roll{
    int arraySize, sign, addedValue;
    int *arrayOfValues;
    struct roll *next;
};

void cleanSpaces(char *input, int len);
void randNums(struct roll *temp, int modulus);
void displayRolls(struct roll ***head, int commaCount);
int countCommas(char *input);
void sumRolls(struct roll ***head, int commaCount);
void deleteAll(struct roll ***head, int commaCount);

void highLow(struct roll *temp, char hOrL, char operation);
int syntax(char *input, struct roll ***head, int commaCount);
