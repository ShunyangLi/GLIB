#include <iostream>
#include "glib/graph.h"

int main() {
    auto graph = GLIB::Graph<int>();

    graph.add_edge(1, 2);
    graph.add_edge(2, 3);

    std::cout << graph.get_edge_num() << std::endl;
}
