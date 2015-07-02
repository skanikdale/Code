#include "stdafx.h"
#include <stdio.h>
#include <Windows.h>


DWORD Sum; /* data is shared by the thread */

DWORD WINAPI Summation(LPVOID Param)
{ 
  DWORD Upper = *(DWORD*)Param; 

  for (DWORD i = 0; i <= Upper; i++)
    Sum += i; 

 for (DWORD i = 0; i <= 99999; i++)
   char* temp = (char*) malloc(sizeof(char));
   
  return 0; 
}

void multiThreadingTest()
{
  DWORD Threadid; 
  HANDLE ThreadHandle; 
  int Param = 5 ; 

  ThreadHandle = CreateThread( 
                              NULL, // default security attributes 
                              0, // default stack size 
                              Summation, // thread function 
                              &Param, // parameter to thread function 
                              0, // default creation flags 
                              &Threadid); // returns the thread identifier '

  if(ThreadHandle != NULL)
  {
    // now wait for the thread to finish 
    WaitForSingleObject(ThreadHandle,INFINITE); 

    // close the thread handle 
    CloseHandle(ThreadHandle); 

    printf("surn = %d\n" ,Sum); 
  }
}