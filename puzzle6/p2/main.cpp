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

size_t get_number_fishes_after_some_time(int timer, int days) {

    std::vector<int> fishes = {timer};

    for (int day = 0; day < days; day++) {

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

    return fishes.size();
}

int main() {

    std::ifstream input_file("../input.txt");

    std::vector<int> fishes;
    int val;
    while (input_file >> val) {
        fishes.push_back(val);
    }

    for (int day = 0; day < 80; day++) {

        std::array<int, 7> counts = {0};
        for (int i = 0; i < 7; i++) {
            auto count = std::count(fishes.begin(), fishes.end(), i);
            counts[i] = count;
        }
        for (int i = 2; i < 7; i++) {
            std::cout << i << ':' << counts[i] << std::endl;

            auto nb_fish = get_number_fishes_after_some_time(i, 256);
            auto total = counts[i] * nb_fish;

            std::cout << "TOTAL " << total << std::endl;

            break;
        }

        break;
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

int main() {}