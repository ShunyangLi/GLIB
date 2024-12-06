/**
 * @author Shunyang Li
 * Contact: sli@cse.unsw.edu.au
 * @date on 2024/12/6.
 */

#ifndef GLIB_ALGORITHM_H
#define GLIB_ALGORITHM_H

#include "glib/graph.h"

namespace GLIB {
    template<typename VertexType, typename EdgeType = void>
    auto bfs(const Graph<VertexType>& graph, const VertexType vertex) -> std::vector<VertexType>;

    template<typename VertexType, typename EdgeType = void>
    auto dfs(const Graph<VertexType>& graph, const VertexType vertex) -> std::vector<VertexType>;
} // namespace GLIB

#endif //GLIB_ALGORITHM_H
