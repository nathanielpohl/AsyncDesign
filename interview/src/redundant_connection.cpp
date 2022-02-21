// This file contains the class definition for finding a redundant connection in
// an undirected graph.
#include "interview/redundant_connection.h"

#include <glog/logging.h>

#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace interview {

//=============================================================================
RedundantConnection::RedundantConnection(std::string command_id) {
  command_id_ = command_id;
}

//=============================================================================
void RedundantConnection::Deserialize(tools::CSVParser& /*params*/) {
  // Nothing to see here.
}

//=============================================================================
namespace {
/*
In this problem, a tree is an undirected graph that is connected and has no
cycles.

You are given a graph that started as a tree with n nodes labeled from 1 to n,
with one additional edge added. The added edge has two different vertices chosen
from 1 to n, and was not an edge that already existed. The graph is represented
as an array edges of length n where edges[i] = [ai, bi] indicates that there is
an edge between nodes ai and bi in the graph.

Return an edge that can be removed so that the resulting graph is a tree of n
nodes. If there are multiple answers, return the answer that occurs last in the
input.

Example 1:
Input: edges = [[1,2],[1,3],[2,3]]
Output: [2,3]

Example 2:
Input: edges = [[1,2],[2,3],[3,4],[1,4],[1,5]]
Output: [1,4]


Constraints:

n == edges.length
3 <= n <= 1000
edges[i].length == 2
1 <= ai < bi <= edges.length
ai != bi
There are no repeated edges.
The given graph is connected.
*/

class Solution {
 public:
  int InLoopHelper(const std::unordered_map<int, std::vector<int>>& graph,
                   int start, int end, std::unordered_set<int>& visited) {
    if (visited.contains(start)) {
      return false;
    }

    if (start == end) {
      return true;
    }

    visited.insert(start);

    const auto& connections = graph.at(start);
    for (const auto& connection : connections) {
      if (InLoopHelper(graph, connection, end, visited)) {
        return true;
      }
    }

    return false;
  }

  bool InLoop(const std::unordered_map<int, std::vector<int>>& graph, int start,
              int end) {
    std::unordered_set<int> visited;
    return InLoopHelper(graph, start, end, visited);
  }

  std::vector<int> findRedundantConnection(
      const std::vector<std::vector<int>>& edges) {
    std::unordered_map<int, std::vector<int>> graph;
    std::vector<int> last_loop_edge{0, 0};

    for (const auto& edge : edges) {
      bool new_node = (!graph.contains(edge[0]) || !graph.contains(edge[1]));
      if (!new_node && InLoop(graph, edge[0], edge[1])) {
        last_loop_edge = edge;
      }
      graph[edge[0]].push_back(edge[1]);
      graph[edge[1]].push_back(edge[0]);
    }

    return last_loop_edge;
  }
};

}  // namespace

//=============================================================================
int RedundantConnection::Execute() {
  LOG(INFO) << "###################################################";
  LOG(INFO) << "###            Redundant Connection            ####";
  LOG(INFO) << "###################################################";

  {
    // Example 1 - Triangle
    std::vector<std::vector<int>> graph{{1, 2}, {1, 3}, {2, 3}};
    Solution mine;
    auto result = mine.findRedundantConnection(graph);
    LOG(INFO) << "Should be {2, 3}: {" << result[0] << ", " << result[1] << "}";
  }

  {
    // Example 2 - Box with one leaf
    std::vector<std::vector<int>> graph{{1, 2}, {2, 3}, {3, 4}, {1, 4}, {1, 5}};
    Solution mine;
    auto result = mine.findRedundantConnection(graph);
    LOG(INFO) << "Should be {1, 4}: {" << result[0] << ", " << result[1] << "}";
  }

  {
    // X
    std::vector<std::vector<int>> graph{{1, 2}, {2, 3}, {4, 5}, {5, 6}, {2, 5}};
    Solution mine;
    auto result = mine.findRedundantConnection(graph);
    LOG(INFO) << "Should be {0, 0}: {" << result[0] << ", " << result[1] << "}";
  }

  {
    // Two squares
    std::vector<std::vector<int>> graph{{1, 2}, {2, 3}, {4, 5}, {5, 6},
                                        {2, 5}, {1, 4}, {3, 6}};
    Solution mine;
    auto result = mine.findRedundantConnection(graph);
    LOG(INFO) << "Should be {3, 6}: {" << result[0] << ", " << result[1] << "}";
  }

  return 0;
}
}  // namespace interview
