#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <unordered_map>
#include <utility>
#include <vector>

#define RESET "\033[0m"
#define RED "\033[31m" /* Red */

void find_bassin(auto low_point, const auto &height_map, auto &bassin_map,
                 int label, int previous_value);

int main() {

    std::vector<std::string> colors = {"\033[30m", "\033[31m", "\033[32m",
                                       "\033[33m", "\033[34m", "\033[35m",
                                       "\033[36m", "\033[37m"};

    std::ifstream input_file("../input.txt");

    std::string line;

    std::vector<std::vector<int>> height_map;

    std::vector<std::vector<int>> bassin_map;

    while (std::getline(input_file, line)) {

        std::vector<int> row;

        std::vector<int> bassin_row;

        std::transform(line.begin(), line.end(), std::back_inserter(row),
                       [](const char c) { return c - '0'; });

        std::transform(line.begin(), line.end(), std::back_inserter(bassin_row),
                       [](const char c) { return 0; });

        height_map.push_back(row);

        bassin_map.push_back(bassin_row);
    }

    std::vector<std::pair<int, int>> low_points;

    for (int row = 0; row < height_map.size(); row++) {
        for (int col = 0; col < height_map[0].size(); col++) {
            auto val = height_map[row][col];

            int up = 10;
            int down = 10;
            int left = 10;
            int right = 10;

            if (row > 0) {
                up = height_map[row - 1][col];
            }
            if (row < height_map.size() - 1) {
                down = height_map[row + 1][col];
            }
            if (col > 0) {
                left = height_map[row][col - 1];
            }
            if (col < height_map[0].size() - 1) {
                right = height_map[row][col + 1];
            }

            if (val < up && val < down && val < right && val < left) {

                low_points.push_back(std::make_pair(row, col));
                std::cout << RED << val << RESET;
            } else {
                std::cout << val;
            }
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;

    // Run through all low-points
    int bassin_label = 1;
    for (const auto lp : low_points) {

        int fake_lp_value = height_map[lp.first][lp.second] - 1;

        find_bassin(lp, height_map, bassin_map, bassin_label, fake_lp_value);

        bassin_label++;
    }

    // Display bassin map
    for (int row = 0; row < bassin_map.size(); row++) {
        for (int col = 0; col < bassin_map[0].size(); col++) {

            auto label = bassin_map[row][col];
            if (label == 0) {
                std::cout << RED << '*' << RESET;
            } else {
                char disp = (bassin_map[row][col] % 52) + 'A';
                std::cout << colors[bassin_map[row][col] % 8] << disp << RESET;
            }
        }
        std::cout << std::endl;
    }

    // Count labels in bassin map
    std::map<int, int> counts;

    for (int row = 0; row < bassin_map.size(); row++) {
        for (int col = 0; col < bassin_map[0].size(); col++) {

            auto label = bassin_map[row][col];

            if (counts.find(label) == counts.end()) {
                counts[label] = 1;
            } else {
                counts[label]++;
            }
        }
    }

    for (const auto &c : counts) {
        std::cout << c.first << ": " << c.second << std::endl;
    }

    std::vector<int> counts_vec;
    std::transform(counts.begin(), counts.end(), std::back_inserter(counts_vec),
                   [](const auto val) { return val.second; });

    std::sort(counts_vec.begin(), counts_vec.end());

    for (const auto &c : counts_vec) {
        std::cout << c << std::endl;
    }
}

void find_bassin(auto low_point, const auto &height_map, auto &bassin_map,
                 int label, int previous_value) {

    auto low_point_value = height_map[low_point.first][low_point.second];
    if (low_point_value <= previous_value)
        return;
    // if( low_point_value != previous_value+1) return;
    if (low_point_value == 9)
        return;

    // update bassin map with label
    bassin_map[low_point.first][low_point.second] = label;

    // Check left:
    if (low_point.second > 0) {
        auto new_low_point =
            std::make_pair(low_point.first, low_point.second - 1);
        find_bassin(new_low_point, height_map, bassin_map, label,
                    low_point_value);
    }
    // Check right:
    if (low_point.second < height_map[0].size() - 1) {
        auto new_low_point =
            std::make_pair(low_point.first, low_point.second + 1);
        find_bassin(new_low_point, height_map, bassin_map, label,
                    low_point_value);
    }
    // Check up:
    if (low_point.first > 0) {
        auto new_low_point =
            std::make_pair(low_point.first - 1, low_point.second);
        find_bassin(new_low_point, height_map, bassin_map, label,
                    low_point_value);
    }
    // Check down:
    if (low_point.first < height_map.size() - 1) {
        auto new_low_point =
            std::make_pair(low_point.first + 1, low_point.second);
        find_bassin(new_low_point, height_map, bassin_map, label,
                    low_point_value);
    }
}
