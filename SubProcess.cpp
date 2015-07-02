#include "stdafx.h"
#include <stdio.h>
#include <Windows.h>

void subProcessTest()
{
  STARTUPINFO si; 
  PROCESS_INFORMATION pi; 

  ZeroMemory(&si, sizeof(si));

  si.cb = sizeof(si);

  ZeroMemory(&pi, sizeof(pi));

  LPTSTR szCmdline = _tcsdup(TEXT("C:\\Windows\\Notepad.exe"));

  try
  {

  BOOL temp = CreateProcess(NULL, 
                    szCmdline,
                    NULL, 
                    NULL, // don't inherit thread handle 
                    FALSE, // disable handle inheritance 
                    0, // no creation flags 
                    NULL, // use parent's environment block 
                    NULL, // use parent's existing directory 
                    &si, 
                    &pi);
  {
     fprintf(stderr, "Create Process Failed"); 
     return; 
  }
  }
  catch(char e)
  {

  }

    // parent will wait for the child to complete 
   WaitForSingleObject(pi.hProcess, INFINITE); 

   printf("Child Complete"); 
  
   // close handles 
   CloseHandle(pi.hProcess); 
   CloseHandle(pi.hThread);
}