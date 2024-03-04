// cpW.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>
//#include <stdio.h>
#define BUF_SIZE 256*256*8

int main (int argc, LPTSTR argv [])
{
	printf("Hello World!\n");

  HANDLE hIn, hOut;
  DWORD  nIn, nOut, count;
  CHAR Buffer [BUF_SIZE];

  CHAR Str [] = "Привет Hello!";
  printf("%s\n", Str);
  CharToOem(Str,Str);
  printf("%s\n", Str); 

  if (argc != 3) {
     printf("Used: cpW file1 file2\n");
     return 1;
  }
  hIn = CreateFile (argv[1], GENERIC_READ, 0, NULL,
                    OPEN_EXISTING, 0, NULL);
  if (hIn == INVALID_HANDLE_VALUE)  {
    printf("Coun't open Input File, Error: %x\n",
            GetLastError() );
    return 2;
  }
  hOut = CreateFile (argv[2], GENERIC_WRITE, 0, NULL,
                    CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
  if (hOut == INVALID_HANDLE_VALUE)  {
    printf("Coun't open Output File, Error: %x\n",
            GetLastError() );
    return 3;
  }
  count = GetTickCount();
  printf("BeginTime = %d\n", count);
  while (ReadFile (hIn, Buffer, BUF_SIZE, &nIn, NULL) && nIn > 0) {
     WriteFile(hOut, Buffer, nIn,  &nOut, NULL);
     if (nIn != nOut) {
       printf("Error by write: %x\n",
            GetLastError() );
       return 4;
     }
  }
  CloseHandle(hIn);
  CloseHandle(hOut);
  printf("EndTime = %d\n", GetTickCount());
  count = GetTickCount() - count;
  printf("DeltaTime = %d\n", count);

  return 0;
}

