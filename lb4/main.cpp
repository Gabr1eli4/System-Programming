#include <iostream>

#include "PrintMsg.cpp"
#include "opitons.h"

using namespace std;

#define BUF_SIZE 256

VOID CatFile(HANDLE hInFile, HANDLE hOutFile) {
  DWORD nIn, nOut;
  char Buffer[BUF_SIZE];

  SetConsoleOutputCP(CP_UTF8);

  while (ReadFile(hOutFile, Buffer, BUF_SIZE, &nIn, NULL) && nIn > 0) {
    // WriteConsole(hInFile, Buffer, nIn, &nOut, NULL);
    WriteFile(hInFile, Buffer, nIn, &nOut, NULL);
  }
}

int main(int argc, LPTSTR argv[]) {
  setlocale(0, "Russian");
  HANDLE hInFile;
  char optStr[3] = "-s";

  DWORD index = Options(argc, argv, optStr, NULL);

  hInFile = CreateFile(_T("CONOUT$"), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS,
                       FILE_ATTRIBUTE_NORMAL, NULL);

  if (index == argc) {
    LPCTSTR msg = _T("Введите сообщение: ");
    LPTSTR resp = new TCHAR[31];
    resp[0] = '\0';

    ConsolePrompt(msg, resp, 31, true);
    PrintStrings(hInFile, resp, NULL);
  }

  for (index; index < argc; index++) {
    HANDLE hOutFile =
        CreateFile(argv[index], GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);

    CatFile(hInFile, hOutFile);
  }

  return 0;
}
