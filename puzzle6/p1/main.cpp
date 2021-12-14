#include <array>
#include <fstream>
#include <iostream>
#include <vector>

std::vector<int> update_fishes(auto begin, auto end) {

    std::vector<int> new_fishes;
    while (begin != end) {
        auto val = *begin;
        if (val == 0) {
            *begin = 7;
            new_fishes.push_back(8);
        }
        *begin = *begin - 1;
        begin++;
    }
    return new_fishes;
}

int main() {

    std::ifstream input_file("../input.txt");

    std::vector<int> fishes;
    int val;
    while (input_file >> val) {
        fishes.push_back(val);
    }

    for (int day = 0; day < 80; day++) {

        auto new_fishes = update_fishes(fishes.begin(), fishes.end());
        fishes.insert(fishes.end(), new_fishes.begin(), new_fishes.end());

        std::cout << "after day " << day + 1 << " : "; //<< std::endl;
        // for (const auto &fush : fishes) {
        //     std::cout << fush << ",";
        // }

        auto total = fishes.size();
        std::cout << total;

        std::cout << std::endl;
    }

    return 0;
}
