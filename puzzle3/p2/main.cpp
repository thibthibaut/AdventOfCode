#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

enum criteria { MOST_COMMON, LEAST_COMMON };

constexpr size_t SIZE = 12;

auto find_diagnostic(auto lines, auto criteria) {

    for (int i = 0; i < SIZE; i++) {

        if (lines.size() == 1) {
            return std::stoi(lines[0].c_str(), nullptr, 2);
        }

        auto count_ones =
            std::count_if(lines.begin(), lines.end(),
                          [i](std::string x) { return x[i] == '1'; });

        auto count_zeros = lines.size() - count_ones;

        auto target_value = '?';
        if (count_ones > count_zeros) {
            target_value = (criteria == MOST_COMMON) ? '1' : '0';
        } else if (count_ones == count_zeros) {
            target_value = (criteria == MOST_COMMON) ? '1' : '0';
        } else {
            target_value = (criteria == MOST_COMMON) ? '0' : '1';
        }

        std::vector<std::string> lines_filtered;
        std::copy_if(
            lines.begin(), lines.end(), std::back_inserter(lines_filtered),
            [i, target_value](std::string x) { return x[i] == target_value; });

        lines = lines_filtered;
    }
    return std::stoi(lines[0].c_str(), nullptr, 2);
}

int main() {

    std::ifstream input_file("../input.txt");

    std::vector<std::string> lines;
    std::string value;

    while (input_file >> value) {
        lines.push_back(value);
    }

    int co2_scrubber = find_diagnostic(lines, LEAST_COMMON);
    int oxygen_generator = find_diagnostic(lines, MOST_COMMON);

    std::cout << oxygen_generator * co2_scrubber << std::endl;
}
