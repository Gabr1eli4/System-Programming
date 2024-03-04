#include <stdio.h>

#include <iostream>
#define BUF_SIZE 256
#include <windows.h>

using namespace std;

int main(int argc, char* argv[]) {
  LARGE_INTEGER frequency;
  if (!QueryPerformanceFrequency(&frequency)) {
    cerr << "QueryPerformanceFrequency failed!" << endl;
    return 1;
  }

  FILE *in_file, *out_file;
  char rec[BUF_SIZE];
  size_t bytes_in, bytes_out;
  DWORD BegTik;

  LARGE_INTEGER start, end;
  QueryPerformanceCounter(&start);

  if (argc != 3) {
    printf("used: cpC file1 file2\n");
    return 1;
  }
  in_file = fopen(argv[1], "rb");
  if (in_file == NULL) {
    perror(argv[1]);
    return 2;
  }
  out_file = fopen(argv[2], "w");
  if (out_file == NULL) {
    perror(argv[2]);
    return 3;
  }

  while ((bytes_in = fread(rec, 1, BUF_SIZE, in_file)) > 0) {
    bytes_out = fwrite(rec, 1, bytes_in, out_file);
    if (bytes_out != bytes_in) {
      perror("Error by Write");
      return 4;
    }
  }
  fclose(in_file);
  fclose(out_file);
  QueryPerformanceCounter(&end);
  double elapsedTime = static_cast<double>(end.QuadPart - start.QuadPart) *
                       1000.0 / frequency.QuadPart;
  cout << "Time = " << elapsedTime << endl;

  return 0;
}