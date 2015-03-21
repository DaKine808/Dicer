#include "dicer.h"

void insertNewRoll(struct roll ***tail, struct roll **end, int numRolls)
{
    if(!(**tail))
    {
        (**tail) = newRoll(numRolls);
        *end = (**tail);
    }
    else
    {
        (*end) -> next = newRoll(numRolls);
        *end = (*end) -> next;
    }
}

void insertNewInt(struct roll ***tail, struct roll **end, int numRolls)
{
   if(!(**tail))
   {
       (**tail) = newInt(numRolls);
       *end = (**tail);
   }
   else
   {
       (*end) -> next = newInt(numRolls);
       *end = (*end) -> next;
   }
}
