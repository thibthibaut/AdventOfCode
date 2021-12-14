#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <unordered_map>

bool is_oppening(const char c){
  if(c == '{' || c == '[' || c == '(' || c == '<'){
    return true;
  }
  return false;
}

int main() {

  std::ifstream input_file("../input.txt");
  std::string line;

  std::unordered_map<char, char> pairs = {
    {'}', '{'},
    {']', '['},
    {'>', '<'},
    {')', '('},
  };

std::unordered_map<char, int> points =  {
    {')',3},
    {']', 57},
    {'}',1197},
    {'>', 25137 }
};

  int total_points = 0;
  while(std::getline(input_file, line)) {

      std::cout << line << std::endl;

      std::stack<char> stack;

      for (const auto c : line) {
          if (is_oppening(c)) {
              stack.push(c);
          } else {
              auto top = stack.top();
              char closing = pairs[c];
              if (top != closing) {
                  std::cout << "Syntax error: Expected " << closing << " got "
                            << top << std::endl;
                  total_points += points[c];
                  break;
              }
              stack.pop();
          }
      }
  }

  std::cout << "total points: " << total_points << std::endl;
}