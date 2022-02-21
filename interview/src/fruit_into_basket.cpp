// This file contains the class definition for fitting as much fruit into a
// basket as you can.
#include "interview/fruit_into_basket.h"

#include <glog/logging.h>

#include <vector>

namespace interview {

//=============================================================================
FruitIntoBasket::FruitIntoBasket(std::string command_id) {
  command_id_ = command_id;
}

//=============================================================================
void FruitIntoBasket::Deserialize(tools::CSVParser& /*params*/) {
  // Nothing to see here.
}

//=============================================================================
namespace {
/*
You are visiting a farm that has a single row of fruit trees arranged from left
to right. The trees are represented by an integer array fruits where fruits[i]
is the type of fruit the ith tree produces.

You want to collect as much fruit as possible. However, the owner has some
strict rules that you must follow:

-You only have two baskets, and each basket can only hold a single type of
fruit. There is no limit on the amount of fruit each basket can hold.
-Starting from any tree of your choice, you must pick exactly one fruit from
every tree (including the start tree) while moving to the right. The picked
fruits must fit in one of your baskets.
-Once you reach a tree with fruit that cannot fit in your baskets, you must
stop.

Given the integer array fruits, return the maximum number of fruits you can
pick.



Example 1:

Input: fruits = [1,2,1]
Output: 3
Explanation: We can pick from all 3 trees.
Example 2:

Input: fruits = [0,1,2,2]
Output: 3
Explanation: We can pick from trees [1,2,2].
If we had started at the first tree, we would only pick from trees [0,1].
Example 3:

Input: fruits = [1,2,3,2,2]
Output: 4
Explanation: We can pick from trees [2,3,2,2].
If we had started at the first tree, we would only pick from trees [1,2].
Example 4:

Input: fruits = [3,3,3,1,2,1,1,2,3,3,4]
Output: 5
Explanation: We can pick from trees [1,2,1,1,2].


Constraints:

1 <= fruits.length <= 10^5
0 <= fruits[i] < fruits.length
 */

class Solution {
 public:
  int totalFruit(std::vector<int>& fruits) {
    if (fruits.size() < 3) {
      return fruits.size();
    }

    int fruit_one = fruits[0];
    int fruit_two = fruits[1];
    int streak_fruit = fruit_two;
    int streak = fruit_one == fruit_two ? 2 : 1;
    int longest_count = 2;
    int current_count = 2;

    for (unsigned int ii = 2; ii < fruits.size(); ++ii) {
      const auto& fruit = fruits[ii];

      if (fruit_one == fruit_two && fruit_two != fruit) {
        fruit_two = fruit;
        streak_fruit = fruit;
        streak = 0;
      }

      if (fruit == fruit_one || fruit == fruit_two) {
        current_count++;
        if (current_count > longest_count) {
          longest_count = current_count;
        }
        if (fruit == streak_fruit) {
          streak++;
        } else {
          streak_fruit = fruit;
          streak = 1;
        }
      } else {
        current_count = streak + 1;

        fruit_one = fruits[ii - 1];
        fruit_two = fruit;
        streak_fruit = fruit;
        streak = 1;
      }
    }

    return longest_count;
  }
};

}  // namespace

//=============================================================================
int FruitIntoBasket::Execute() {
  LOG(INFO) << "###################################################";
  LOG(INFO) << "####             Fruit Into Basket             ####";
  LOG(INFO) << "###################################################";

  {
    std::vector<int> fruit{1};
    Solution mine;
    LOG(INFO) << "Should be 1: " << mine.totalFruit(fruit);
  }

  {
    std::vector<int> fruit{1, 1};
    Solution mine;
    LOG(INFO) << "Should be 2: " << mine.totalFruit(fruit);
  }

  {
    std::vector<int> fruit{1, 2, 1};
    Solution mine;
    LOG(INFO) << "Should be 3: " << mine.totalFruit(fruit);
  }

  {
    std::vector<int> fruit{0, 1, 2, 2};
    Solution mine;
    LOG(INFO) << "Should be 3: " << mine.totalFruit(fruit);
  }

  {
    std::vector<int> fruit{0, 0, 1, 1};
    Solution mine;
    LOG(INFO) << "Should be 4: " << mine.totalFruit(fruit);
  }

  {
    std::vector<int> fruit{0, 1, 2, 3, 2, 2};
    Solution mine;
    LOG(INFO) << "Should be 4: " << mine.totalFruit(fruit);
  }

  {
    std::vector<int> fruit{0, 1, 2, 2};
    Solution mine;
    LOG(INFO) << "Should be 3: " << mine.totalFruit(fruit);
  }

  {
    std::vector<int> fruit{0, 1, 1, 2, 2};
    Solution mine;
    LOG(INFO) << "Should be 4: " << mine.totalFruit(fruit);
  }

  {
    std::vector<int> fruit{3, 3, 3, 1, 2, 1, 1, 2, 3, 3, 4};
    Solution mine;
    LOG(INFO) << "Should be 5: " << mine.totalFruit(fruit);
  }

  {
    std::vector<int> fruit{1, 0, 0, 0, 1, 0, 4, 0, 4};
    Solution mine;
    LOG(INFO) << "Should be 6: " << mine.totalFruit(fruit);
  }

  return 0;
}
}  // namespace interview
