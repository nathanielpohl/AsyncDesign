// This file contains the class definition for adding two numbers represented as
// a linked list.
#include "interview/adding_two_numbers.h"

#include <glog/logging.h>

#include <sstream>
#include <string>
#include <vector>

namespace interview {

//=============================================================================
AddingTwoNumbers::AddingTwoNumbers(std::string command_id) {
  command_id_ = command_id;
}

//=============================================================================
void AddingTwoNumbers::Deserialize(tools::CSVParser& /*params*/) {
  // Nothing to see here.
}

//=============================================================================
namespace {
/*
You are given two non-empty linked lists representing two non-negative integers.
The digits are stored in reverse order, and each of their nodes contains a
single digit. Add the two numbers and return the sum as a linked list.

You may assume the two numbers do not contain any leading zero, except the
number 0 itself.

Example 1:
Input: l1 = [2,4,3], l2 = [5,6,4]
Output: [7,0,8]
Explanation: 342 + 465 = 807.

Example 2:
Input: l1 = [0], l2 = [0]
Output: [0]

Example 3:
Input: l1 = [9,9,9,9,9,9,9], l2 = [9,9,9,9]
Output: [8,9,9,9,0,0,0,1]

*/

// Definition for singly-linked list.
struct ListNode {
  int val;
  ListNode* next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode* next) : val(x), next(next) {}
};

// Should be part of the ListNode, but leetcode doesn't give me access to that
// class.
std::string PrintList(ListNode* list) {
  std::stringstream result;
  result << '{';
  bool first_time = true;
  while (list != nullptr) {
    if (first_time == false) {
      result << ", ";
    } else {
      first_time = false;
    }
    result << list->val;
    list = list->next;
  }
  result << '}';

  return result.str();
}

// Should be part of the ListNode, but leetcode doesn't give me access to that
// class.
void DestroyList(ListNode* list) {
  while (list != nullptr) {
    ListNode* next = list->next;
    delete list;
    list = next;
  }
}

// Should be part of the ListNode, but leetcode doesn't give me access to that
// class.
ListNode* CreateList(const std::vector<int>&& vec) {
  ListNode* list_end_ptr = nullptr;
  ListNode* list_ptr = nullptr;

  for (const auto& value : vec) {
    ListNode* next = new ListNode(value);

    if (list_ptr == nullptr) {
      list_ptr = next;
      list_end_ptr = next;
    } else {
      list_end_ptr->next = next;
      list_end_ptr = next;
    }
  }

  return list_ptr;
}

class Solution {
 public:
  ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    ListNode* list_ptr = nullptr;
    ListNode* list_end_ptr = nullptr;
    int carry = 0, next_val = 0;

    while (l1 != nullptr || l2 != nullptr) {
      next_val = 0;
      if (l2 != nullptr) {
        next_val += l2->val;
        l2 = l2->next;
      }
      if (l1 != nullptr) {
        next_val += l1->val;
        l1 = l1->next;
      }

      next_val += carry;
      carry = next_val / 10;
      next_val %= 10;

      ListNode* next = new ListNode(next_val);

      if (list_ptr == nullptr) {
        list_ptr = next;
        list_end_ptr = next;
      } else {
        list_end_ptr->next = next;
        list_end_ptr = next;
      }
    }

    if (carry != 0) {
      list_end_ptr->next = new ListNode(carry);
    }

    return list_ptr;
  }
};

}  // namespace

//=============================================================================
int AddingTwoNumbers::Execute() {
  LOG(INFO) << "###################################################";
  LOG(INFO) << "###            Adding Two Numbers              ####";
  LOG(INFO) << "###################################################";

  {
    // Example 1
    ListNode* list_one = CreateList({2, 4, 3});
    ListNode* list_two = CreateList({5, 6, 4});
    Solution mine;
    ListNode* result_list = mine.addTwoNumbers(list_one, list_two);

    LOG(INFO) << "Should be {7,0,8}: " << PrintList(result_list);
    DestroyList(result_list);
  }

  {
    // Example 2
    ListNode* list_one = CreateList({0});
    ListNode* list_two = CreateList({0});
    Solution mine;
    ListNode* result_list = mine.addTwoNumbers(list_one, list_two);

    LOG(INFO) << "Should be {0}: " << PrintList(result_list);
    DestroyList(result_list);
  }

  {
    // Example 3
    ListNode* list_one = CreateList({9, 9, 9, 9, 9, 9, 9});
    ListNode* list_two = CreateList({9, 9, 9, 9});
    Solution mine;
    ListNode* result_list = mine.addTwoNumbers(list_one, list_two);

    LOG(INFO) << "Should be {8,9,9,9,0,0,0,1}: " << PrintList(result_list);
    DestroyList(result_list);
  }

  {
    ListNode* list_one = CreateList({2, 4, 3});
    Solution mine;
    ListNode* result_list = mine.addTwoNumbers(list_one, nullptr);

    LOG(INFO) << "Should be {2, 4, 3}: " << PrintList(result_list);
    DestroyList(result_list);
  }

  {
    Solution mine;
    ListNode* result_list = mine.addTwoNumbers(nullptr, nullptr);

    LOG(INFO) << "Should be {}: " << PrintList(result_list);
    DestroyList(result_list);
  }

  return 0;
}
}  // namespace interview
