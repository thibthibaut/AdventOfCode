#include <algorithm>
#include <fstream>
#include <iostream>
#include <utility>
#include <vector>

typedef enum fold {
    FOLD_UP,
    FOLD_LEFT,
} fold_t;

int main() {

    std::ifstream input_file("../input.txt");

    std::vector<std::pair<fold_t, int>> folds;
    std::vector<std::pair<int, int>> pairs_of_points;

    std::string line;
    while (std::getline(input_file, line)) {

        std::size_t pos;
        pos = line.find("fold along ");
        if (pos != std::string::npos) {
            line.erase(0, pos + 11);
            fold_t fold_type = line[0] == 'x' ? FOLD_LEFT : FOLD_UP;
            pos = line.find("=");
            line.erase(0, pos + 1);
            int fold_direction = std::stoi(line);
            folds.emplace_back(fold_type, fold_direction);

        } else if ((pos = line.find(",")) != std::string::npos) {
            auto pos = line.find(",");
            int x = std::stoi(line.substr(0, pos));
            line.erase(0, pos + 1);
            int y = std::stoi(line);
            auto point = std::make_pair(x, y);
            pairs_of_points.push_back(point);
        }
    }

    auto max_x_ = std::max_element(
        pairs_of_points.begin(), pairs_of_points.end(),
        [](const auto &lhs, const auto &rhs) { return lhs.first < rhs.first; });

    auto max_y_ =
        std::max_element(pairs_of_points.begin(), pairs_of_points.end(),
                         [](const auto &lhs, const auto &rhs) {
                             return lhs.second < rhs.second;
                         });

    auto width = max_x_->first + 1;
    auto height = max_y_->second + 1;
    std::cout << width << " " << height << std::endl;

    // Populate the grid
    std::vector<std::vector<int>> grid;
    for (int y = 0; y < height; y++) {
        std::vector<int> row;
        for (int x = 0; x < width; x++) {
            row.push_back(0);
        }
        grid.push_back(row);
    }

    for (const auto &point : pairs_of_points) {
        grid[point.second][point.first] = 1;
    }

    for (const auto &fold : folds) {
        std::cout << "Applying fold " << fold.first << " " << fold.second
                  << std::endl;

        auto fold_type = fold.first;
        auto fold_line = fold.second;
        if (fold_type == FOLD_UP) {

            for (int y = fold_line + 1; y < height; y++) {
                for (int x = 0; x < width; x++) {
                    if (grid[y][x] == 1) {
                        auto new_y = y - 2 * (y - fold_line);
                        grid[new_y][x] = 1;
                    }
                }
            }
            height = fold_line + 1;
        } else if (fold_type == FOLD_LEFT) {

            for (int y = 0; y < height; y++) {
                for (int x = fold_line + 1; x < width; x++) {
                    if (grid[y][x] == 1) {
                        auto new_x = x - 2 * (x - fold_line);
                        grid[y][new_x] = 1;
                    }
                }
            }
            width = fold_line + 1;
        }

        int count = 0;
        // std::cout << std::endl;
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                // std::cout << grid[y][x];
                if (grid[y][x] == 1)
                    count++;
            }
            // std::cout << std::endl;
        }

        std::cout << "Count " << count << std::endl;
    }

    std::cout << std::endl;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            char show = grid[y][x] ? '#' : ' ';
            std::cout << show;
        }
        std::cout << std::endl;
    }
}
