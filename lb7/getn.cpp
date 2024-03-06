#include <fstream>
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
  if (argc < 2) {
    cout << "Не указано имя файла" << endl;
    return 1;
  }

  if (argc < 3) {
    cout << "Не указана номер строки ОТ которой будет производится чтение"
         << endl;
    return 1;
  }

  if (argc < 4) {
    cout << "Не указана номер строки ДО которой будет производится чтение"
         << endl;
    return 1;
  }

  char* file = argv[1];
  int from = atoi(argv[2]);
  int to = atoi(argv[3]);

  if (from < 0) {
    cout << "Введено отрицательное число" << endl;
    return 0;
  }
  if (to < 0) {
    cout << "Введено отрицательное число" << endl;
    return 0;
  }

  ifstream in(argv[1]);
  string line;
  int currentLine = 0;
  int count = 0;

  if (in.is_open()) {
    while (getline(in, line)) {
      currentLine++;
      if (currentLine >= from && count < to) {
        count++;
        cout << line << endl;
      }
    }
  } else {
    cout << "Ошибка открытия файла" << endl;
    return 1;
  }

  in.close();

  return 0;
}