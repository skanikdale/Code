#include "stdafx.h"

int findLen(char* string)
{
  int i = 0;

  while(string[i] != '\0')
  {
    i++;
  }

  return i;
}

void swapChar(int nfirst, int nSecond, char* inString)
{
  char temp = {'\0'};

  temp = inString[nfirst];
  inString[nfirst] = inString[nSecond];
  inString[nSecond] = temp;
}

char* reverseString(char* inString)
{
  int nLen = strlen(inString);

  // Swap characters
  for(int i = 0; i < ((nLen +1) / 2); i++)
  {
    swapChar(i, ((nLen -1) - i), inString);
  }

  return inString;
}

bool findCharacter(char* inString, char findChar)
{
  int i = 0; 

  while(inString[i] != '\0')
  {
    if(inString[i] == findChar)
      return true;
    i++;
  }

  return false;
}

char* concantateString(char* tempString, char* revString)
{
  int i;
  int len1 = findLen(tempString);
  int len2 = findLen(revString);
  int len3 = len1 + len2;
  char* outString = (char*) malloc(sizeof(char) * len3);

  int temp = strlen(outString);

  for(i = 0; i < len1; i++)
  {
    outString[i] = tempString[i];
  }

  for(i = 0; i < len2; i++)
  {
    outString[len1 + i] = revString[i];
  }

  outString[len1 + i] = '\0';

  temp = findLen(outString);

  return outString;
}

void concatenate_string(char *original, char *add)
{
   while(*original)
      original++;
 
   while(*add)
   {
      *original = *add;
      add++;
      original++;
   }
   *original = '\0';
}

int check_anagram(char a[], char b[])
{
   int first[26] = {0}, second[26] = {0}, c = 0;
 
   while (a[c] != '\0')
   {
      first[a[c]-'a']++;
      c++;
   }
 
   c = 0;
 
   while (b[c] != '\0')
   {
      second[b[c]-'a']++;
      c++;
   }
 
   for (c = 0; c < 26; c++)
   {
      if (first[c] != second[c])
         return 0;
   }
 
   return 1;
}

void reverse(char* str)
{
  char tmp;
  char* end = str;

  if(str)
  {
    while(*end)
      ++end;

    --end;

    while(str < end)
    {
      tmp = *str;
      *str++ = *end;
      *end-- = tmp;
    }
  }

}


bool areAllUniqueChars(char* str)
{
  int nLen = strlen(str);
  int index = 0;
  int alpha [26] = {0};

  if(nLen <= 0)
    return true;

  while(*str)
  {
    int pos = *str++ - 'a';

    if(alpha[pos] == 0)
      alpha[pos] = 1;
    else
      return false;
  }

  return true;
}

// Using bitwise operator to reduce space complexity
bool areAllUniqueChars2(char* str)
{
  int checker = 0;

  while(*str)
  {
    int pos = *str++ - 'a';

    if((checker & (1 << pos)) > 0)
      return false;
    else
      checker |= (1 << pos);
  }

  return true;
}

void removeDuplicateChar(char* str)
{
  int checker = 0, index = 0;

  while(*str)
  {
    int pos = *str - 'a';

    if((checker & (1 << pos)) > 0) // Remove that char
      str[index] = str[index + 1];
    else
      checker |= (1 << pos);

    *str++; index++;
  }

}

/*

The algorithm is as follows:
1. Count the number of spaces during the first scan of the string.
2. Parse the string again from the end and for each character:
» If a space is encountered, store “%20”. 
» Else, store the character as it is in the newly shifted location.

*/

char* ReplaceFun(char str [])
{
  int spaceCount = 0, newLength, i = 0, index;
  int length = strlen(str);

  for (i = 0; i < length; i++) {
    if (str[i] == ' ') {
      spaceCount++;
    }
  }

  newLength = length + spaceCount * 2;
  str[newLength] = '\0';

  char* reStr = (char*)malloc(sizeof(char) * newLength);

  reStr[newLength] = '\0';

  for(i = 0, index = 0; i < length; i++)
  {
     if (str[i] == ' ') 
     {
       reStr[index] = '%';
       reStr[index + 1] = '2';
       reStr[index + 2] = '0';
       index = index + 3;
     }
     else
     {
       reStr[index] = str[i];
       index++;
     }
  }

  

  //for (i = length - 1; i >= 0; i--) 
  //{
  //  if (str[i] == ' ') 
  //  {
  //    str[newLength - 1] = '0';
  //    str[newLength - 2] = '2';
  //    str[newLength - 3] = '%';
  //    newLength = newLength - 3;
  //  }
  //  else
  //  {
  //    str[newLength - 1] = str[i];
  //    newLength = newLength - 1;
  //  }
  //}

  return reStr;
}

/*

Given an image represented by an NxN matrix, where each pixel in the image is 4 
bytes, write a method to rotate the image by 90 degrees. Can you do this in place?

1 2 3 4
5 6 7 8
9 10 11 12
13 14 15 16

13 9 5 1
14 10 6 2 
15 11 7 3
16 12 8 4

*/

void rotate(int matrix [4][4], int n) 
{
  for (int layer = 0; layer < n / 2; ++layer) 
  {
    int first = layer;
    int last = n - 1 - layer;

    for(int i = first; i < last; ++i) {

      int offset = i - first;
      int top = matrix[first][i]; // save top

      // left -> top
      matrix[first][i] = matrix[last-offset][first]; 

      // bottom -> left
      matrix[last-offset][first] = matrix[last][last - offset]; 

      // right -> bottom
      matrix[last][last - offset] = matrix[i][last]; 

      // top -> right
      matrix[i][last] = top; // right <- saved top
    }
  }
}


void stringTest()
{
  char tempString [] = "Sa m ee r";
  char findChar = '4';

  char* revString = (char*)malloc(sizeof(char) * 100);

  //strrev(tempString);
  int a ,b;

  /***************************************************************************/

  int matrix[4] [4];

  matrix[0] [0] = 1;
  matrix[0] [1] = 2;
  matrix[0] [2] = 3;
  matrix[0] [3] = 4;

  matrix[1] [0] = 5;
  matrix[1] [1] = 6;
  matrix[1] [2] = 7;
  matrix[1] [3] = 8;

  matrix[2] [0] = 9;
  matrix[2] [1] = 10;
  matrix[2] [2] = 11;
  matrix[2] [3] = 12;

  matrix[3] [0] = 13;
  matrix[3] [1] = 14;
  matrix[3] [2] = 15;
  matrix[3] [3] = 16;

  rotate(matrix, 4);


  /***************************************************************************/

  //bool isUnique = areAllUniqueChars(tempString);
  //isUnique = areAllUniqueChars2(tempString);

  //removeDuplicateChar(tempString);

  // Write a method to replace all spaces in a string with ‘%20'
  char* temp = ReplaceFun(tempString);

  // 1. Reverse any incoming string.
  revString = reverseString(tempString);

  // Reverse string with pointers
  reverse(tempString);

  // 2. Find char in a string
  bool isCharAvl = findCharacter(tempString, findChar);


  // 3. Find length of a string 
  int nLen = findLen(tempString);

  // 4. Find char from reverse order

  // 5. conctanate 2 strings
  char* conString = concantateString("1", "8");

  // 6. 

  // check anagrams
  int test = check_anagram("ade", "eda");
}

