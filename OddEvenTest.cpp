#include "stdafx.h"
#include <stdio.h>
#include <Windows.h>
#include <iostream>

int arr[17];

DWORD WINAPI PrintOdd(LPVOID Param)
{ 
  HANDLE* Mutex = (HANDLE*) Param;

  for(int i = 1, count =0; i <= 5; )
  {
    wchar_t buffer[256];
    wsprintfW(buffer, L"%d", i);

    // Acquire the lock
    WaitForSingleObject(*Mutex, INFINITE); 
  
   ::MessageBox(NULL, buffer , L"Odd Dlg title", MB_OK);
   arr[count++] = i;

   ReleaseMutex(*Mutex); 

    i = i+ 2;
  }

  return 0; 
}

DWORD WINAPI PrintEven(LPVOID Param)
{ 
  HANDLE* Mutex = (HANDLE*) Param;

  for(int i = 0, count = 7; i <= 6;)
  {
    wchar_t buffer[256];
    wsprintfW(buffer, L"%d", i);

    WaitForSingleObject(*Mutex, INFINITE); 

   ::MessageBox(NULL, buffer , L"Even Dlg title", MB_OK);
   arr[count++] = i;

   ReleaseMutex(*Mutex); 

    i = i+ 2;
  }

  return 0; 
}

void oddEvenTest()
{
  DWORD Threadid; 
  HANDLE ThreadHandle1, ThreadHandle2; 
  HANDLE Mutex1; 
  
  Mutex1 = CreateMutex(NULL, FALSE, NULL); 
  
  ThreadHandle2 = CreateThread( 
                              NULL,
                              0, 
                              PrintEven, // thread function 
                              &Mutex1, 
                              0, 
                              &Threadid); 

  ThreadHandle1 = CreateThread( 
                              NULL,
                              0, 
                              PrintOdd, // thread function 
                              &Mutex1, 
                              0, 
                              &Threadid); 

  WaitForSingleObject(ThreadHandle1, INFINITE); 
  WaitForSingleObject(ThreadHandle2, INFINITE); 
  
  for(int j = 0; j < 7; j++)
  {
    int temp = arr[j];
  }
}


