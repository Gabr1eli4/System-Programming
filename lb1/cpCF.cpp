#include <windows.h>

#include <iostream>

using namespace std;

int main(int argc, LPTSTR argv[]) {
  LARGE_INTEGER frequency;
  if (!QueryPerformanceFrequency(&frequency)) {
    cout << "QueryPerformanceFrequency failed!" << endl;
    return 1;
  }

  LARGE_INTEGER start, end;
  QueryPerformanceCounter(&start);
  if (!CopyFile(argv[1], argv[2], FALSE)) {
    return 2;
  }

  QueryPerformanceCounter(&end);
  double elapsedTime = static_cast<double>(end.QuadPart - start.QuadPart) *
                       1000.0 / frequency.QuadPart;
  cout << "Time = " << elapsedTime << endl;

  return 0;
}