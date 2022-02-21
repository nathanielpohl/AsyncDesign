// This file contains the class definition for finding the longest increasing
// path in a matrix.
#include "interview/longest_increasing_path_matrix.h"

#include <glog/logging.h>

#include <functional>
#include <vector>

namespace interview {

//=============================================================================
LongestIncreasingPathMatrix::LongestIncreasingPathMatrix(
    std::string command_id) {
  command_id_ = command_id;
}

//=============================================================================
void LongestIncreasingPathMatrix::Deserialize(tools::CSVParser& /*params*/) {
  // Nothing to see here.
}

//=============================================================================
namespace {
/*
Given an m x n integers matrix, return the length of the longest increasing path
in matrix.

From each cell, you can either move in four directions: left, right, up, or
down. You may not move diagonally or move outside the boundary (i.e.,
wrap-around is not allowed).


Example 1:
.9 9 4
.6 6 8
.2.1 1
Input: matrix = [[9,9,4],[6,6,8],[2,1,1]]
Output: 4
Explanation: The longest increasing path is [1, 2, 6, 9].


Example 2:
.3.4.5
 3 2.6
 2 2 1
Input: matrix = [[3,4,5],[3,2,6],[2,2,1]]
Output: 4
Explanation: The longest increasing path is [3, 4, 5, 6]. Moving diagonally is
not allowed.


Example 3:
Input: matrix = [[1]]
Output: 1


Constraints:

m == matrix.length
n == matrix[i].length
1 <= m, n <= 200
0 <= matrix[i][j] <= 231 - 1
*/
class Solution {
 public:
  int BFS(const std::vector<std::vector<int>>& matrix,
          std::vector<std::vector<int>>& memo, int yy, int xx, int y_dim,
          int x_dim) {
    // LOG(INFO) << "Visit XX: " << xx << ", YY: " << yy
    //           << " val: " << matrix[yy][xx] << " , path: " << path.size();

    if (memo[yy][xx] != 0) {
      return memo[yy][xx];
    }

    // Up
    int up_path = 0;
    if (xx > 0 && matrix[yy][xx] < matrix[yy][xx - 1]) {
      up_path = BFS(matrix, memo, yy, xx - 1, y_dim, x_dim);
    }
    // Right
    int right_path = 0;
    if (yy < y_dim - 1 && matrix[yy][xx] < matrix[yy + 1][xx]) {
      right_path = BFS(matrix, memo, yy + 1, xx, y_dim, x_dim);
    }
    // Down
    int down_path = 0;
    if (xx < x_dim - 1 && matrix[yy][xx] < matrix[yy][xx + 1]) {
      down_path = BFS(matrix, memo, yy, xx + 1, y_dim, x_dim);
    }
    // Left
    int left_path = 0;
    if (yy > 0 && matrix[yy][xx] < matrix[yy - 1][xx]) {
      left_path = BFS(matrix, memo, yy - 1, xx, y_dim, x_dim);
    }

    // Pick the longest path, and remember it.
    int longest =
        std::max(up_path, std::max(right_path, std::max(down_path, left_path)));
    longest += 1;

    memo[yy][xx] = longest;
    return longest;
  }

  int longestIncreasingPath(const std::vector<std::vector<int>>& matrix) {
    int x_dim = static_cast<int>(matrix[0].size());
    int y_dim = static_cast<int>(matrix.size());

    // Memo stores how long of a path you can make from any given square. The
    // paths are all to the increasing side, IE if the values of our path were
    // 4,5,9 they would have memo valuse of 3,2,1. Memo also serves as a proxy
    // for keeping track of visited states in BFS.
    std::vector<std::vector<int>> memo(y_dim, std::vector<int>(x_dim, 0));

    int longest_path = 0;
    for (int yy = 0; yy < y_dim; ++yy) {
      for (int xx = 0; xx < x_dim; ++xx) {
        if (memo[yy][xx] == 0) {
          // LOG(INFO) << "Increasing BFS from XX: " << xx << ", YY: " << yy;
          int total_path = BFS(matrix, memo, yy, xx, y_dim, x_dim);

          if (total_path > longest_path) {
            longest_path = total_path;
          }
        }
      }
    }
    return longest_path;
  }
};

}  // namespace

//=============================================================================
int LongestIncreasingPathMatrix::Execute() {
  LOG(INFO) << "###################################################";
  LOG(INFO) << "###       Longest Increasing Path Matrix       ####";
  LOG(INFO) << "###################################################";

  {
    // Example 1
    std::vector<std::vector<int>> matrix{{9, 9, 4}, {6, 6, 8}, {2, 1, 1}};
    Solution mine;
    LOG(INFO) << "Should be 4: " << mine.longestIncreasingPath(matrix);
  }

  {
    // Example 2
    std::vector<std::vector<int>> matrix{{3, 4, 5}, {3, 2, 6}, {2, 2, 1}};
    Solution mine;
    LOG(INFO) << "Should be 4: " << mine.longestIncreasingPath(matrix);
  }

  {
    // Example 3
    std::vector<std::vector<int>> matrix{{0}};
    Solution mine;
    LOG(INFO) << "Should be 1: " << mine.longestIncreasingPath(matrix);
  }

  {
    std::vector<std::vector<int>> matrix{{1, 2}, {2, 3}};
    Solution mine;
    LOG(INFO) << "Should be 3: " << mine.longestIncreasingPath(matrix);
  }

  {
    std::vector<std::vector<int>> matrix{{7, 8, 9}, {9, 7, 6}, {7, 2, 3}};
    Solution mine;
    LOG(INFO) << "Should be 6: " << mine.longestIncreasingPath(matrix);
  }

  {
    std::vector<std::vector<int>> matrix{
        {0, 1, 2, 3, 4, 5, 6, 7, 8, 9},
        {19, 18, 17, 16, 15, 14, 13, 12, 11, 10},
        {20, 21, 22, 23, 24, 25, 26, 27, 28, 29},
        {39, 38, 37, 36, 35, 34, 33, 32, 31, 30},
        {40, 41, 42, 43, 44, 45, 46, 47, 48, 49},
        {59, 58, 57, 56, 55, 54, 53, 52, 51, 50},
        {60, 61, 62, 63, 64, 65, 66, 67, 68, 69},
        {79, 78, 77, 76, 75, 74, 73, 72, 71, 70},
        {80, 81, 82, 83, 84, 85, 86, 87, 88, 89},
        {99, 98, 97, 96, 95, 94, 93, 92, 91, 90},
        {100, 101, 102, 103, 104, 105, 106, 107, 108, 109},
        {119, 118, 117, 116, 115, 114, 113, 112, 111, 110},
        {120, 121, 122, 123, 124, 125, 126, 127, 128, 129},
        {139, 138, 137, 136, 135, 134, 133, 132, 131, 130},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
    Solution mine;
    LOG(INFO) << "Should be 140: " << mine.longestIncreasingPath(matrix);
  }

  return 0;
}
}  // namespace interview
