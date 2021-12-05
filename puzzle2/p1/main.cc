#include <iostream>
#include <fstream>



int main(){

  std::ifstream input_file("../input.txt");
  
  std::string direction;

  int value;

  int x = 0;
  int y = 0;
  int aim = 0;

  while (input_file >> direction >> value)
  {
    std::cout << direction << ' ' << value << '\n';

    if( direction == "forward" ){
      x += value;
      y += aim*value;
    }else if( direction == "down"){
      aim += value;
    }else if( direction == "up"){
      aim -= value;
    }else{
      throw std::runtime_error("Invalid direction");
    }

  }

  std::cout << ">>>>> " << x * y << '\n';
}
