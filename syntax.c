#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dicer.h"

struct roll *newRoll(int numRolls, char sign);
struct roll *newInt(int value, char sign);
void insertNewRoll(struct roll ***tail, struct roll **end, int numRolls, char sign);
void insertNewInt(struct roll ***tail, struct roll **end, int numRolls, char sign);

int syntax(char *input, struct roll ***head, int commaCount)
{
    int index = -1, numRolls = 1, rollsPtr = 0;
    int state = 0, encounteredD = 0, encounteredHL = 0;
    char rolls[10], operation = '+', inputChar = '\0';
    struct roll  *end;   //traverses along the LLL chain
    struct roll  **tail; //iterates over head[]

    *head = (struct roll **) calloc(1, commaCount * sizeof(struct roll *));
    
    tail = *head;

    memset(rolls, '\0', 10);

    while(inputChar = input[++index])
    {
        printf("input = %c\n", inputChar);
//        printf("%d) Head = %u\t end = %u\n", __LINE__, (unsigned int) *head, (unsigned int) end);
        if((state == 0) && (inputChar >= '1') && (inputChar <= '9'))
        {
            rolls[rollsPtr++] = inputChar;
            if(rollsPtr > 9)
            {
                fprintf(stderr, "Too many digits in integer!");
                return index;
            }
            state = 1;
        }
        else if((state == 0) && (inputChar == 'd'))
        {
            encounteredD = 1;

            if(rollsPtr > 0)
            {
                numRolls = atoi(rolls);
                rollsPtr = 0;
            }

            insertNewRoll(&tail, &end, numRolls, operation);

            numRolls = 1;
            memset(rolls, '\0', 10);

            state = 2;
        }
        else if((state == 1) && (inputChar == '\0'))
        {
            printf("\nReturning from state 1!\n");
            return 0;
        }
        else if((state == 1) && (inputChar >= '0') && (inputChar <='9'))
        {
            rolls[rollsPtr++] = inputChar;
            state = 1;
        }
        else if((state == 1) && (inputChar == '+' || inputChar == '-' || inputChar == ','))
        {
            if(rollsPtr > 0)
            {
                numRolls = atoi(rolls);
                rollsPtr = 0;
            }
            if(encounteredD) //This means you've hit the modulus
            {
                randNums(end, numRolls); 
                encounteredD = 0;
            }
            else if(encounteredHL) //If the previous thing I saw was an H or L then I dont want to do anything
            {
                encounteredHL = 0;
            }
            else //Then the value is just some int
            {
                insertNewInt(&tail, &end, numRolls, operation);
            }
            if(inputChar == ',')
            {
                tail++;
                operation = '+';
            }
            else
            {
                operation = inputChar;
            }
            
            numRolls = 1;
            memset(rolls, '\0', 10);
            state = 0;
        }
        else if((state == 1) && (inputChar == 'd'))
        {
            encounteredD = 1;

            if(rollsPtr > 0)
            {
                numRolls = atoi(rolls);
                rollsPtr = 0;
            }

            insertNewRoll(&tail, &end, numRolls, operation);

            numRolls = 1;
            memset(rolls, '\0', 10);
            state = 2;
        }
//        else if((state == 1) && (input[index] == '-'))
//        {
//            state = 4;
//        }
        else if((state == 2) && (inputChar >= '1') && (inputChar <= '9'))
        {
            rolls[rollsPtr++] = inputChar;
            state = 3;
        }
        else if((state == 3) && (inputChar == '\0'))
        {
            printf("\nReturning from state 3!\n");
            return 0;
        }
        else if((state == 3) && (inputChar >= '0') && (inputChar <= '9'))
        {
            rolls[rollsPtr++] = inputChar;
            state = 3;
        }

        else if((state == 3) && (inputChar == ','))
        {
            if(rollsPtr > 0)
            {
                numRolls = atoi(rolls);
                rollsPtr = 0;
            }
            if(encounteredD) //This means you've hit the modulus
            {
                randNums(end, numRolls); 
                encounteredD = 0;
            }
            else if(encounteredHL) //If the previous thing I saw was an H or L then I dont want to do anything
            {
                encounteredHL = 0;
            }
            else //Then the value is just some int
            {
                insertNewInt(&tail, &end, numRolls, operation);
            }
            if(inputChar == ',')
            {
                tail++;
                operation = '+';
            }

            numRolls = 1;
            memset(rolls, '\0', 10);
            state = 0;
        }
        else if((state == 3) && (inputChar == '+' || inputChar == '-'))
        {
            if(rollsPtr > 0)
            {
                numRolls = atoi(rolls);
                rollsPtr = 0;
            }
            if(encounteredD) //This means you've hit the modulus
            {
                randNums(end, numRolls); 
                encounteredD = 0;
            }
            else if(encounteredHL) //If the previous thing I saw was an H or L then I dont want to do anything
            {
                encounteredHL = 0;
            }
            else //Then the value is just some int
            {
                insertNewInt(&tail, &end, numRolls, operation);
            }
            
            numRolls = 1;
            memset(rolls, '\0', 10);
            operation = inputChar;
            state = 4;
        }
        else if((state == 4) && ((inputChar == 'L') || (inputChar == 'l') || (inputChar == 'H') || (inputChar == 'h')))
        {
            encounteredHL = 1;
            highLow(end, inputChar, operation);
            state = 5;
        }
        else if((state == 4) && (inputChar >= '1') && (inputChar <='9'))
        {
            rolls[rollsPtr++] = inputChar;
            state = 1;
        }
        else if((state == 4) && (inputChar == 'd'))
        {
            encounteredD = 1;

            if(rollsPtr > 0)
            {
                numRolls = atoi(rolls);
                rollsPtr = 0;
            }

            insertNewRoll(&tail, &end, numRolls, operation);

            numRolls = 1;
            memset(rolls, '\0', 10);
            state = 2;
        }
        else if((state == 5) && (inputChar == '\0'))
        {
            printf("\nReturning from state 5!\n");
            return 0;
        }
        else if((state == 5) && (inputChar == '+' || inputChar == '-' || inputChar == ','))
        {
            if(rollsPtr > 0)
            {
                numRolls = atoi(rolls);
                rollsPtr = 0;
            }
            if(encounteredD) //This means you've hit the modulus
            {
                randNums(end, numRolls); 
                encounteredD = 0;
            }
            else if(encounteredHL) //If the previous thing I saw was an H or L then I dont want to do anything
            {
                encounteredHL = 0;
            }
            else //Then the value is just some int
            {
                insertNewInt(&tail, &end, numRolls, operation);
            }
            if(inputChar == ',')
            {
                tail++;
                operation = '+';
            }
            else
            {
                operation = inputChar;
            }
            
            numRolls = 1;
            memset(rolls, '\0', 10);
            state = 0;
        }
        else
            return index;
    }
    if(state != 5) //If the last character in the input string is not L or H
    {
//        printf("%d) encounteredD = %d\n", __LINE__, encounteredD);
        if(rollsPtr > 0)
        {
            numRolls = atoi(rolls);
            rollsPtr = 0;
        }
        if(encounteredD) //This means you've hit the modulus
        {
            randNums(end, numRolls); 
            encounteredD = 0;
        }
        else //Then the value is just some int
        {
            insertNewInt(&tail, &end, numRolls, operation);
        }
    }
/*
    printf("%d) ----------------------------------\n", __LINE__);
    printf("%d) Syntax *head = %u\t end = %u\n", __LINE__, (unsigned int) *head, (unsigned int) end);
    int i = 0;
    struct roll *cur;
    cur = (*head)[0];
    printf("%d) ", __LINE__);
    while(cur)
    {
        printf("\t");
        for(i = 0; i < cur -> arraySize; ++i)
            printf("array[%d]=%d, ", i, cur -> arrayOfValues[i]);
        cur = cur -> next;
        printf("\n");
    }
*/
    return 0;
}

