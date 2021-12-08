#include <array>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>

void update_grid(auto &grid, const auto value) {
    for (int row = 0; row < 5; ++row) {
        for (int col = 0; col < 5; ++col) {
            if (grid[row][col].first == value) {
                grid[row][col].second = true;
            }
        }
    }
}

auto check_grid(const auto &grid) {

    // Check rows
    for (int row = 0; row < 5; ++row) {
        bool test = true;
        for (int col = 0; col < 5; ++col) {
            if (!grid[row][col].second) {
                test = false;
                break;
            }
        }
        if (test)
            return true;
    }

    // Check columns
    for (int col = 0; col < 5; ++col) {
        bool test = true;
        for (int row = 0; row < 5; ++row) {
            if (!grid[row][col].second) {
                test = false;
                break;
            }
        }
        if (test)
            return true;
    }

    return false;
}

auto compute_score(const auto &grid, const auto value) {

    auto sum = 0;
    for (int row = 0; row < 5; ++row) {
        for (int col = 0; col < 5; ++col) {
            if (!grid[row][col].second) {
                sum += grid[row][col].first;
            }
        }
    }
    return sum * value;
}
int main() {

    // A grid is a 2D array of pairs <number, marked>
    typedef std::array<std::array<std::pair<int, bool>, 5>, 5> grid_t;

    std::vector<grid_t> grids;

    std::map<size_t, bool> winning_grids;

    std::ifstream input_file("../input.txt");

    std::string drawing_str;
    input_file >> drawing_str;

    std::vector<int> drawing;
    size_t pos = 0;
    std::string token;
    std::string delimiter = ",";
    while ((pos = drawing_str.find(delimiter)) != std::string::npos) {
        token = drawing_str.substr(0, pos);
        drawing.emplace_back(std::stoi(token.c_str()));
        drawing_str.erase(0, pos + delimiter.length());
    }
    drawing.emplace_back(std::stoi(drawing_str.c_str()));

    while (input_file.peek() != EOF) {
        int val;
        grid_t grid;
        for (int row = 0; row < 5; ++row) {
            for (int col = 0; col < 5; ++col) {
                input_file >> val;
                grid[row][col] = std::make_pair(val, false);
            }
        }
        grids.emplace_back(grid);
    }
    // End of parsing

    grid_t latest_winning_grid;
    int latest_winning_draw;
    for (const auto draw : drawing) {
        // Update all grids
        for (int idx = 0; idx < grids.size(); ++idx) {
            // Discard grids which has already won
            if (winning_grids.find(idx) != winning_grids.end()) {
                continue;
            }

            auto &grid = grids[idx];
            update_grid(grid, draw);
            auto bingo_test = check_grid(grid);
            if (bingo_test) {
                winning_grids[idx] = true;

                latest_winning_grid = grids[idx];
                latest_winning_draw = draw;
            }
        }
    }
    std::cout << "Last grid score "
              << compute_score(latest_winning_grid, latest_winning_draw)
              << std::endl;
}
