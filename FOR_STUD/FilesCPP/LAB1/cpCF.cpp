// cpCF.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>

int main (int argc, LPTSTR argv [])
{
	printf("Hello World!\n");

   DWORD count;
   if (argc != 3) {
     printf("Used: cpCF file1 file2\n");
     return 1;
   }
   count = GetTickCount();
   if (!CopyFile (argv[1], argv[2], FALSE) ) {
     printf("Error CopyFile: %x\n", GetLastError() );
     return 2;
   }
   count = GetTickCount() - count;
   printf("DeltaTime = %d", count);
   return 0;
}



