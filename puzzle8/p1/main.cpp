#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>

int main() {

  std::ifstream input_file("../input.txt");

  int count = 0;
  std::string line;
  while(std::getline(input_file, line)) {

    auto pos = line.find("|");
    line.erase(0, pos + 2);

    while ((pos = line.find(" ")) != std::string::npos) {
      auto str = line.substr(0, pos);
      std::cout << str << "-";

      auto size = str.size();
      if(size == 2 || size == 4 || size == 3 || size == 7){
        count++;
      }


      line.erase(0, pos + 1);
    }

      auto size = line.size();
      if(size == 2 || size == 4 || size == 3 || size == 7){
        count++;
      }

      std::cout << line << std::endl;
  }

  std::cout << "Number : " << count << std::endl;
}
