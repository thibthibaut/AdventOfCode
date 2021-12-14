#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>


#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */


int main() {

  std::ifstream input_file("../input.txt");

  std::string line;

  std::vector<std::vector<int>> height_map;

  while(std::getline(input_file, line)) {

    std::vector<int> row;

    std::transform(line.begin(), line.end(), std::back_inserter(row),
        [](const char c){return c - '0';});


    height_map.push_back(row);
  }

  int total = 0;

  for(int row = 0; row < height_map.size(); row++) {
    for(int col = 0; col < height_map[0].size(); col++){
      auto val = height_map[row][col];

      int up = 10;
      int down = 10; 
      int left = 10; 
      int right = 10; 

      if( row > 0){
        up = height_map[row-1][col];
      }
      if( row < height_map.size() -1 ){
        down = height_map[row+1][col];
      }
      if( col > 0){
        left = height_map[row][col-1];
      }
      if( col < height_map[0].size() -1 ){
        right = height_map[row][col+1];
      }


      if( val < up && 
          val < down &&
          val < right &&
          val < left){

        total += 1+val;
        std::cout << RED << val << RESET;
      }
      else {
        std::cout << val;
      }

    }
    std::cout<< std::endl;
  }


  std::cout << "TOTAL " << total << std::endl;

}
