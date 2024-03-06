#include <windows.h>

#include <iostream>

using namespace std;

int main(int argc, LPTSTR argv[]) {
  SetConsoleCP(CP_UTF8);
  SetConsoleOutputCP(CP_UTF8);
  HANDLE hInFile, hOutFile;

  hOutFile = CreateFile(TEXT("CONOUT$"), GENERIC_READ | GENERIC_WRITE,
                        FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING,
                        0, NULL);

  if (argv[1] == NULL) {
    cout << "Не указано имя файла" << endl;
    return 1;
  }

  hInFile = CreateFile(argv[1], GENERIC_READ, FILE_SHARE_READ, NULL,
                       OPEN_EXISTING, 0, NULL);

  if (hInFile == INVALID_HANDLE_VALUE) {
    cout << "Ошибка открытия файла" << endl;
    return 1;
  }

  char buffer[256];
  DWORD dwRead;

  while (ReadFile(hInFile, buffer, 256, &dwRead, NULL) && dwRead > 0) {
    WriteFile(hOutFile, buffer, dwRead, &dwRead, NULL);
  }

  CloseHandle(hInFile);
  CloseHandle(hOutFile);

  return 0;
}