#include <array>
#include <fstream>
#include <iostream>
#include <vector>

struct Point {
    int x;
    int y;
};

typedef std::pair<Point, Point> segment_t;

void update_grid(auto &grid, const auto &segment) {

    if (segment.first.x == segment.second.x) {

        auto start_point = segment.first.y;
        auto end_point = segment.second.y;
        if (segment.first.y > segment.second.y) {
            start_point = segment.second.y;
            end_point = segment.first.y;
        }
        for (int i = start_point; i < end_point + 1; i++) {
            grid[segment.first.x][i]++;
        }
    } else if (segment.first.y == segment.second.y) {
        auto start_point = segment.first.x;
        auto end_point = segment.second.x;
        if (segment.first.x > segment.second.x) {
            start_point = segment.second.x;
            end_point = segment.first.x;
        }
        for (int i = start_point; i < end_point + 1; i++) {
            grid[i][segment.first.y]++;
        }
    } else {

        auto left_most_point = segment.first;
        auto right_most_point = segment.second;
        if (segment.first.x > segment.second.x) {
            left_most_point = segment.second;
            right_most_point = segment.first;
        }

        auto y = left_most_point.y;
        auto direction = right_most_point.y > left_most_point.y ? 1 : -1;
        for (int i = left_most_point.x; i < right_most_point.x + 1; i++) {
            grid[i][y]++;
            y += direction;
        }
    }
}

int main() {

    std::ifstream input_file("../input.txt");

    std::vector<segment_t> segments;
    int x1, y1, x2, y2;
    while (input_file >> x1 >> y1 >> x2 >> y2) {

        Point p1 = {x1, y1};
        Point p2 = {x2, y2};
        segment_t segment = std::make_pair(p1, p2);
        segments.push_back(segment);
    }

    std::array<std::array<int, 1000>, 1000> grid;

    for (int x = 0; x < 1000; x++) {
        for (int y = 0; y < 1000; y++) {
            grid[x][y] = 0;
        }
    }

    for (const auto &segment : segments) {

        update_grid(grid, segment);
    }

    int count = 0;
    for (int x = 0; x < 1000; x++) {
        for (int y = 0; y < 1000; y++) {
            // std::cout << grid[x][y];
            if (grid[x][y] >= 2)
                count++;
        }
        // std::cout << std::endl;
    }

    std::cout << count << '\n';

    return 0;
}
