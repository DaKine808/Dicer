#include "dicer.h"

int syntax(char *input, struct roll ***head, int commaCount)
{
    int index = -1, numRolls = 1, rollsPtr = 0, encounteredD = 0;
    int state = 0;
    char rolls[10], operation = '\0';
    struct roll  *end;   //traverses along the LLL chain
    struct roll  **tail; //iterates over head[]

    *head = (struct roll **) calloc(1, commaCount * sizeof(struct roll *));
    
    tail = *head;

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

            insertNewRoll(&tail, &end, numRolls);

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
        else if((state == 1) && (input[index] == '+' || input[index] == '-' || input[index] == ','))
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
                insertNewInt(&tail, &end, numRolls);
            }
            if(input[index] == ',')
            {
                tail++;
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

            insertNewRoll(&tail, &end, numRolls);

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
                insertNewInt(&tail, &end, numRolls);
            }
            if(input[index] == ',')
            {
                tail++;
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
                insertNewInt(&tail, &end, numRolls);
            }
            
            numRolls = 1;
            memset(rolls, '\0', 10);
            operation = '-';
            state = 4;
        }
        else if((state == 4) && ((input[index] == 'L') || (input[index] == 'l') || (input[index] == 'H') || (input[index] == 'h')))
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

            insertNewRoll(&tail, &end, numRolls);

            numRolls = 1;
            memset(rolls, '\0', 10);
            state = 2;
        }
        else if((state == 5) && (input[index] == '\0'))
        {
            printf("\nReturning from state 5!\n");
            return 0;
        }
        else if((state == 5) && (input[index] == '+' || input[index] == '-' || input[index] == ','))
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
                insertNewInt(&tail, &end, numRolls);
            }
            if(input[index] == ',')
            {
                tail++;
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
            insertNewInt(&tail, &end, numRolls);
        }
    }

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
    return 0;
}
