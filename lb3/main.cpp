#include <windows.h>

#include <fstream>
#include <iostream>
#include <locale>

#include "PrintMsg.cpp"

using namespace std;

VOID ReportError(LPCTSTR UserMessage, DWORD ExitCode, BOOL PrintErrorMsg) {
  DWORD eMsgLen, LastErr = GetLastError();
  LPTSTR lpvSysMsg;
  HANDLE hStdErr = GetStdHandle(STD_ERROR_HANDLE);

  // PrintMsg(hStdErr, UserMessage);
  if (PrintErrorMsg) {
    eMsgLen = FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL,
        LastErr, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpvSysMsg,
        0, NULL);

    char oemMsg[512];
    CharToOem(lpvSysMsg, oemMsg);
    PrintStrings(hStdErr, _T ("\n"), oemMsg, _T("\n"), NULL);
    HeapFree(GetProcessHeap(), 0, lpvSysMsg);
  }
  // if (ExitCode > 0) {
  //   ExitProcess(ExitCode);
  // } else {
  //   return;
  // }
  return;
}

int main(int argc, char *argv[]) {
  setlocale(LC_ALL, "Russian");
  FILE *file1, *file2, *file3;
  TCHAR buffer[256] = TEXT("Message");
  size_t a = 1;
  char errorMessage[7] = "perror";

  file1 = fopen("test1.txt", "r");
  wcout << L"Пункт 1 - Открытие несуществующего файла" << endl;
  perror(errorMessage);
  ReportError(buffer, 10, TRUE);

  file1 = fopen("onlyRead.txt", "r");
  file2 = fopen("onlyRead.txt", "w");
  wcout << L"Пункт 2 - Открытие файла, используемого другой программной на "
           "чтение, для записи"
        << endl;
  perror(errorMessage);
  ReportError(buffer, 10, TRUE);

  fopen("onlyRead.txt", "w");
  wcout << L"Пункт 3 - Открытие файла с атрибутом 'только для чтения' на запись"
        << endl;
  perror(errorMessage);
  ReportError(buffer, 10, TRUE);

  file1 = fopen("onlyRead.txt", "r");
  const char *data = "Trying to write to a file opened for reading only.";
  fwrite(data, sizeof(char), strlen(data), file1);
  wcout << L"Пункт 4 - Запись в файл, открытый только для чтения" << endl;
  perror(errorMessage);
  ReportError(buffer, 10, TRUE);

  HANDLE hIn = CreateFile(TEXT("test2.txt"), GENERIC_READ, 0, NULL,
                          OPEN_EXISTING, 0, NULL);
  file3 = fopen("test2.txt", "wt");
  fwrite("test", 1, a, file3);
  wcout << L"Пункт 5 - Запись в файл, редактируемой другим приложением" << endl;
  perror(errorMessage);
  ReportError(buffer, 10, TRUE);

  // hIn = CreateFile(TEXT("test2.txt"), GENERIC_READ, 0, NULL, OPEN_EXISTING,
  // 0,
  //                  NULL);
  file3 = fopen("test2.txt", "rt");
  char readBuffer[256];
  fread(readBuffer, 1, 256, file3);
  wcout << L"Пункт 6 - Чтение из файла, редактируемого другой программой"
        << endl;
  perror(errorMessage);
  ReportError(buffer, 10, TRUE);

  file1 = fopen("test2.txt", "rt");
  file2 = fopen("test2.txt", "rt");
  fclose(file2);
  fwrite("test", 1, 3, file1);
  wcout << L"Пункт 7 - Закрытие файла, используемого другой программой" << endl;
  perror(errorMessage);
  ReportError(buffer, 10, TRUE);

  return 0;
}