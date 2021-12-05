#include <iostream>
#include <fstream>



int main(){

  std::ifstream input_file("input.txt");

  int augmented_counter = 0;
  int prev_data_point = -1;
  int data_point;
  while (input_file >> data_point)
  {
    std::cout << data_point;

    if(prev_data_point != -1 && data_point > prev_data_point ){
      augmented_counter++;
      std::cout << " INCREASED\n";
    } 
    else{
      std::cout << " not increased\n";
    }
    prev_data_point = data_point;
  }

  std::cout << augmented_counter << '\n';

}
