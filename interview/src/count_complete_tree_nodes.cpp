// This file contains the class definition for counting the number of nodes in a
// complete tree.
#include "interview/count_complete_tree_nodes.h"

#include <glog/logging.h>

#include <deque>

namespace interview {

//=============================================================================
CountCompleteTreeNodes::CountCompleteTreeNodes(std::string command_id) {
  command_id_ = command_id;
}

//=============================================================================
void CountCompleteTreeNodes::Deserialize(tools::CSVParser & /*params*/) {
  // Nothing to see here.
}

//=============================================================================
namespace {
/*
Given the root of a complete binary tree, return the number of the nodes in the
tree.

According to Wikipedia, every level, except possibly the last, is completely
filled in a complete binary tree, and all nodes in the last level are as far
left as possible. It can have between 1 and 2h nodes inclusive at the last level
h.

Design an algorithm that runs in less than O(n) time complexity.



Example 1:
Input: root = [1,2,3,4,5,6]
Output: 6


Example 2:
Input: root = []
Output: 0

Example 3:
Input: root = [1]
Output: 1


Constraints:

The number of nodes in the tree is in the range [0, 5 * 10^4].
0 <= Node.val <= 5 * 10^4
The tree is guaranteed to be complete.
*/

// Definition for a binary tree node.
struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  // TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left = nullptr, TreeNode *right = nullptr)
      : val(x), left(left), right(right) {}
};

class Solution {
 public:
  int CountLeft(TreeNode *root, int left_depth) {
    int right_depth = 0;

    if (root == nullptr) {
      return 0;
    }

    TreeNode *ptr = root;
    while (ptr != nullptr) {
      ptr = ptr->right;
      right_depth++;
    }

    if (root == nullptr) {
      return 0;
    } else if (left_depth == right_depth) {
      // The tree is balanced, calculate it's size.
      return (1 << left_depth) - 1;
    } else {
      return 1 + CountLeft(root->left, left_depth - 1) +
             CountRight(root->right, right_depth - 1);
    }
  }

  int CountRight(TreeNode *root, int right_depth) {
    int left_depth = 0;

    if (root == nullptr) {
      return 0;
    }

    TreeNode *ptr = root;
    while (ptr != nullptr) {
      ptr = ptr->left;
      right_depth++;
    }

    if (left_depth == right_depth) {
      // The tree is balanced, calculate it's size.
      return (1 << left_depth) - 1;
    } else {
      return 1 + CountLeft(root->left, left_depth - 1) +
             CountRight(root->right, right_depth - 1);
    }
  }

  int countNodes(TreeNode *root) {
    int left_depth = 0;
    int right_depth = 0;

    if (root == nullptr) {
      return 0;
    }

    TreeNode *ptr = root;
    while (ptr != nullptr) {
      ptr = ptr->left;
      left_depth++;
    }

    ptr = root;
    while (ptr != nullptr) {
      ptr = ptr->right;
      right_depth++;
    }

    if (left_depth == right_depth) {
      // The tree is balanced, calculate it's size.
      return (1 << left_depth) - 1;
    } else {
      return 1 + CountLeft(root->left, left_depth - 1) +
             CountRight(root->right, right_depth - 1);
    }
  }
};

}  // namespace

//=============================================================================
int CountCompleteTreeNodes::Execute() {
  LOG(INFO) << "###################################################";
  LOG(INFO) << "###          Count Complete Tree Nodes         ####";
  LOG(INFO) << "###################################################";

  {
    // Empty tree
    Solution mine;
    LOG(INFO) << "Should be 0: " << mine.countNodes(nullptr);
  }

  {
    // Tree of size 1
    TreeNode tree(1);
    Solution mine;
    LOG(INFO) << "Should be 1: " << mine.countNodes(&tree);
  }

  {
    // Tree of size 2;
    TreeNode leaf(2);
    TreeNode tree(1, &leaf);
    Solution mine;
    LOG(INFO) << "Should be 2: " << mine.countNodes(&tree);
  }

  {
    // Tree of size 3;
    TreeNode leaf_2(2), leaf_3(3);
    TreeNode tree(1, &leaf_2, &leaf_3);
    Solution mine;
    LOG(INFO) << "Should be 3: " << mine.countNodes(&tree);
  }

  {
    // Tree of size 6;
    TreeNode leaf_4(4), leaf_5(5), leaf_6(6);
    TreeNode stem_2(2, &leaf_4, &leaf_5), stem_3(3, &leaf_6);
    TreeNode tree(1, &stem_2, &stem_3);
    Solution mine;
    LOG(INFO) << "Should be 6: " << mine.countNodes(&tree);
  }

  return 0;
}
}  // namespace interview
