#include <array>
#include <fstream>
#include <iostream>

int main() {

    constexpr size_t SIZE = 12;

    std::ifstream input_file("input.txt");

    std::array<int, SIZE> counts = {0};

    std::string value;
    int total = 0;
    while (input_file >> value) {

        for (int i = 0; i < SIZE; i++) {
            if (value[i] == '1') {
                counts[i]++;
            }
        }
        total++;
    }

    int gama_rate = 0;
    int epsilon_rate = 0;

    for (int i = 0; i < SIZE; i++) {

        gama_rate <<= 1;
        epsilon_rate <<= 1;

        if (counts[i] > total / 2) {
            gama_rate |= 1;
        } else {
            epsilon_rate |= 1;
        }
        std::cout << i << ':' << counts[i] << "   " << gama_rate << " "
                  << epsilon_rate << std::endl;
    }

    std::cout << gama_rate * epsilon_rate << std::endl;
}
