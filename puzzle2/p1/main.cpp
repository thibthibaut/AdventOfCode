#include <fstream>
#include <iostream>

int main() {

    std::ifstream input_file("../input.txt");

    std::string direction;

    int value;

    int x = 0;
    int y = 0;

    while (input_file >> direction >> value) {
        std::cout << direction << ' ' << value << '\n';

        if (direction == "forward") {
            x += value;
        } else if (direction == "down") {
            y += value;
        } else if (direction == "up") {
            y -= value;
        } else {
            throw std::runtime_error("Invalid direction");
        }
    }

    std::cout << x * y << '\n';
}
