#include <windows.h>

#include <iostream>

#include "PrintMsg.cpp"

using namespace std;

int main(int argc, char* argv[]) {
  HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
  if (output == INVALID_HANDLE_VALUE) {
    cout << "Failed to get console output handle." << endl;
    return 1;
  }

  const DWORD bufferSize = 256;
  TCHAR buffer[bufferSize];

  TCHAR pPromtMsg[] = TEXT("Enter message: ");
  ConsolePrompt(pPromtMsg, buffer, bufferSize, false);
  PrintMsg(output, buffer);
  cout << endl;
  ConsolePrompt(pPromtMsg, buffer, bufferSize, true);
  PrintStrings(output, buffer, NULL);
  CloseHandle(output);

  return 0;
}