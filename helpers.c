#include "dicer.h"

void cleanSpaces(char *input, int len)
{
    char *lead = input, *follow = input;

    while(*lead)
    {
        if(*follow != *lead)
            *follow = *lead;
        if(*lead == ' ')
        {
            while(*(++lead) == ' ')
                ;
            *follow = *lead;
        }
        lead++;
        follow++;
    }
    *follow = '\0';
}

void randNums(struct roll *temp, int modulus)
{
    int i = 0, len = temp -> arraySize;
    for(i = 0; i < len; ++i)
    {
        temp -> arrayOfValues[i] = (rand() % modulus) + 1;
    }
}


void displayRolls(struct roll ***head, int commaCount)
{
    int i = 0, j = 0;
    struct roll *bot = NULL;

    for(i = 0; i < commaCount; ++i)
    {
        bot = (*head)[i];
        while(bot)
        {
            printf("(%d)\t", bot -> arraySize);
            for(j = 0; j < bot -> arraySize; ++j)
            {
                printf("%d%s", bot -> arrayOfValues[j], (j != (bot -> arraySize) - 1) ? ", " : "\n");
            }
            bot = bot -> next;
        }
    }
}

int countCommas(char *input)
{
    int count = 0;
    while(*input)
    {
        if(*input == ',')
            count++;
        input++;
    }
    return ++count;
}

void sumRolls(struct roll ***head, int commaCount)
{
    struct roll *bot = NULL;
    int i = 0, j = 0, tempSum = 0, sum = 0;

    for(i = 0; i < commaCount; ++i)
    {
        bot = (*head)[i];
        sum = 0;
        while(bot)
        {
            tempSum = 0;
            for(j = 0; j < bot -> arraySize; ++j)
            {
                tempSum += bot -> arrayOfValues[j];
            }
            tempSum *= bot -> sign;
            tempSum += bot -> addedValue;
            sum += tempSum;
            bot = bot -> next;
        }
        printf("%d%s", sum, (i != commaCount - 1) ? ", " : "\n");
    }
}

void deleteAll(struct roll ***head, int commaCount)
{
    struct roll *bot = NULL, *temp = NULL;
    int i = 0;
    for(i = 0; i < commaCount; ++i)
    {
        bot = (*head)[i];
        temp = bot -> next;
        while(temp)
        {
            free(bot -> arrayOfValues);
            free(bot);
            bot = temp;
            temp = temp -> next;
        }
        free(bot -> arrayOfValues);
        free(bot);
    }
}
