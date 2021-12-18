#include <algorithm>
#include <array>
#include <cctype>
#include <fstream>
#include <iostream>
#include <math.h>
#include <memory>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#define MEGA_DEBUG 1

void populate_node(auto &node, auto &node_connexions, const auto &nodes) {

    // Populate the graph
    auto target = node->id;

    std::cout << "Populating node " << target << std::endl;

    // Find this node in node connexions
    auto pos = node_connexions.begin();
    while ((pos = std::find_if(
                pos, node_connexions.end(), [target](const auto &conn) {
                    return conn.first == target || conn.second == target;
                })) != node_connexions.end()) {

        std::cout << "Found connextion with start: " << pos->first << " "
                  << pos->second << std::endl;

        // Assume left node is current node
        auto other_node = pos->second;
        if (pos->first != target) {
            other_node = pos->first;
        }

        // Find other node in node list
        auto other_node_pos =
            std::find_if(nodes.begin(), nodes.end(), [other_node](auto &node) {
                return node->id == other_node;
            });

        // Add connexion if it's not already there
        auto &start_node_connexion = node->next_nodes;
        auto to_add = (*other_node_pos)->id;
        if (std::find_if(start_node_connexion.begin(),
                         start_node_connexion.end(),
                         [to_add](const auto &node) {
                             return node->id == to_add;
                         }) == start_node_connexion.end()) {
            node->next_nodes.emplace_back(*other_node_pos);
        }

        // Bilateral connexion must be done
        // Add the reverse connexion
        (*other_node_pos)->next_nodes.emplace_back(node);

        // Remove this connexion from the list
        node_connexions.erase(pos, pos + 1);
    }
}

size_t explore_graph(auto &node, std::stack<std::string> &path,
                     auto path_count) {

    path.push(node->id);
    node->visit_counter++;

#ifdef MEGA_DEBUG
    std::cout << "Current PATH : ";
    auto stack = path;
    while (!stack.empty()) {
        std::cout << stack.top() << " <- ";
        stack.pop();
    }
    std::cout << std::endl;
#endif

    if (node->is_end) {
        std::cout << "ARRIVED AT THE END with path : ";
        auto stack = path;
        while (!stack.empty()) {
            std::cout << stack.top() << " <- ";
            stack.pop();
        }
        std::cout << std::endl;
        path.pop();
        return path_count + 1;
    }

    int number_of_exploration = 0;
    for (auto &next_node : node->next_nodes) {

        // Don't visit small next nodes that already have been visited once
        if (!(next_node->is_end) && !(next_node->is_big) &&
            next_node->visit_counter > 0) {
#ifdef MEGA_DEBUG
            std::cout << "From node " << node->id << " skipping visit of "
                      << next_node->id << std::endl;
#endif
            continue;
        }
        path_count = explore_graph(next_node, path, path_count);
    }

#ifdef MEGA_DEBUG
    std::cout << "Form node " << node->id << " End exploration : ";
    stack = path;
    while (!stack.empty()) {
        std::cout << stack.top() << " <- ";
        stack.pop();
    }
    std::cout << std::endl;
#endif

    node->visit_counter--;
    path.pop();

    return path_count;
}

struct Node {
    Node(std::string _id)
        : is_big(false), is_start(false), is_end(false), visit_counter(0),
          id(_id){};

    bool is_big;
    bool is_start;
    bool is_end;
    int visit_counter;
    std::string id;
    std::vector<std::shared_ptr<Node>> next_nodes;
};

int main() {

    std::ifstream input_file("../input.txt");

    std::vector<std::pair<std::string, std::string>> node_connexions;

    std::unordered_set<std::string> node_names;

    std::vector<std::shared_ptr<Node>> nodes;

    std::string line;
    while (std::getline(input_file, line)) {

        // Split lines with '-' delimiter and create a node
        auto pos = line.find("-");

        auto left_node_name = line.substr(0, pos);
        line.erase(0, pos + 1);

        auto right_node_name = line;
        std::cout << "node: " << left_node_name << '-' << right_node_name
                  << std::endl;

        if (left_node_name > right_node_name) {
            std::swap(left_node_name, right_node_name);
        }

        // Add these nodes to the map
        node_connexions.emplace_back(
            std::make_pair(left_node_name, right_node_name));

        // Add these node names to the set
        node_names.insert(left_node_name);
        node_names.insert(right_node_name);
    }

    for (const auto &conn : node_connexions) {
        std::cout << conn.first << " connected to " << conn.second << std::endl;
    }

    std::cout << "Create list of nodes: " << std::endl;
    for (const auto &node_name : node_names) {
        std::cout << node_name << std::endl;

        auto new_node = std::make_shared<Node>(node_name);

        if (node_name.size() <= 2 && !std::islower(node_name[0])) {
            new_node->is_big = true;
        }
        if (node_name == "end")
            new_node->is_end = true;

        nodes.push_back(new_node);
    }

    // Populate graph
    for (auto &node : nodes) {
        populate_node(node, node_connexions, nodes);
    }

    // Display connexions
    for (const auto &node : nodes) {
        std::cout << "Node " << node->id << " is connected with ";
        for (const auto &conn : node->next_nodes) {
            std::cout << conn->id << ", ";
        }
        std::cout << std::endl;
    }

    // Explore graph
    auto start_node =
        *std::find_if(nodes.begin(), nodes.end(),
                      [](const auto &n) { return n->id == "start"; });
    std::cout << std::endl;
    std::cout << std::endl;

    std::stack<std::string> path;
    auto path_count = explore_graph(start_node, path, 0);

    std::cout << std::endl;
    std::cout << std::endl;

    std::cout << "Number of pathes " << path_count << std::endl;

    return 0;
}
