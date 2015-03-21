#include "dicer.h"

//There might be a bug in the way I increment i in the following function
void highLow(struct roll *temp, char hOrL, char operation)
{
    int i = 0, savedIndex = 0, value = 0;
    if(operation == '+')
    {
        if(hOrL == 'H' || hOrL == 'h')
        {
            value = temp->arrayOfValues[i];
            while(++i < temp->arraySize)
            {
                if(temp->arrayOfValues[i] > value)
                    value = temp->arrayOfValues[i];
            }
        }
        else if(hOrL == 'L' || hOrL == 'l')
        {
            value = temp->arrayOfValues[i];
            while(++i < temp->arraySize)
            {
                if(temp->arrayOfValues[i] < value)
                    value = temp->arrayOfValues[i];
            }
        }
        else
        {
            fprintf(stderr, "Did not recieve expected value of 'H' or 'L'!!!\n");
            return;
        }

        temp->addedValue = value;
        return;
    }
    else if(operation == '-')
    {
        if(hOrL == 'H' || hOrL == 'h')
        {
            value = temp->arrayOfValues[i];
            while(++i < temp->arraySize)
            {
                if(temp->arrayOfValues[i] > value)
                {
                    value = temp->arrayOfValues[i];
                    savedIndex = i;
                }
            }
        }
        else if(hOrL == 'L' || hOrL == 'l')
        {
            value = temp->arrayOfValues[i];
            while(++i < temp->arraySize)
            {
                if(temp->arrayOfValues[i] < value)
                {
                    value = temp->arrayOfValues[i];
                    savedIndex = i;
                }
            }
        }
        else
        {
            fprintf(stderr, "Did not recieve expected value of 'H' or 'L'!!!\n");
            return;
        }

        temp->arrayOfValues[savedIndex] = 0;
        return;
    }
    else
    {
        fprintf(stderr, "Did not recieve expected value of '+' or '-'!!!\n");
        return;
    }
}
