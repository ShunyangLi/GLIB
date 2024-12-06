/**
 * @author Shunyang Li
 * Contact: sli@cse.unsw.edu.au
 * @date on 2024/12/6.
 */

#ifndef GLIB_ALGORITHM_H
#define GLIB_ALGORITHM_H

#include "glib/graph.h"

namespace GLIB {
    template<typename VertexType>
    auto bfs(const Graph<VertexType>& graph, VertexType vertex) -> std::vector<VertexType> {
        if (graph.vertex_map.find(vertex) == graph.vertex_map.end()) {
            log_error("Error: Vertex {} not found in the graph", vertex);
            exit(EXIT_FAILURE);
        }

        log_info("Running BFS on vertex {}", vertex);

        int u = graph.vertex_map.at(vertex);

        auto q = std::queue<int>();
        auto visited = std::vector<bool>(graph.n, false);
        auto orders = std::vector<VertexType>();

        q.push(u);
        visited[u] = true;

        while (!q.empty()) {
            int v = q.front();
            q.pop();

            // Process the vertex.
            orders.push_back(graph.vertex_list[v]);

            for (int nbr : graph.nbrs[v]) {
                if (!visited[nbr]) {
                    q.push(nbr);
                    visited[nbr] = true;
                }
            }
        }
        return orders;
    }

    template<typename VertexType>
    auto dfs(const Graph<VertexType>& graph, VertexType vertex) -> std::vector<VertexType> {
        if (graph.vertex_map.find(vertex) == graph.vertex_map.end()) {
            log_error("Error: Vertex {} not found in the graph", vertex);
            exit(EXIT_FAILURE);
        }

        log_info("Running DFS on vertex {}", vertex);

        int u = graph.vertex_map.at(vertex);

        auto visited = std::vector<bool>(graph.n, false);
        auto orders = std::vector<VertexType>();

        std::function<void(int)> dfs_visit = [&](int v) {
            visited[v] = true;
            orders.push_back(graph.vertex_list[v]);

            for (int nbr : graph.nbrs[v]) {
                if (!visited[nbr]) {
                    dfs_visit(nbr);
                }
            }
        };

        dfs_visit(u);

        return orders;
    }

    template<typename VertexType>
    auto topo_sort(const GLIB::Graph<VertexType>& graph) -> std::vector<VertexType> {
        if (graph.type != GraphType::Directed) {
            log_error("Error: Topological sort only works for directed graph");
            exit(EXIT_FAILURE);
        }

        log_info("Running topological sort with Kahn's Algorithm");

        auto in_degree = std::vector<int>(graph.n, 0);
        auto result = std::vector<VertexType>();
        auto q = std::queue<uint>();

        for (uint u = 0; u < graph.n; u ++) {
            for (auto const& v : graph.nbrs[u]) in_degree[v] ++;
        }

        for (uint u = 0; u < graph.n; u ++) {
            if (in_degree[u] == 0) q.push(u);
        }

        while (!q.empty()) {
            int v = q.front();
            q.pop();
            result.push_back(graph.vertex_list[v]); // Add to result

            // Reduce in-degree for all neighbors
            for (int nbr : graph.nbrs[v]) {
                in_degree[nbr]--;
                if (in_degree[nbr] == 0) {
                    q.push(nbr);
                }
            }
        }

        if (result.size() != graph.n) {
            log_error("Error: Graph contains a cycle");
            exit(EXIT_FAILURE);
        }

        return result;
    }
} // namespace GLIB

#endif //GLIB_ALGORITHM_H
