// Файл Options.cpp

#include <stdarg.h>

#include "EvryThng.h"

DWORD Options(int argc, LPTSTR argv[], LPCTSTR OptStr, ...)
/* argv - командная строка. Опции, начинающиеся с "-", помещаются в argv[1],
argv[2], ... OptStr - текстовая строка, содержащая все возможные опции во
взаимно-однозначном соответствии с адресом булевых переменных в списке
параметров-переменных (...). Эти флаги устанавливаются тогда и только тогда,
когда символ соответствующей опции встреча-ется в argv[1], argv[2], ...
Возвращаемое значение - индекс в argv первого параметра, не принадлежаще-го к
опциям.  */
{
  va_list pFlagList;
  LPBOOL pFlag;
  bool found;
  int iFlag = 0, iArg;

  va_start(pFlagList, OptStr);
  while ((pFlag = va_arg(pFlagList, LPBOOL)) != NULL &&
         iFlag < (int)_tcslen(OptStr)) {
    *pFlag = FALSE;
    for (iArg = 1; !(*pFlag) && iArg < argc && argv[iArg][0] == '-'; iArg++)
      *pFlag = _memtchr(argv[iArg], OptStr[iFlag], _tcslen(argv[iArg])) != NULL;
    iFlag++;
  }
  va_end(pFlagList);
  for (iArg = 1; iArg < argc && argv[iArg][0] == '-'; iArg++) {
    char opt = (char)argv[iArg][1];
    for (int j = 0; j < (int)_tcslen(OptStr); j++) {
      found = (OptStr[j] == opt);
      if (found) {
        break;
      }
    }
    if (!found) {
      std::cout << "Warning: " << opt << " illegal option" << std::endl;
    }
  }
  return iArg;
}