struct roll *newRoll(int numRolls, char sign)
{
    struct roll *nodePtr;

    nodePtr = (struct roll *) calloc(1, sizeof(struct roll));
    if(nodePtr == NULL)
    {
        fprintf(stderr, "Unable to allocate memory for struct newRoll\n");
    }
    if(sign == '+')
        nodePtr -> sign = 1;
    else
        nodePtr -> sign = -1;
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

struct roll *newInt(int value, char sign)
{
    struct roll *nodePtr;

    nodePtr = (struct roll *) calloc(1, sizeof(struct roll));
    if(nodePtr == NULL)
    {
        fprintf(stderr, "Unable to allocate memory for struct newInt\n");
    }
    if(sign == '+')
        nodePtr -> sign = 1;
    else
        nodePtr -> sign = -1;
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

void insertNewRoll(struct roll ***tail, struct roll **end, int numRolls, char sign)
{
    if(!(**tail))
    {
        (**tail) = newRoll(numRolls, sign);
        *end = (**tail);
    }
    else
    {
        (*end) -> next = newRoll(numRolls, sign);
        *end = (*end) -> next;
    }
}

void insertNewInt(struct roll ***tail, struct roll **end, int numRolls, char sign)
{
   if(!(**tail))
   {
       (**tail) = newInt(numRolls, sign);
       *end = (**tail);
   }
   else
   {
       (*end) -> next = newInt(numRolls, sign);
       *end = (*end) -> next;
   }
}

