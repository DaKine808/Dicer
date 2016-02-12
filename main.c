/*
 * NOTE: Dicer currently only takes command line arguments!
 *
 * Dicer is D&D style dice rolling program where you can
 * specify the number of times you wish to roll a die and
 * whether you want to add or subtract another roll or the 
 * lowest/highest value rolled. You may also comma seperate
 * multiple instances of rolls.
 * 
 * Example: 4d6 - L, 2d20 + d7 - H, 20 - 6
 * 
 * The output will be 3 comma seperated results.
 */

#include "dicer.h"

int main(int argc, char* argv[])
{
    int error = 0, commaCount = 0, i = 0;
    char *input;
    struct roll **head;
    srand(time(NULL));

    if(argc < 2)
    {
        printf("No arguments provided. Program is exiting.\n");
        return -1;
    }
    else if(argc > 2)
    {
        int arglen = 0, j = 0, k = 0;
        
        for(i = 1; i < argc; ++i)
            arglen += strlen(argv[i]);
        arglen++;

        input = (char *) calloc(1, arglen * sizeof(char));
        
        for(i = 1, j = 0; i < argc; ++i)
        {
            for(k = 0; k < strlen(argv[i]); ++k, ++j)
                input[j] = argv[i][k];
        }
        
        input[arglen-1] = '\0';
    }
    else
    {
        input = argv[1];
        cleanSpaces(input, strlen(input));
    }

    commaCount = countCommas(input);

    error = syntax(input, &head, commaCount);
    if(error)
    {
        if(error < 0)
            error = 0;
        printf("Invalid syntax at character \'%c\' !!!!\n", input[error]);
        return -3;
    }

    displayRolls(&head, commaCount);
    sumRolls(&head, commaCount);
    deleteAll(&head, commaCount);
    free(head);
    if(input != argv[1])
    {
        free(input);
    }

    return 0;
}

