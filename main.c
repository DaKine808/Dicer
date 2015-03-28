/*
 *Note to self: consider using a dynamic array of linked lists, where
 *     an array index indicates a set of rolls ending with a comma.
 *     For example: 2d20+4d6-H,4d6-L
 *     should produce an array of size 2 since there are 2 sets of rolls.
 *     
 *     And each element of a linked list has a pointer to an array of ints
 *     where the array of ints are the values to be summed. This makes 
 *     the problem of subtraction easier since the last roll that was read
 *     will be at the end of the linked list. 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
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

//    printf("commaCount = %d\n", commaCount);
//    printf("%d) input: %s\n", __LINE__, input);
    

    error = syntax(input, &head, commaCount);
    if(error)
    {
        printf("Invalid syntax at character %c!!!!\n", input[error]);
        return -3;
    }

//    printf("%d) ----------------------------------\n", __LINE__);
//    printf("%d) Main head = %u\t head->first = %u\n", __LINE__, (unsigned int) head, (unsigned int) head[0]);
/*
    printf("First roll values: ");
    for(i = 0; i < head[0]->arraySize; ++i)
    {
        printf("%d%s", head[0]->arrayOfValues[i], (i != (head[0]->arraySize) - 1) ? ", " : "\n");
    }
*/
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

