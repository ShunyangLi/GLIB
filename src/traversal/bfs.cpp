/**
 * @author Shunyang Li
 * Contact: sli@cse.unsw.edu.au
 * @date on 2024/12/6.
 */

#include "glib/graph.h"
#include "glib/traversal/algorithm.h"

namespace GLIB {
    template<typename VertexType, typename EdgeType>
    auto bfs(const Graph<VertexType>& graph, const VertexType vertex) -> std::vector<VertexType> {

        if (graph.vertex_map.find(vertex) == graph.vertex_map.end()) {
            log_error("Error: Vertex {} not found in the graph", vertex);
            exit(EXIT_FAILURE);
        }

        int u = graph.vertex_map[vertex];

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

    template<typename VertexType, typename EdgeType>
    auto dfs(const Graph<VertexType>& graph, const VertexType vertex) -> std::vector<VertexType> {

        if (graph.vertex_map.find(vertex) == graph.vertex_map.end()) {
            log_error("Error: Vertex {} not found in the graph", vertex);
            exit(EXIT_FAILURE);
        }

        int u = graph.vertex_map[vertex];

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


} // namespace GLIB