// This file contains the solution for finding the meadian of two sorted
// arrays.
#include "interview/median_of_two_sorted_arrays.h"

#include <glog/logging.h>

#include <vector>

namespace interview {

//=============================================================================
MedianOfTwoSortedArrays::MedianOfTwoSortedArrays(std::string command_id) {
  command_id_ = command_id;
}

//=============================================================================
void MedianOfTwoSortedArrays::Deserialize(tools::CSVParser& /*params*/) {
  // Nothing to see here.
}

//=============================================================================
namespace {
/*
Given two sorted arrays nums1 and nums2 of size m and n respectively, return
the median of the two sorted arrays.

The overall run time complexity should be O(log (m+n)).



Example 1:

Input: nums1 = [1,3], nums2 = [2]
Output: 2.00000
Explanation: merged array = [1,2,3] and median is 2.
Example 2:

Input: nums1 = [1,2], nums2 = [3,4]
Output: 2.50000
Explanation: merged array = [1,2,3,4] and median is (2 + 3) / 2 = 2.5.
Example 3:

Input: nums1 = [0,0], nums2 = [0,0]
Output: 0.00000
Example 4:

Input: nums1 = [], nums2 = [1]
Output: 1.00000
Example 5:

Input: nums1 = [2], nums2 = []
Output: 2.00000


Constraints:

nums1.length == m
nums2.length == n
0 <= m <= 1000
0 <= n <= 1000
1 <= m + n <= 2000
-106 <= nums1[i], nums2[i] <= 106

 */

class Solution {
 public:
  double MedianOfOneArray(std::vector<int>& arr) {
    if (arr.size() % 2) {
      return arr[arr.size() / 2];
    } else {
      return (arr[(arr.size() / 2) - 1] + arr[arr.size() / 2]) / 2.0;
    }
  }
  double findMedianSortedArrays(std::vector<int>& nums1,
                                std::vector<int>& nums2) {
    int size1 = nums1.size();
    int size2 = nums2.size();

    if (size1 == 0) {
      return MedianOfOneArray(nums2);
    } else if (size2 == 0) {
      return MedianOfOneArray(nums1);
    }

    int previous = 0;
    int current = 0;
    int index1 = 0;
    int index2 = 0;
    for (int ii = 0; ii <= (size1 + size2) / 2; ii++) {
      previous = current;
      if (index1 == size1) {
        // Array 1 is exhuasted.
        current = nums2[index2];
        index2++;
      } else if (index2 == size2) {
        // Array 2 is exhuasted.
        current = nums1[index1];
        index1++;
      } else if (nums1[index1] <= nums2[index2]) {
        // Array 1 has the smaller value.
        current = nums1[index1];
        index1++;
      } else {
        // Array 2 has the smaller value.
        current = nums2[index2];
        index2++;
      }
    }

    if ((size1 + size2) % 2) {
      return current;
    } else {
      return (previous + current) / 2.0;
    }
  }
};

}  // namespace

//=============================================================================
int MedianOfTwoSortedArrays::Execute() {
  LOG(INFO) << "###################################################";
  LOG(INFO) << "####         Median Of Two Sorted Arrays       ####";
  LOG(INFO) << "###################################################";

  {
    std::vector<int> array_one{1, 3, 6, 8};
    std::vector<int> array_two{2, 4, 5, 9};
    Solution mine;
    LOG(INFO) << "Should be 4.5:"
              << mine.findMedianSortedArrays(array_one, array_two);
  }

  {
    std::vector<int> array_one{1, 2};
    std::vector<int> array_two{3, 4};
    Solution mine;
    LOG(INFO) << "Should be 2.5:"
              << mine.findMedianSortedArrays(array_one, array_two);
  }

  {
    std::vector<int> array_one{20};
    std::vector<int> array_two{1};
    Solution mine;
    LOG(INFO) << "Should be 10.5:"
              << mine.findMedianSortedArrays(array_one, array_two);
  }

  {
    std::vector<int> array_one{100001};
    std::vector<int> array_two{100000};
    Solution mine;
    LOG(INFO) << "Should be 100000.5:"
              << mine.findMedianSortedArrays(array_one, array_two);
  }

  {
    std::vector<int> array_one{1, 2, 3, 5};
    std::vector<int> array_two{6, 7, 8, 9};
    Solution mine;
    LOG(INFO) << "Should be 5.5:"
              << mine.findMedianSortedArrays(array_one, array_two);
  }

  {
    std::vector<int> array_one{1};
    std::vector<int> array_two{2, 4, 5, 9};
    Solution mine;
    LOG(INFO) << "Should be 4:"
              << mine.findMedianSortedArrays(array_one, array_two);
  }

  {
    std::vector<int> array_one{5};
    std::vector<int> array_two{2, 4, 6, 9};
    Solution mine;
    LOG(INFO) << "Should be 5:"
              << mine.findMedianSortedArrays(array_one, array_two);
  }

  {
    std::vector<int> array_one{3};
    std::vector<int> array_two{1, 1, 1, 1};
    Solution mine;
    LOG(INFO) << "Should be 1:"
              << mine.findMedianSortedArrays(array_one, array_two);
  }

  {
    std::vector<int> array_one{};
    std::vector<int> array_two{1, 2, 3};
    Solution mine;
    LOG(INFO) << "Should be 2:"
              << mine.findMedianSortedArrays(array_one, array_two);
  }

  {
    std::vector<int> array_one{1, 2, 3, 4};
    std::vector<int> array_two{};
    Solution mine;
    LOG(INFO) << "Should be 2.5:"
              << mine.findMedianSortedArrays(array_one, array_two);
  }

  return 0;
}
}  // namespace interview
