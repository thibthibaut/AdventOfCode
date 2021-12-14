#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <array>
#include <unordered_map>
#include <math.h>


std::string extract_from(const std::string& base, const std::string& from){

  std::string ret = "";

  for(const auto& b : base){
    bool is_not_diff = false;
    for(const auto& f : from){
      if(b == f){
        is_not_diff = true;
          break;
      }
    }
    if(!is_not_diff) ret += b;
  }

  return ret;
}

int main() {

  std::ifstream input_file("../input.txt");

  int count = 0;
  std::string line;
  int sum = 0;
  while(std::getline(input_file, line)) {

    auto pos = line.find("|");
    auto left_side = line.substr(0, pos-1);
    auto right_side = line.substr(pos+2);

    std::vector<std::string> unique_patterns;

    while ((pos = left_side.find(" ")) != std::string::npos) {
        auto token = left_side.substr(0, pos);
          unique_patterns.emplace_back(token);
        left_side.erase(0, pos + 1);
    }
    unique_patterns.emplace_back(left_side);

    std::sort(unique_patterns.begin(), unique_patterns.end(), 
        [](const auto& lhs, const auto& rhs){return lhs.size() < rhs.size();});


    // Step 1: find c/f 
    std::string cf = "zz" ;
    cf[0] = unique_patterns[0].c_str()[0];
    cf[1] = unique_patterns[0].c_str()[1];

    //std::cout << "Found c/f as : " << cf[0] << ' ' << cf[1] << std::endl;

    // Step 2: find A
    auto seven = unique_patterns[1];

    //auto A = extract_A_from_seven(seven, cf);
    auto A = extract_from(seven, cf);
    //std::cout << "Found A as : " << A << std::endl;
    
    // Step 3: extract b/d from 4
    auto four = unique_patterns[2];

    auto bd = extract_from(four, cf);

    //std::cout << "Found bd as : " << bd << std::endl;
    
    // Step 4: find number 9
    int nine;
    std::string G, e_dirty;
    for(int i = 6; i<9 ; i++){
      auto candidate = unique_patterns[i];

      auto diff = extract_from(candidate, bd+cf+A);

        if( diff.size() == 1){
          G = diff;
          nine = i;
          //std::cout << "found G: " << G << std::endl;
        }else{
          e_dirty = diff;
        }

    }

    auto E = extract_from(e_dirty, G);
    //std::cout << "found E: " << E << std::endl;

    // Step 5: find B
    int zero;
    std::string B, d_dirty;
    for(int i = 6; i<9 ; i++){
      if(i == nine) continue;

      auto candidate = unique_patterns[i];
      auto diff = extract_from(candidate, A+cf+G+E);
        if( diff.size() == 1){
          B = diff;
          zero = i;
          //std::cout << "found B: " << B << std::endl;
        }
        else{
          d_dirty = diff;
        }
    }

    auto D = extract_from(d_dirty, B);
    //std::cout << "found D: " << D << std::endl;


    //Step 6: Find F
    std::string F;
    for(int i = 6; i<9 ; i++){
      if(i == nine) continue;
      if(i == zero) continue;
    
      auto six = unique_patterns[i];
      F = extract_from(six, A+B+D+E+G);
    }
    //std::cout << "found F: " << F << std::endl;


    // Step 7: Find C
    auto C = extract_from(cf, F);
    //std::cout << "found C: " << C << std::endl;


    std::cout << "Solution : " << A+B+C+D+E+F+G << std::endl;
    //break;

    std::unordered_map<char, char> mixup;

    mixup[A.c_str()[0]] = 'a';
    mixup[B.c_str()[0]] = 'b';
    mixup[C.c_str()[0]] = 'c';
    mixup[D.c_str()[0]] = 'd';
    mixup[E.c_str()[0]] = 'e';
    mixup[F.c_str()[0]] = 'f';
    mixup[G.c_str()[0]] = 'g';

    std::unordered_map<std::string, int> string_to_number =
    { {"abcefg", 0},
      {"cf", 1},
      {"acdeg", 2},
      {"acdfg", 3},
      {"bcdf", 4},
      {"abdfg", 5},
      {"abdefg", 6},
      {"acf", 7},
      {"abcdefg", 8},
      {"abcdfg", 9}
    };

    std::cout << "Right side : " << right_side << std::endl;

    std::vector<std::string> outputs;

    while ((pos = right_side.find(" ")) != std::string::npos) {
        auto token = right_side.substr(0, pos);
          outputs.emplace_back(token);
        right_side.erase(0, pos + 1);
    }
    outputs.emplace_back(right_side);

    int power = 3;
    int total = 0;
    for(const auto& outval : outputs){
      //std::cout << outval << ' ';

      std::string demixup = "";
      for(const auto c : outval){
        demixup += mixup[c];
      }

      std::sort(demixup.begin(), demixup.end()); //, [](const auto lfs, const auto rhs){ return lfs < rhs})
      //std::cout << demixup << ' ';

      auto digit = string_to_number[demixup] ;
      //std::cout << digit << ' ';

      total += static_cast<int>(digit * pow(10, power));
      power--;
      //std::cout << total << std::endl;

    }

    sum += total;

  }

  std::cout << "SUM " << sum << std::endl;

  return 0;
}


