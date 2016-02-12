#include "dicer.h"

void highLow(struct roll *temp, char hOrL, char operation)
{
    int i = 0, savedIndex = 0, value = 0, size = 0;
    int *valPtr = NULL;

    valPtr = temp -> arrayOfValues;
    value  = *valPtr;
    size   = temp -> arraySize;
    
    if(hOrL == 'H' || hOrL == 'h')
    {
        while(++i < size)
        {
            if(*(++valPtr) > value)
            {
                value = *valPtr;
                savedIndex = i;
            }
        }
    }
    else if(hOrL == 'L' || hOrL == 'l')
    {
        while(++i < size)
        {
            if(*(++valPtr) < value)
            {
                value = *valPtr;
                savedIndex = i;
            }
        }
    }
    else
    {
        fprintf(stderr, "Did not recieve expected value of 'H' or 'L'!!!\n");
        return;
    }
    if(operation == '+')
    {
        temp -> addedValue = temp -> arrayOfValues[savedIndex];
        return;
    }
    else if(operation == '-')
    {
        temp->arrayOfValues[savedIndex] = 0;
        return;
    }
    else
    {
        fprintf(stderr, "Did not recieve expected value of '+' or '-'!!!\n");
        return;
    }
}

