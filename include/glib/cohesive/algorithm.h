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
    auto query_kcore(const Graph<VertexType>& graph, uint k) -> std::vector<VertexType> {

        if (k <= 0) {
            log_error("k should be greater than 0");
            exit(EXIT_FAILURE);
        }

        auto is_deleted = std::vector<bool>(graph.n, false);
        auto degree = std::vector<int>(graph.n, 0);
        auto invalid = std::vector<int>();

        for (int i = 0; i < graph.n; i++) {
            degree[i] = graph.adj[i].size();
            if (degree[i] < k) invalid.push_back(i);
        }

        while (!invalid.empty()) {
            auto u = invalid.back();
            invalid.pop_back();
            is_deleted[u] = true;

            for (const auto& v : graph.adj[u]) {
                if (!is_deleted[v]) {
                    degree[v]--;
                    if (degree[v] < k) invalid.push_back(v);
                }
            }
        }

        auto kcore = std::vector<VertexType>();
        for (int i = 0; i < graph.n; i++) {
            if (!is_deleted[i]) kcore.push_back(graph.vertices[i]);
        }

        return kcore;
    }

    template<typename VertexType>
    auto kcore_decomposition(const Graph<VertexType>& graph) -> std::unordered_map<VertexType, int> {

    }

} // namespace GLIB


#endif //GLIB_ALGORITHM_H
