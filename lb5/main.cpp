#include <iostream>

#include "utils/Asc2Un.cpp"
#include "utils/PrintMsg.cpp"
#include "utils/opitons.h"

#define BUFFER_SIZE 256

using namespace std;

int main(int argc, char* argv[]) {
  char optStr[3] = "-i";

  BOOL bFailIfExists;
  bool isWritenOk;

  DWORD index = Options(argc, argv, optStr, &bFailIfExists, NULL);

  Asc2Un(argv[index], argv[index + 1], bFailIfExists);

  return 0;
}