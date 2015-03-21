#include <time.h>
#include "dicer.h"

void cleanSpaces(char *input, int len)
{
    int lead = 0, follow = 0;

    for(lead = 0, follow = 0; lead < len; ++lead, ++follow)
    {
        if(follow != lead)
            input[follow] = input[lead];
        if(input[lead] == ' ')
        {
            while(input[++lead] == ' ')
                ;
            input[follow] = input[lead];
        }
    }

    input[follow] = '\0';

    printf("%d) Clean spaces: %s\n", __LINE__, input);

}

void randNums(struct roll *temp, int modulus)
{
    srand(time(NULL));

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

    bot = (*head)[0];

    printf("%d) ----------------------------------\n", __LINE__);
    printf("%d) Display *head = %u\t bot = %u\n", __LINE__, (unsigned int) *head, (unsigned int) bot);
    
    for(i = 0; i < commaCount; ++i)
    {
        bot = (*head)[i];
        printf("%dth rolls:\n", i);
        while(bot)
        {
            printf("(%d)\t", bot -> arraySize);
            for(j = 0; j < bot -> arraySize; ++j)
            {
                printf("%d%s", bot -> arrayOfValues[j], (j != (bot -> arraySize) - 1) ? ", " : "\n");
            }
            bot = bot -> next;
        }
        printf("End of while(bot)\n");
    }
}

int countCommas(char *input)
{
    int count = 0;
    char *temp = input;
    while(*temp)
    {
        if(*temp == ',')
            count++;
        temp++;
    }
    return ++count;
}
