#include <windows.h>

#include <iostream>

#define BUF_SIZE 256

using namespace std;

int main(int argc, LPTSTR argv[]) {
  LARGE_INTEGER frequency;
  if (!QueryPerformanceFrequency(&frequency)) {
    cerr << "QueryPerformanceFrequency failed!" << endl;
    return 1;
  }
  HANDLE hIn, hOut;
  DWORD nIn, nOut, count;
  CHAR Buffer[BUF_SIZE];

  if (argc != 3) {
    cout << "Used: cpW file1 file2" << endl;
    return 1;
  }
  hIn = CreateFile(argv[1], GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);
  if (hIn == INVALID_HANDLE_VALUE) {
    cout << "Can't open Input File, Error: " << GetLastError() << endl;
    return 2;
  }

  hOut = CreateFile(argv[2], GENERIC_WRITE, 0, NULL, CREATE_ALWAYS,
                    FILE_ATTRIBUTE_NORMAL, NULL);

  if (hOut == INVALID_HANDLE_VALUE) {
    cout << "Can't open Output File, Error: " << GetLastError() << endl;
    return 3;
  }

  LARGE_INTEGER start, end;
  QueryPerformanceCounter(&start);

  while (ReadFile(hIn, Buffer, BUF_SIZE, &nIn, NULL) && nIn > 0) {
    WriteFile(hOut, Buffer, nIn, &nOut, NULL);
    if (nIn != nOut) {
      cout << "Error by write: " << GetLastError() << endl;
      return 4;
    }
  }

  CloseHandle(hIn);
  CloseHandle(hOut);
  QueryPerformanceCounter(&end);
  double elapsedTime = static_cast<double>(end.QuadPart - start.QuadPart) *
                       1000.0 / frequency.QuadPart;

  cout << "Time = " << elapsedTime << endl;

  return 0;
}