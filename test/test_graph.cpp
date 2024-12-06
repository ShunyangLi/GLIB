#include <gtest/gtest.h>
#include "glib/graph.h"

using namespace GLIB;

// 测试图的基本功能
class GraphTest : public ::testing::Test {
protected:
    Graph<int> graph;

    void SetUp() override {
        // 初始化数据，设置测试环境
    }

    void TearDown() override {
        // 清理数据
    }
};

// 测试添加顶点
TEST_F(GraphTest, AddVertex) {
    graph.add_vertex(1);
    EXPECT_EQ(graph.get_vertex_num(), 1);
}

// 测试添加边
TEST_F(GraphTest, AddEdge) {
    graph.add_edge(1, 2);
    EXPECT_EQ(graph.get_vertex_num(), 2); // 应该有2个顶点
}
