#include <iostream>
#include "glib/graph.h"
#include "glib/traversal/algorithm.h"

int main() {
    auto graph = GLIB::Graph<std::string>();

    graph.add_edge("AA", "BB");
    graph.add_edge("AA", "CC");
    graph.add_edge("BB", "DD");

    std::vector<std::string> bfs_order = GLIB::dfs(graph, std::string("AA"));

    std::cout << "BFS order: ";
    for (const auto& vertex : bfs_order) {
        std::cout << vertex << " ";
    }
    std::cout << std::endl;
}
