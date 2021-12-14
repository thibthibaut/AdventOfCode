#include <algorithm>
#include <fstream>
#include <iostream>
#include <stack>
#include <unordered_map>
#include <vector>

bool is_oppening(const char c) {
    if (c == '{' || c == '[' || c == '(' || c == '<') {
        return true;
    }
    return false;
}

int main() {

    std::ifstream input_file("../input.txt");
    std::string line;

    std::unordered_map<char, char> pairs = {
        {'}', '{'}, {']', '['}, {'>', '<'}, {')', '('},
        {'{', '}'}, {'[', ']'}, {'<', '>'}, {'(', ')'},
    };

    std::unordered_map<char, int> points = {
        {')', 1}, {']', 2}, {'}', 3}, {'>', 4}};

    std::vector<long int> scores;
    while (std::getline(input_file, line)) {

        std::stack<char> stack;

        bool corrupted_line = false;
        for (const auto c : line) {
            if (is_oppening(c)) {
                stack.push(c);
            } else {
                auto top = stack.top();
                char closing = pairs[c];
                if (top != closing) {
                    corrupted_line = true;
                    break;
                }
                stack.pop();
            }
        }
        if (corrupted_line) {
            continue;
        }

        long long int total_score = 0;
        std::cout << line << ' ';
        // Unstack
        while (stack.size() > 0) {
            char missing = stack.top();
            char closing = pairs[missing];
            total_score *= 5;
            total_score += points[closing];
            std::cout << closing;
            stack.pop();
        }
        scores.push_back(total_score);
        std::cout << '|' << total_score;
        std::cout << std::endl;
    }

    std::sort(scores.begin(), scores.end());

    std::cout << scores.size() << '\n';
    auto answer = scores[scores.size() / 2];
    std::cout << "Total score " << answer << std::endl;
}
