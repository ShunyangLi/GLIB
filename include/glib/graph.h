/**
 * @author Shunyang Li
 * Contact: sli@cse.unsw.edu.au
 * @date on 2024/12/6.
 */
#pragma once
#ifndef GLIB_GRAPH_H
#define GLIB_GRAPH_H

#include "utility.h"
#include "log.h"

namespace GLIB {
    /**
     * @brief A generic Graph class template supporting both vertex and edge types.
     *
     * @tparam VertexType Type of vertices in the graph.
     * @tparam EdgeType Type of edges in the graph (default is void for unweighted graphs).
     */
    template<typename VertexType, typename EdgeType = void>
    class Graph {
    public:
        std::unordered_map<VertexType, int> vertex_map;
        std::vector<VertexType> vertex_list;
        std::vector<std::vector<int>> nbrs;
        uint n, m;
        GraphType type;

    public:
        /**
         * @brief Adds a vertex to the graph. If the vertex already exists, it does nothing.
         *
         * @param v The vertex to add.
         */
        virtual auto add_vertex(const VertexType &v) -> void {
            if (vertex_map.find(v) != vertex_map.end()) return;

            vertex_map[v] = n++; // Assign a new index to the vertex.
            vertex_list.push_back(v);
        }

        /**
         * @brief Adds an edge between two vertices. Adds the vertices if they do not exist.
         *
         * @param u The first vertex of the edge.
         * @param v The second vertex of the edge.
         */
        virtual auto add_edge(const VertexType &u, const VertexType &v) -> void {
            add_vertex(u); // Ensure vertex u is added.
            add_vertex(v); // Ensure vertex v is added.

            int u_id = vertex_map[u], v_id = vertex_map[v];

            if (nbrs.size() <= u_id) nbrs.resize(u_id + 1); // Expand adjacency list for u if needed.
            if (nbrs.size() <= v_id) nbrs.resize(v_id + 1); // Expand adjacency list for v if needed.

            nbrs[u_id].push_back(v_id); // Add v as a neighbor of u.
            nbrs[v_id].push_back(u_id); // Add u as a neighbor of v.
            m++; // Increment edge count.
        }

        auto init(const VertexType &u, const VertexType &v) -> void {
            add_edge(u, v); // Add the edge without storing the edge data.
        }

        /**
         * @brief Default constructor. Initializes an empty graph.
         */
        Graph() : n(0), m(0) {
            vertex_map.clear();
            vertex_list.clear();
            nbrs.clear();
            type = GraphType::Undirected;
        }

        /**
         * @brief Constructor initializing the graph with a list of edges.
         *
         * @param edges List of edges represented as pairs of vertices.
         */
        explicit Graph(const std::vector<std::pair<VertexType, VertexType>> &edges) : n(0), m(0) {
            vertex_map.clear();
            vertex_list.clear();
            nbrs.clear();
            type = GraphType::Undirected;

            for (const auto &e: edges) {
                init(e.first, e.second); // Add each edge to the graph.
            }
        }

        /**
         * @brief Constructor initializing the graph from a file containing edges.
         *
         * @param file_path Path to the input file. Each line should contain two vertices separated by whitespace.
         */
        explicit Graph(const std::string &file_path) : n(0), m(0) {
            vertex_map.clear();
            vertex_list.clear();
            nbrs.clear();
            type = GraphType::Undirected;

            std::ifstream infile(file_path);
            if (!infile.is_open()) {
                log_error("Error: Unable to open file {}", file_path);
                exit(EXIT_FAILURE);
            }

            std::string line;
            while (std::getline(infile, line)) {
                std::istringstream iss(line);
                VertexType u, v;
                if (!(iss >> u >> v)) {
                    log_error("Error: Invalid line format in file: {}", line);
                    exit(EXIT_FAILURE);
                }
                init(u, v); // Add each edge from the file.
            }
            infile.close();
        }

        /**
         * @brief Destructor. Clears all graph data.
         */
        virtual ~Graph() {
            vertex_map.clear();
            vertex_list.clear();
            nbrs.clear();
        }
    };

    template<typename VertexType, typename EdgeType = void>
    class DirectedGraph : public Graph<VertexType, EdgeType> {
    public:
        std::unordered_map<VertexType, int> vertex_map;
        std::vector<VertexType> vertex_list;
        std::vector<std::vector<int>> nbrs;
        uint n{}, m{};
        GraphType type;

        auto add_vertex(const VertexType &v) -> void override {
            if (this->vertex_map.find(v) != this->vertex_map.end()) return;

            this->vertex_map[v] = n++; // Assign a new index to the vertex.
            this->vertex_list.push_back(v);
        }

        /**
         * @brief Adds a directed edge from vertex u to vertex v. Adds the vertices if they do not exist.
         *
         * @param u The starting vertex of the edge.
         * @param v The ending vertex of the edge.
         */
        auto add_edge(const VertexType &u, const VertexType &v) -> void override {
            add_vertex(u); // Ensure vertex u is added.
            add_vertex(v); // Ensure vertex v is added.

            int u_id = this->vertex_map[u], v_id = this->vertex_map[v];

            if (this->nbrs.size() <= u_id) this->nbrs.resize(u_id + 1); // Expand adjacency list for u if needed.
            if (this->nbrs.size() <= v_id) this->nbrs.resize(v_id + 1); // Expand adjacency list for v if needed.

            this->nbrs[u_id].push_back(v_id); // Add v as a neighbor of u (directed edge).
            m++; // Increment edge count.
        }

        /**
         * @brief Default constructor. Initializes an empty directed graph.
         */
        DirectedGraph() : Graph<VertexType, EdgeType>() {
            type = GraphType::Directed;
        }

        /**
         * @brief Constructor initializing the directed graph with a list of edges.
         *
         * @param edges List of edges represented as pairs of vertices.
         */
        explicit DirectedGraph(const std::vector<std::pair<VertexType, VertexType>> &edges) {
            vertex_map.clear();
            vertex_list.clear();
            nbrs.clear();
            type = GraphType::Directed;

            for (const auto &e: edges) {
                add_edge(e.first, e.second); // Add each edge to the graph.
            }
        }

        /**
         * @brief Constructor initializing the directed graph from a file containing edges.
         *
         * @param file_path Path to the input file. Each line should contain two vertices separated by whitespace.
         */
        explicit DirectedGraph(const std::string &file_path) {
            vertex_map.clear();
            vertex_list.clear();
            nbrs.clear();
            type = GraphType::Directed;

            std::ifstream infile(file_path);
            if (!infile.is_open()) {
                log_error("Error: Unable to open file {}", file_path);
                exit(EXIT_FAILURE);
            }

            std::string line;
            while (std::getline(infile, line)) {
                std::istringstream iss(line);
                VertexType u, v;
                if (!(iss >> u >> v)) {
                    log_error("Error: Invalid line format in file: {}", line);
                    exit(EXIT_FAILURE);
                }
                add_edge(u, v); // Add each edge from the file.
            }
            infile.close();
        }

        /**
         * @brief Destructor. Clears all directed graph data.
         */
        ~DirectedGraph() = default;
    };

    template<typename VertexType>
    class BipartiteGraph : public Graph<VertexType> {
    public:
        std::vector<int> upper; std::vector<int> lower;

    public:
    };
} // namespace GLIB

#endif //GLIB_GRAPH_H
