#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
  if (argc < 2) {
    cout << "Не указано имя файла" << endl;
    return 1;
  }

  ifstream in(argv[1]);
  string line;
  vector<string> lines;

  if (in.is_open()) {
    while (getline(in, line)) {
      lines.push_back(line);
    }
  } else {
    cout << "Ошибка открытия файла" << endl;
    return 1;
  }

  in.close();

  int count = 0;
  for (int i = lines.size() - 1; i >= 0; --i) {
    count++;
    if (count > 10) break;
    cout << count << " " << lines[i] << endl;
  }

  return 0;
}