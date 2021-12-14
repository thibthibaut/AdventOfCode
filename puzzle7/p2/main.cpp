#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

int main() {

    std::ifstream input_file("../input.txt");

    std::vector<int> crabs; //= {16,1,2,0,4,2,7,1,2,14};
    int value;
    while (input_file >> value) {
        crabs.push_back(value);
    }

    const auto [min, max] = std::minmax_element(crabs.begin(), crabs.end());

    std::vector<std::pair<int, int>> distance_map;
    for (auto pivot = *min; pivot < *max + 1; pivot++) {

        int sum_of_distances = 0;
        for (const auto elem : crabs) {
            auto dist = std::abs(elem - pivot);
            auto cumul = (dist * (dist + 1)) / 2;
            sum_of_distances += cumul;
        }
        distance_map.emplace_back(std::make_pair(pivot, sum_of_distances));
    }

    for (const auto &x : distance_map) {
        std::cout << x.first << ", " << x.second << std::endl;
    }

    auto min_val = std::min_element(distance_map.begin(), distance_map.end(),
                                    [](const auto &lhs, const auto &rhs) {
                                        return lhs.second < rhs.second;
                                    });

    std::cout << "Minimum element is "
              << std::distance(std::begin(distance_map), min_val) << " With "
              << min_val->second << " Fuel " << std::endl;
}
