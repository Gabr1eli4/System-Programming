#include "EvryThng.h"
#define BUF_SIZE 256

BOOL Asc2Un(LPCTSTR fIn, LPCTSTR fOut, BOOL bFailIfExists)
// Копиpуем файл ASCII в Unicode на базе CopyFile
{
  HANDLE hIn, hOut;
  DWORD fdwOut, nIn, nOut, iCopy;
  CHAR aBuffer[BUF_SIZE];
  WCHAR uBuffer[BUF_SIZE];
  BOOL WriteOk = TRUE;

  hIn = CreateFile(fIn, GENERIC_READ, 0, NULL, OPEN_EXISTING,
                   FILE_ATTRIBUTE_NORMAL, NULL);
  /* Определяем действие CreateFile, если выходной
     файл уже существует */
  fdwOut = bFailIfExists ? CREATE_NEW : CREATE_ALWAYS;
  hOut = CreateFile(fOut, GENERIC_WRITE, 0, NULL, fdwOut, FILE_ATTRIBUTE_NORMAL,
                    NULL);
  WCHAR BOM = 0xFEFF;
  WriteFile(hOut, &BOM, sizeof(WCHAR), &nOut, NULL);
  while (ReadFile(hIn, aBuffer, BUF_SIZE, &nIn, NULL) && nIn > 0 && WriteOk) {
    int nWideChar =
        MultiByteToWideChar(1251, 0, aBuffer, BUF_SIZE, uBuffer, nIn);
    WriteOk = WriteFile(hOut, uBuffer, 2 * nIn, &nOut, NULL);
  }
  CloseHandle(hIn);
  CloseHandle(hOut);
  return WriteOk;
}
