#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

#define RESET "\033[0m"
#define BLACK "\033[30m"   /* Black */
#define RED "\033[31m"     /* Red */
#define GREEN "\033[32m"   /* Green */
#define YELLOW "\033[33m"  /* Yellow */
#define BLUE "\033[34m"    /* Blue */
#define MAGENTA "\033[35m" /* Magenta */
#define CYAN "\033[36m"    /* Cyan */
#define WHITE "\033[37m"   /* White */

void increase_energy(std::vector<std::vector<std::pair<int, bool>>> &octopies,
                     int row, int col) {

    if (row < 0 || row > (octopies.size() - 1) || col < 0 ||
        col > (octopies.size() - 1)) {
        return;
    }

    octopies[row][col].first++;

    /*
    if(octopies[row][col].first > 9 && octopies[row][col].second == false ){

      // flash
      octopies[row][col].first++;
      octopies[row][col].second = true;
      increase_energy(octopies, row, col-1); // left
      increase_energy(octopies, row, col+1); // right
      increase_energy(octopies, row-1, col); // up
      increase_energy(octopies, row+1, col); // down

      increase_energy(octopies, row-1, col-1); // top-left
      increase_energy(octopies, row-1, col+1); // top-right
      increase_energy(octopies, row+1, col-1); // bottom-left
      increase_energy(octopies, row+1, col+1); // bottom-right

    }
    */
}

size_t
update_octopies(std::vector<std::vector<std::pair<int, bool>>> &octopies) {

    size_t flash = 0;

    // First, the energy level of each octopus increases by 1.
    for (int row = 0; row < octopies.size(); row++) {
        for (int col = 0; col < octopies[0].size(); col++) {
            octopies[row][col].first++;
        }
    }

    // Then, any octopus with an energy level greater than 9 flashes.
    // This increases the energy level of all adjacent octopuses by 1
    // including octopuses that are diagonally adjacent.
    // If this causes an octopus to have an energy level greater than 9, it also
    // flashes. This process continues as long as new octopuses keep having
    // their energy level increased beyond 9. (An octopus can only flash at most
    // once per step.)

    bool update = false;
    do {
        update = false;
        for (int row = 0; row < octopies.size(); row++) {
            for (int col = 0; col < octopies[0].size(); col++) {

                if (octopies[row][col].first > 9 &&
                    octopies[row][col].second == false) {
                    // Flash
                    update = true;
                    flash++;

                    octopies[row][col].second = true;

                    increase_energy(octopies, row, col - 1); // left
                    increase_energy(octopies, row, col + 1); // right
                    increase_energy(octopies, row - 1, col); // up
                    increase_energy(octopies, row + 1, col); // down

                    increase_energy(octopies, row - 1, col - 1); // top-left
                    increase_energy(octopies, row - 1, col + 1); // top-right
                    increase_energy(octopies, row + 1, col - 1); // bottom-left
                    increase_energy(octopies, row + 1, col + 1); // bottom-right
                }
            }
        }

    } while (update); // end while update

    // Finally, any octopus that flashed during this step
    // has its energy level set to 0, as it used all of its energy to flash.

    for (int row = 0; row < octopies.size(); row++) {
        for (int col = 0; col < octopies[0].size(); col++) {
            if (octopies[row][col].second) {
                std::cout << CYAN << '*' << RESET;
                octopies[row][col].second = false;
                octopies[row][col].first = 0;
            } else {
                std::cout << WHITE << octopies[row][col].first << RESET;
            }
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;
    std::cout << std::endl;

    return flash;
}

int main() {

    std::ifstream input_file("../input.txt");

    std::vector<std::vector<std::pair<int, bool>>> octopies;
    std::string line;
    while (std::getline(input_file, line)) {

        std::vector<std::pair<int, bool>> row;

        std::transform(
            line.begin(), line.end(), std::back_inserter(row),
            [](const char a) { return std::make_pair(a - '0', false); });

        octopies.push_back(row);
    }

    size_t total_flashes = 0;
    for (int step = 0; step < 100; step++) {

        std::cout << "After step " << step + 1 << ": " << std::endl;
        total_flashes += update_octopies(octopies);
    }

    std::cout << "Total number of flashes " << total_flashes << std::endl;
}
