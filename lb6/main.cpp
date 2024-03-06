#include <locale.h>

#include <filesystem>
#include <iostream>

#include "utils/EvryThng.h"
#include "utils/PrintMsg.cpp"
#include "utils/opitons.h"

using namespace std;
namespace fs = std::filesystem;

// const string dir = "D:/Университет/Системное Программирование/lb6/";
const string dir = fs::current_path().string() + "\\";

void printOptions() {
  cout << "1. Создать файл" << endl;
  cout << "2. Удалить файл" << endl;
  cout << "3. Копировать файл" << endl;
  cout << "4. Переименовать файл" << endl;
  cout << "5. Создать папку" << endl;
  cout << "6. Удалить папку" << endl;
  cout << "7. Копировать папку" << endl;
  cout << "8. Переименовать папку" << endl;
}

void printHelp() {
  cout << "Задание выполнил студент группы ИВТ-41-20 Александров Александр"
       << endl;
}

bool accept(string message) {
  char answer;
  cout << message << "Продолжить? (y/n): ";
  cin >> answer;
  return answer == 'y';
}

int main(int argc, LPTSTR argv[]) {
  SetConsoleCP(CP_UTF8);
  SetConsoleOutputCP(CP_UTF8);
  int task;

  if (argc > 1 && strcmp(argv[1], "-?") == 0) {
    printHelp();
    return 0;
  }

  printOptions();

  while (true) {
    cout << "Введите номер задания: ";
    cin >> task;
    HANDLE hInFile;

    char *fileName = new char[256], *copyFile = new char[256],
         *newFileName = new char[256];
    char *dirName = new char[256], *copyDirName = new char[256],
         *newDirName = new char[256];

    switch (task) {
      case 1:
        /* Создать файл */
        cout << "Введите имя файла: ";
        cin >> fileName;

        hInFile = CreateFile(fileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS,
                             FILE_ATTRIBUTE_NORMAL, NULL);
        if (hInFile != INVALID_HANDLE_VALUE) {
          CloseHandle(hInFile);
          cout << "Файл успешно создан\n" << endl;
          printOptions();
        } else {
          DWORD error = GetLastError();
          cout << "Ошибка при создании файла: " << error << endl;
          printOptions();
        }
        break;
      case 2:
        /* Удалить файл */
        cout << "Введите имя удаляемого файла: ";
        cin >> fileName;

        if (DeleteFile(fileName)) {
          cout << "Файл успешно удален\n" << endl;
          printOptions();
        } else {
          DWORD error = GetLastError();
          cout << "Ошибка при удалении файла: " << error << endl;
          printOptions();
        }
        break;

      case 3:
        /* Копировать файл */
        cout << "Введите имя копируемого файла: ";
        cin >> fileName;

        cout << "Введите имя нового файла: ";
        cin >> copyFile;

        if (CopyFile(fileName, copyFile, FALSE)) {
          cout << "Файл успешно скопирован\n" << endl;
          printOptions();
        } else {
          DWORD error = GetLastError();
          cout << "Ошибка при копировании файла: " << error << endl;
          printOptions();
        }
        break;

      case 4:
        /* Переименовать файл */
        cout << "Введите имя переименовываемого файла: ";
        cin >> fileName;

        cout << "Введите новое имя файла: ";
        cin >> newFileName;

        if (MoveFile(fileName, newFileName)) {
          cout << "Файл успешно переименован\n" << endl;
          printOptions();
        } else {
          DWORD error = GetLastError();
          cout << "Ошибка при переименовании файла: " << error << endl;
          printOptions();
        }
        break;

      case 5:
        /* Создать папку */
        cout << "Введите название папки для создания: ";
        cin >> dirName;

        try {
          string message = "Папка уже существует.";
          cout << "dir - " << dir << endl;
          cout << "dir + dirName = " << dir + dirName << endl;

          if (fs::exists(dir + dirName)) {
            if (accept(message)) {
              fs::create_directory(dir + dirName);
              cout << "Папка успешно создана" << endl;
            }
          } else {
            fs::create_directory(dir + dirName);
          }
          printOptions();
        } catch (const fs::filesystem_error& e) {
          cout << "Ошибка при создании папки: " << e.what() << endl;
          printOptions();
        }
        break;

      case 6:
        /* Удалить папку */
        cout << "Введите названия удаляемой папки: ";
        cin >> dirName;

        try {
          string message =
              "Данное действие удалит папку со всем его содержимым! ";
          bool isAccepted = accept(message);

          if (isAccepted) {
            fs::remove_all(dir + dirName);
            cout << "Папка успешно удалена\n" << endl;
          }
          printOptions();
        } catch (const fs::filesystem_error& e) {
          cout << "Ошибка при удалении папки: " << e.what() << endl;
          printOptions();
        }

        break;

      case 7:
        /* Копировать папку */
        cout << "Введите название копируемой папки: ";
        cin >> dirName;

        cout << "Введите названия новой папки: ";
        cin >> copyDirName;

        try {
          string message = "Папка уже существует.";
          if (fs::exists(dir + copyDirName)) {
            if (accept(message)) {
              fs::remove_all(dir + copyDirName);
              fs::copy(dir + dirName, dir + copyDirName,
                       fs::copy_options::recursive |
                           fs::copy_options::overwrite_existing);
            }
          } else {
            fs::copy(dir + dirName, dir + copyDirName,
                     fs::copy_options::recursive |
                         fs::copy_options::overwrite_existing);
          }
          cout << "Папка успешно скопирована\n" << endl;
          printOptions();
        } catch (const fs::filesystem_error& e) {
          cout << "Ошибка при копировании папки: " << e.what() << endl;
          printOptions();
        }
        break;

      case 8:
        /* Переименовать папку */
        cout << "Введите название переименовываемой папки: ";
        cin >> dirName;

        cout << "Введите новое название папки: ";
        cin >> newDirName;

        try {
          string message = "Папка уже существует.";

          if (fs::exists(dir + newDirName) && accept(message)) {
            break;
          }

          fs::rename(dir + dirName, dir + newDirName);
          cout << "Папка успешно переименована\n" << endl;
          printOptions();
        } catch (const fs::filesystem_error& e) {
          cout << "Ошибка при переименовании папки: " << e.what() << endl;
          printOptions();
        }
        break;

      default:
        cout << "\nНу и на что ты надеялся?" << endl;
        break;
    }
  }

  return 0;
}