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

struct roll{
    int arraySize, addedValue;
    int *arrayOfValues;
    struct roll *next;
};

struct comma{
    struct roll *head;
    struct comma *next;
}

int syntax(int state, char* input, struct roll **head);
void cleanSpaces(char* input, int len);
void randNums(struct roll* temp, int modulus);
void highLow(struct roll* temp, char hOrL, char operation);
struct roll *newRoll(int numRolls);
struct roll *newInt(int value);

int main(int argc, char* argv[])
{
    int error = 0, i = 0;
    struct roll *head = NULL;
    struct roll *cur = NULL;
    srand(time(NULL));    

    if(argc < 2)
    {
        printf("No arguments provided. Program is exiting.\n");
        return -1;
    }
    printf("%d) input: %s\n", __LINE__, argv[1]);
    
    cleanSpaces(argv[1], strlen(argv[1]));

    error = syntax(0, argv[1], &head);
    if(error)
    {
        printf("Invalid syntax at character %c!!!!\n", argv[1][error]);
        return -3;
    }

    printf("\n%d) Head=%u\n", __LINE__, (unsigned int) head);

    cur = head;
    while(cur)
    {
        for(i = 0; i < cur -> arraySize; ++i)
            printf("array[%d]=%d, ", i, cur -> arrayOfValues[i]);
        printf("\n");
        cur = cur -> next;
    }

    return 0;
}

