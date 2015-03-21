#include "dicer.h"

struct roll *newRoll(int numRolls)
{
    struct roll *nodePtr;

    nodePtr = (struct roll *) calloc(1, sizeof(struct roll));
    if(nodePtr == NULL)
    {
        fprintf(stderr, "Unable to allocate memory for struct newRoll\n");
    }
    nodePtr -> arraySize = numRolls;
    nodePtr -> addedValue = 0;
    nodePtr -> arrayOfValues = (int *) calloc(numRolls, sizeof(int));
    if(nodePtr -> arrayOfValues == NULL)
    {
        fprintf(stderr, "Unable to allocate memory for array of values\n");
    }
    nodePtr -> next = NULL;

    return nodePtr;
}

struct roll *newInt(int value)
{
    struct roll *nodePtr;

    nodePtr = (struct roll *) calloc(1, sizeof(struct roll));
    if(nodePtr == NULL)
    {
        fprintf(stderr, "Unable to allocate memory for struct newInt\n");
    }
    nodePtr -> arraySize = 1;
    nodePtr -> addedValue = 0;
    nodePtr -> arrayOfValues = (int *) calloc(1, sizeof(int));
    if(nodePtr -> arrayOfValues == NULL)
    {
        fprintf(stderr, "Unable to allocate memory for array of values\n");
    }
    nodePtr -> arrayOfValues[0] = value;
    nodePtr -> next = NULL;

    return nodePtr;
}
