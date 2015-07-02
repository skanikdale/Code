#include "stdafx.h"
#include <iostream>
#include <list>

// Describe how you could use a single array to implement three stacks.

void threestacksarray()
{

}


// stack implementation using an array
void addElem(int* pInt, int val)
{
  while(*pInt)
  {
    pInt++;
  }

  *pInt = val;
}

int getLastElem(int* pInt)
{
  int val;

  while(*pInt)
  {
    pInt++;
  }

 *pInt--;

  return *pInt;
}

void stackTest()
{
   int n = 10;
   int* pInt = NULL;

   pInt = (int*) malloc(sizeof(int) * n);

   for(int i = 0; i < n; i++)
     pInt[i] = NULL;

   addElem(pInt, 1);
   addElem(pInt, 2);
   addElem(pInt, 3);
   addElem(pInt, 4);
   addElem(pInt, 5);
   addElem(pInt, 544);

   int val = getLastElem(pInt);
}