int syntax(int state, char *input, struct roll **head)
{
    int index = -1, numRolls = 1, rollsPtr = 0, encounteredD = 0;
    char rolls[10], operation = '\0';
    struct roll *end;

    end = *head;

    memset(rolls, '\0', 10);

    while(input[++index])
    {
//        printf("%d) Head = %u\t end = %u\n", __LINE__, (unsigned int) *head, (unsigned int) end);
        if((state == 0) && (input[index] >= '1') && (input[index] <= '9'))
        {
            rolls[rollsPtr++] = input[index];
            state = 1;
        }
        else if((state == 0) && (input[index] == 'd'))
        {
            encounteredD = 1;

            if(rollsPtr > 0)
            {
                numRolls = atoi(rolls);
                rollsPtr = 0;
            }

            if(!*head)
            {
                *head = newRoll(numRolls);
                end = *head;
            }
            else
            {
                end -> next = newRoll(numRolls);
                end = end -> next;
            }

            numRolls = 1;
            memset(rolls, '\0', 10);

            state = 2;
        }
        else if((state == 1) && (input[index] == '\0'))
        {
            printf("\nReturning from state 1!\n");
            return 0;
        }
        else if((state == 1) && (input[index] >= '0') && (input[index] <='9'))
        {
            rolls[rollsPtr++] = input[index];
            state = 1;
        }
        else if((state == 1) && (input[index] == '+' || input[index] == ',' || input[index] == '-'))
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
            else //Then the value is just some int
            {
                if(!*head)
                {
                    *head = newInt(numRolls);
                    end = *head;
                }
                else
                {
                    end -> next = newInt(numRolls);
                    end = end -> next;
                }
            }
            
            numRolls = 1;
            memset(rolls, '\0', 10);
            operation = input[index];
            state = 0;
        }
        else if((state == 1) && (input[index] == 'd'))
        {
            encounteredD = 1;

            if(rollsPtr > 0)
            {
                numRolls = atoi(rolls);
                rollsPtr = 0;
            }

            if(!*head)
            {
                *head = newRoll(numRolls);
                end = *head;
            }
            else
            {
                end -> next = newRoll(numRolls);
                end = end -> next;
            }

            numRolls = 1;
            memset(rolls, '\0', 10);
            state = 2;
        }
//        else if((state == 1) && (input[index] == '-'))
//        {
//            state = 4;
//        }
        else if((state == 2) && (input[index] >= '1') && (input[index] <= '9'))
        {
            rolls[rollsPtr++] = input[index];
            state = 3;
        }
        else if((state == 3) && (input[index] == '\0'))
        {
            printf("\nReturning from state 3!\n");
            return 0;
        }
        else if((state == 3) && (input[index] >= '0') && (input[index] <= '9'))
        {
            rolls[rollsPtr++] = input[index];
            state = 3;
        }
        else if((state == 3) && (input[index] == '+' || input[index] == ','))
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
            else //Then the value is just some int
            {
                if(!*head)
                {
                    *head = newInt(numRolls);
                    end = *head;
                }
                else
                {
                    end -> next = newInt(numRolls);
                    end = end -> next;
                }
            }
            
            numRolls = 1;
            memset(rolls, '\0', 10);
            operation = input[index];
            state = 0;
        }
        else if((state == 3) && (input[index] == '-'))
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
            else //Then the value is just some int
            {
                if(!*head)
                {
                    *head = newInt(numRolls);
                    end = *head;
                }
                else
                {
                    end -> next = newInt(numRolls);
                    end = end -> next;
                }
            }
            
            numRolls = 1;
            memset(rolls, '\0', 10);
            operation = '-';
            state = 4;
        }
        else if((state == 4) && ((input[index] == 'L') || (input[index] == 'H')))
        {
            highLow(end, input[index], operation);
            state = 5;
        }
        else if((state == 4) && (input[index] >= '1') && (input[index] <='9'))
        {
            rolls[rollsPtr++] = input[index];
            state = 1;
        }
        else if((state == 4) && (input[index] == 'd'))
        {
            encounteredD = 1;

            if(rollsPtr > 0)
            {
                numRolls = atoi(rolls);
                rollsPtr = 0;
            }

            if(!*head)
            {
                *head = newRoll(numRolls);
                end = *head;
            }
            else
            {
                end -> next = newRoll(numRolls);
                end = end -> next;
            }

            numRolls = 1;
            memset(rolls, '\0', 10);
            state = 2;
        }
        else if((state == 5) && (input[index] == '\0'))
        {
            printf("\nReturning from state 5!\n");
            return 0;
        }
        else if((state == 5) && (input[index] == '+' || input[index] == ',' || input[index] == '-'))
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
            else //Then the value is just some int
            {
                if(!*head)
                {
                    *head = newInt(numRolls);
                    end = *head;
                }
                else
                {
                    end -> next = newInt(numRolls);
                    end = end -> next;
                }
            }
            
            numRolls = 1;
            memset(rolls, '\0', 10);
            operation = input[index];
            state = 0;
        }
        else
            return index;
    }
    if(state != 5) //If the last character in the input string is not L or H
    {
        printf("%d) encounteredD = %d\n", __LINE__, encounteredD);
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
            if(!*head)
            {
                *head = newInt(numRolls);
                end = *head;
            }
            else
            {
                end -> next = newInt(numRolls);
                end = end -> next;
            }
        }
    }
    printf("%d) Syntax *head = %u\t end = %u\n", __LINE__, (unsigned int) *head, (unsigned int) end);
    int i = 0;
    struct roll *cur;
    cur = *head;
    while(cur)
    {
        for(i = 0; i < cur -> arraySize; ++i)
            printf("%d) array[%d]=%d, ", __LINE__, i, cur -> arrayOfValues[i]);
        cur = cur -> next;
    }
    return 0;
}

void cleanSpaces(char* input, int len)
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
    int i = 0, len = temp -> arraySize;
    for(i = 0; i < len; ++i)
    {
        temp -> arrayOfValues[i] = (rand() % modulus) + 1;
    }
}

//There might be a bug in the way I increment i in the following function
void highLow(struct roll* temp, char hOrL, char operation)
{
    int i = 0, savedIndex = 0, value = 0;
    if(operation == '+')
    {
        if(hOrL == 'H')
        {
            value = temp->arrayOfValues[i];
            while(++i < temp->arraySize)
            {
                if(temp->arrayOfValues[i] > value)
                    value = temp->arrayOfValues[i];
            }
        }
        else if(hOrL == 'L')
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
        if(hOrL == 'H')
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
        else if(hOrL == 'L')
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

struct roll *newRoll(int numRolls)
{
    struct roll *nodePtr;

    nodePtr = (struct roll *) calloc(1, sizeof(struct roll));
    if(nodePtr == NULL)
    {
        fprintf(stderr, "Unable to allocate memory for struct\n");
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
        fprintf(stderr, "Unable to allocate memory for struct\n");
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
