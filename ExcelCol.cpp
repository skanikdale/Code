#include "stdafx.h"
#include <stdio.h>
#include <Windows.h>
#include <string>
#include <iostream>


void excel_column_converter(std::string& source)
{
  bool is_alpha = false;

  if (source[0] >= 'A' && source[0] <= 'Z' )
  { 
    is_alpha = true;
  } 
  else if (source[0] >= '0' && source[0] <= '9')
  {       
    is_alpha = false;
  }
  else
  {
    std::cout<<"invalid input" <<std::endl;
  }          

  if (!is_alpha) 
  {
    std::string result = "";
    char *pEnd;
    long number = atoi(source.c_str());
    
    int residual = 0;
    do {
      residual = number % 26;

      char next = 'A'+ (residual - 1); 

      result = std::string(&next, 1) + result;  

      if (number >= 26 && ((number/26) <= 26))
      {
        char last = number/26;
        next = 'A' + (last-1);
        result = std::string(&next, 1) + result;
      }

      number /= 26;
    } while(number >= 26);

    std::cout<< "result for "<<source<< "=" <<result <<std::endl;
  } else {

    int i = 0, sum = 0;

    while(i < source.length() && source[i]>= 'A' && source[i] <= 'Z')
    {
      sum = sum*26 + ((source[i] - 'A') + 1);
      i++;
    }

    std::cout<<"result for "<< source<<"="<< sum<<std::endl;
  }
}