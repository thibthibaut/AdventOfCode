#include <fstream>
#include <iostream>
#include <vector>

void append_rolling(std::vector<int> &vector, int data) {}

int main() {

    std::ifstream input_file("input.txt");

    std::vector<int> data;

    int data_point;
    while (input_file >> data_point) {
        data.push_back(data_point);
    }

    int increased_cnt = 0;
    for (std::size_t i = 3; i < data.size(); i++) {

        int latest_sum = data[i] + data[i - 1] + data[i - 2];
        int old_sum = data[i - 1] + data[i - 2] + data[i - 3];

        if (latest_sum > old_sum) {
            increased_cnt++;
        }
    }

    std::cout << increased_cnt << '\n';
}
