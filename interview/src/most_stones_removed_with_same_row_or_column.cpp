// This file contains the class definition for the most stones removed with
// same row or column problem.
#include "interview/most_stones_removed_with_same_row_or_column.h"

#include <glog/logging.h>

#include <algorithm>
#include <limits>
#include <map>
#include <vector>

namespace interview {

//=============================================================================
MostStonesRemovedWithSameRowOrColumn::MostStonesRemovedWithSameRowOrColumn(
    std::string command_id) {
  command_id_ = command_id;
}

//=============================================================================
void MostStonesRemovedWithSameRowOrColumn::Deserialize(
    tools::CSVParser& /*params*/) {
  // Nothing to see here.
}

//=============================================================================
namespace {
/*
On a 2D plane, we place n stones at some integer coordinate points. Each
coordinate point may have at most one stone.

A stone can be removed if it shares either the same row or the same column as
another stone that has not been removed.

Given an array stones of length n where stones[i] = [xi, yi] represents the
location of the ith stone, return the largest possible number of stones that
can be removed.



Example 1:

Input: stones = [[0,0],[0,1],[1,0],[1,2],[2,1],[2,2]]
Output: 5
Explanation: One way to remove 5 stones is as follows:
1. Remove stone [2,2] because it shares the same row as [2,1].
2. Remove stone [2,1] because it shares the same column as [0,1].
3. Remove stone [1,2] because it shares the same row as [1,0].
4. Remove stone [1,0] because it shares the same column as [0,0].
5. Remove stone [0,1] because it shares the same row as [0,0].
Stone [0,0] cannot be removed since it does not share a row/column with
another stone still on the plane.


Example 2:

Input: stones = [[0,0],[0,2],[1,1],[2,0],[2,2]]
Output: 3
Explanation: One way to make 3 moves is as follows:
1. Remove stone [2,2] because it shares the same row as [2,0].
2. Remove stone [2,0] because it shares the same column as [0,0].
3. Remove stone [0,2] because it shares the same row as [0,0].
Stones [0,0] and [1,1] cannot be removed since they do not share a row/column
with another stone still on the plane.


Example 3:

Input: stones = [[0,0]]
Output: 0
Explanation: [0,0] is the only stone on the plane, so you cannot remove it.


Constraints:

1 <= stones.length <= 1000
0 <= xi, yi <= 104
No two stones are at the same coordinate point.
*/

class Solution {
 public:
  std::vector<int> FindNExtStone(const std::vector<std::vector<int>>& stones,
                                 const std::map<int, int>& row_counts,
                                 const std::map<int, int>& column_counts) {
    std::vector<std::vector<int>> counts_row;
    std::vector<std::vector<int>> counts_column;

    for (auto& row_count : row_counts) {
      counts_row.emplace_back(
          std::vector<int>{row_count.second, row_count.first});
    }
    std::sort(counts_row.begin(), counts_row.end());

    for (auto& column_count : column_counts) {
      counts_column.emplace_back(
          std::vector<int>{column_count.second, column_count.first});
    }
    std::sort(counts_column.begin(), counts_column.end());

    std::vector<int> suggested_row_stone{-1, -1};
    int suggested_row_stone_friend_count = std::numeric_limits<int>::max();
    int suggested_row_stone_perpendicular_friend_count =
        std::numeric_limits<int>::max();
    // Find the lowest row count that isn't orphaned.
    for (auto& count_row : counts_row) {
      // Find all the stones in the row.
      // LOG(INFO) << "Finding all stones from row: " << count_row[1]
      //          << " and count: " << count_row[0];
      std::vector<std::vector<int>> stones_in_row;
      for (auto& stone : stones) {
        if (stone[0] == count_row[1]) {
          stones_in_row.emplace_back(stone);
          // LOG(INFO) << "Found stone {" << stone[0] << ", " << stone[1] <<
          // "}";
        }
      }

      suggested_row_stone_friend_count = stones_in_row.size();

      // LOG(INFO) << "Find a suggestiong stone.";
      //  See if there are any non-orphaed stones. If the stone is an orphan,
      //  then continue the for loop.
      //  Suggest a stone, with the lowest number of stones on the perpendicular
      //  axis (column).
      for (auto& stone : stones_in_row) {
        if (row_counts.at(stone[0]) == 1 && column_counts.at(stone[1]) == 1) {
          // Orphan stone.
          continue;
          // LOG(INFO) << "Orphan stone {" << stone[0] << ", " << stone[1] <<
          // "}";
        }

        if (column_counts.at(stone[1]) <
            suggested_row_stone_perpendicular_friend_count) {
          suggested_row_stone = stone;
          suggested_row_stone_perpendicular_friend_count =
              column_counts.at(stone[1]);
          // LOG(INFO) << "New best stone {" << stone[0] << ", " << stone[1]
          //           << "} with friend count: "
          //           << suggested_row_stone_perpendicular_friend_count;
        }
      }

      // If we find a non-orphaned stone, than our work for rows is done.
      if (suggested_row_stone_perpendicular_friend_count !=
          std::numeric_limits<int>::max()) {
        // LOG(INFO) << "Found suggested stone";
        break;
      }
    }

    // Do the same for columns.
    std::vector<int> suggested_column_stone{-1, -1};
    int suggested_column_stone_friend_count = std::numeric_limits<int>::max();
    int suggested_column_stone_perpendicular_friend_count =
        std::numeric_limits<int>::max();
    for (auto& count_column : counts_column) {
      // LOG(INFO) << "Finding all stones from column: " << count_column[1]
      //           << " and count: " << count_column[0];
      std::vector<std::vector<int>> stones_in_column;
      for (auto& stone : stones) {
        if (stone[1] == count_column[1]) {
          stones_in_column.emplace_back(stone);
          // LOG(INFO) << "Found stone {" << stone[0] << ", " << stone[1] <<
          // "}";
        }
      }

      suggested_column_stone_friend_count = stones_in_column.size();

      // LOG(INFO) << "Find a suggestiong stone.";
      for (auto& stone : stones_in_column) {
        if (row_counts.at(stone[0]) == 1 && column_counts.at(stone[1]) == 1) {
          // LOG(INFO) << "Orphan stone {" << stone[0] << ", " << stone[1] <<
          // "}";
          continue;
        }

        if (row_counts.at(stone[0]) <
            suggested_column_stone_perpendicular_friend_count) {
          suggested_column_stone = stone;
          suggested_column_stone_perpendicular_friend_count =
              row_counts.at(stone[0]);
          // LOG(INFO) << "New best stone {" << stone[0] << ", " << stone[1]
          //           << "} with friend count: "
          //           << suggested_column_stone_perpendicular_friend_count;
        }
      }

      if (suggested_column_stone_perpendicular_friend_count !=
          std::numeric_limits<int>::max()) {
        // LOG(INFO) << "Found suggested stone";
        break;
      }
    }

    // Pick the stone that has the lowest numbers of a friends on it's
    // perpendicular axis.
    if (suggested_row_stone_friend_count ==
        suggested_column_stone_friend_count) {
      if (suggested_row_stone_perpendicular_friend_count <
          suggested_column_stone_perpendicular_friend_count) {
        // LOG(INFO) << "Going with row stone: {" << suggested_row_stone[0] <<
        // ", "
        //           << suggested_row_stone[1] << "}";
        return suggested_row_stone;
      } else {
        // LOG(INFO) << "Going with column stone: {" <<
        // suggested_column_stone[0]
        //           << ", " << suggested_column_stone[1] << "}";
        return suggested_column_stone;
      }
    } else if (suggested_row_stone_friend_count <
               suggested_column_stone_friend_count) {
      // LOG(INFO) << "Going with row stone: {" << suggested_row_stone[0] << ",
      // "
      //           << suggested_row_stone[1] << "}";
      return suggested_row_stone;
    } else {
      // LOG(INFO) << "Going with column stone: {" << suggested_column_stone[0]
      //           << ", " << suggested_column_stone[1] << "}";
      return suggested_column_stone;
    }
  }

  int removeStones(std::vector<std::vector<int>>& stones) {
    std::map<int, int> row_counts;
    std::map<int, int> column_counts;

    for (auto& stone : stones) {
      row_counts[stone[0]]++;
      column_counts[stone[1]]++;
    }

    int total_number_of_stones_removed = 0;
    const std::vector<int> kNoStoneCanBeRemoved{-1, -1};

    while (true) {
      // Find the next stone to remove.
      auto next_stone = FindNExtStone(stones, row_counts, column_counts);
      if (next_stone == kNoStoneCanBeRemoved) {
        break;
      }

      // LOG(INFO) << "Removing: {" << next_stone[0] << ", " << next_stone[1]
      //           << "}";

      total_number_of_stones_removed++;

      // Remove the stone, and clean up data structs.
      stones.erase(std::remove(stones.begin(), stones.end(), next_stone),
                   stones.end());
      row_counts.at(next_stone[0])--;
      column_counts.at(next_stone[1])--;

      if (row_counts.at(next_stone[0]) == 0) {
        row_counts.erase(next_stone[0]);
      }
      if (column_counts.at(next_stone[1]) == 0) {
        column_counts.erase(next_stone[1]);
      }
    }

    return total_number_of_stones_removed;
  }
};

}  // namespace

//=============================================================================
int MostStonesRemovedWithSameRowOrColumn::Execute() {
  LOG(INFO) << "###################################################";
  LOG(INFO) << "### Most Stones Removed With Same Row Or Column####";
  LOG(INFO) << "###################################################";

  {
    // Hexigon
    std::vector<std::vector<int>> arr{{0, 0}, {0, 1}, {1, 0},
                                      {1, 2}, {2, 1}, {2, 2}};
    Solution mine;
    LOG(INFO) << "Should be 5: " << mine.removeStones(arr);
  }

  {
    // 5 on a dice
    std::vector<std::vector<int>> arr{{0, 0}, {0, 2}, {1, 1}, {2, 0}, {2, 2}};
    Solution mine;
    LOG(INFO) << "Should be 3: " << mine.removeStones(arr);
  }

  {
    // Vertical line
    std::vector<std::vector<int>> arr{{0, 0}, {0, 1}, {0, 2}, {0, 3}};
    Solution mine;
    LOG(INFO) << "Should be 3: " << mine.removeStones(arr);
  }

  {
    // Horizontal line
    std::vector<std::vector<int>> arr{{0, 0}, {1, 0}, {2, 0}, {3, 0}};
    Solution mine;
    LOG(INFO) << "Should be 3: " << mine.removeStones(arr);
  }

  {
    // F
    std::vector<std::vector<int>> arr{{0, 0}, {0, 1}, {1, 1},
                                      {0, 2}, {1, 3}, {0, 3}};
    Solution mine;
    LOG(INFO) << "Should be 5: " << mine.removeStones(arr);
  }

  {
    // F rotated 90d
    std::vector<std::vector<int>> arr{{0, 0}, {0, 1}, {1, 0},
                                      {2, 0}, {2, 1}, {3, 0}};
    Solution mine;
    LOG(INFO) << "Should be 5: " << mine.removeStones(arr);
  }

  {
    // F rotated 180d
    std::vector<std::vector<int>> arr{{0, 0}, {1, 0}, {1, 1},
                                      {0, 2}, {1, 2}, {1, 3}};
    Solution mine;
    LOG(INFO) << "Should be 5: " << mine.removeStones(arr);
  }

  {
    // F rotated 270d
    std::vector<std::vector<int>> arr{{0, 1}, {1, 1}, {1, 0},
                                      {2, 1}, {3, 1}, {3, 0}};
    Solution mine;
    LOG(INFO) << "Should be 5: " << mine.removeStones(arr);
  }

  {
    // Clockwise spiral.
    std::vector<std::vector<int>> arr{{0, 0}, {0, 3}, {3, 3}, {3, 1},
                                      {1, 1}, {1, 2}, {2, 2}};
    Solution mine;
    LOG(INFO) << "Should be 6: " << mine.removeStones(arr);
    for (auto& blah : arr) {
      LOG(INFO) << "{" << blah[0] << ", " << blah[1] << "}";
    }
  }

  {
    // Counterclockwise spiral.
    std::vector<std::vector<int>> arr{{0, 0}, {0, 3}, {3, 3}, {2, 0},
                                      {1, 1}, {1, 2}, {2, 2}};
    Solution mine;
    LOG(INFO) << "Should be 6: " << mine.removeStones(arr);
    for (auto& blah : arr) {
      LOG(INFO) << "{" << blah[0] << ", " << blah[1] << "}";
    }
  }

  {
    // Diagnol zig-zag
    std::vector<std::vector<int>> arr{{0, 2}, {1, 2}, {1, 1},
                                      {2, 1}, {2, 0}, {3, 0}};
    Solution mine;
    LOG(INFO) << "Should be 5: " << mine.removeStones(arr);
  }

  {
    // Sinister zig-zag
    std::vector<std::vector<int>> arr{{2, 3}, {2, 2}, {1, 2},
                                      {1, 1}, {0, 1}, {0, 0}};
    Solution mine;
    LOG(INFO) << "Should be 5: " << mine.removeStones(arr);
  }

  {
    std::vector<std::vector<int>> arr{{0, 0}};
    Solution mine;
    LOG(INFO) << "Should be 0: " << mine.removeStones(arr);
  }

  {
    std::vector<std::vector<int>> arr{
        {970, 746}, {293, 614}, {165, 817}, {668, 195}, {924, 904}, {779, 448},
        {968, 7},   {715, 751}, {326, 721}, {405, 729}, {281, 496}, {88, 519},
        {536, 378}, {440, 132}, {460, 38},  {60, 226},  {577, 627}, {733, 112},
        {294, 425}, {153, 945}, {293, 329}, {787, 642}, {519, 693}, {856, 566},
        {427, 786}, {409, 199}, {881, 169}, {369, 814}, {747, 929}, {950, 29},
        {953, 303}, {720, 921}, {538, 659}, {904, 314}, {558, 29},  {4, 767},
        {984, 61},  {589, 697}, {204, 243}, {612, 240}, {682, 584}, {813, 49},
        {838, 59},  {416, 318}, {960, 300}, {555, 333}, {408, 221}, {606, 950},
        {869, 310}, {618, 445}, {253, 390}, {143, 534}, {310, 258}, {524, 519},
        {523, 988}, {16, 640},  {73, 446},  {22, 651},  {918, 188}, {704, 177},
        {360, 99},  {570, 353}, {73, 271},  {450, 419}, {251, 907}, {398, 500},
        {988, 935}, {27, 65},   {582, 523}, {37, 13},   {714, 156}, {128, 924},
        {55, 115},  {184, 723}, {276, 185}, {884, 406}, {404, 490}, {465, 445},
        {764, 112}, {485, 792}, {549, 659}, {180, 285}, {940, 228}, {990, 831},
        {536, 546}, {168, 540}, {647, 156}, {944, 536}, {587, 834}, {953, 465},
        {475, 430}, {6, 383},   {995, 980}, {980, 285}, {432, 864}, {325, 416},
        {129, 349}, {22, 863},  {223, 255}, {480, 636}, {768, 430}, {370, 410},
        {428, 62},  {232, 583}, {516, 818}, {547, 176}, {944, 543}, {10, 298},
        {413, 756}, {892, 476}, {803, 491}, {864, 326}, {40, 819},  {868, 24},
        {27, 488},  {546, 347}, {786, 791}, {20, 569},  {737, 57},  {846, 627},
        {938, 803}, {172, 448}, {870, 256}, {12, 165},  {469, 906}, {627, 576},
        {761, 694}, {832, 642}, {787, 168}, {645, 242}, {481, 751}, {561, 85},
        {818, 51},  {143, 14},  {660, 932}, {423, 451}, {826, 429}, {924, 785},
        {617, 257}, {504, 935}, {191, 713}, {602, 672}, {325, 402}, {423, 927},
        {13, 200},  {619, 681}, {91, 218},  {805, 175}, {837, 376}, {500, 686},
        {998, 558}, {469, 271}, {533, 565}, {576, 915}, {740, 113}, {544, 775},
        {841, 100}, {143, 627}, {330, 483}, {745, 448}, {67, 35},   {638, 149},
        {258, 759}, {810, 952}, {994, 453}, {755, 974}, {319, 596}, {932, 800},
        {366, 476}, {204, 916}, {903, 26},  {523, 776}, {543, 51},  {804, 16},
        {522, 378}, {886, 203}, {637, 421}, {623, 301}, {933, 10},  {869, 18},
        {154, 713}, {668, 927}, {351, 522}, {923, 157}, {712, 877}, {584, 930},
        {695, 124}, {272, 574}, {865, 174}, {722, 58},  {685, 529}, {546, 690},
        {695, 258}, {40, 617},  {384, 934}, {168, 115}, {963, 90},  {269, 939},
        {162, 231}, {918, 333}, {757, 315}, {423, 204}, {429, 730}, {212, 203},
        {909, 155}, {497, 570}, {829, 409}, {8, 795},   {649, 678}, {509, 947},
        {592, 585}, {735, 83},  {37, 972},  {122, 965}, {671, 349}, {412, 1},
        {695, 710}, {277, 243}, {998, 488}, {375, 394}, {861, 778}, {41, 249},
        {60, 949},  {774, 25},  {244, 489}, {135, 959}, {796, 923}, {925, 718},
        {361, 51},  {401, 50},  {557, 568}, {597, 737}, {429, 47},  {820, 798},
        {185, 699}, {403, 366}, {385, 807}, {686, 41},  {62, 967},  {374, 480},
        {432, 492}, {952, 125}, {534, 662}, {908, 553}, {168, 779}, {557, 730},
        {687, 10},  {283, 336}, {430, 986}, {913, 374}, {862, 484}, {846, 791},
        {98, 337},  {150, 798}, {257, 100}, {86, 444},  {968, 123}, {327, 936},
        {771, 197}, {976, 934}, {866, 733}, {557, 578}, {500, 568}, {285, 468},
        {747, 521}, {495, 874}, {277, 5},   {889, 482}, {615, 75},  {709, 892},
        {384, 796}, {91, 154},  {554, 107}, {497, 604}, {538, 599}, {961, 942},
        {799, 911}, {306, 349}, {808, 925}, {477, 132}, {578, 315}, {65, 916},
        {301, 929}, {451, 930}, {70, 840},  {476, 535}, {4, 785},   {494, 856},
        {706, 151}, {852, 874}, {266, 475}, {69, 384},  {507, 735}, {590, 72},
        {764, 184}, {167, 468}, {89, 148},  {663, 885}, {871, 758}, {643, 965},
        {425, 628}, {65, 919},  {574, 592}, {235, 343}, {950, 9},   {823, 821},
        {19, 515},  {483, 612}, {377, 87},  {747, 176}, {930, 915}, {860, 318},
        {510, 12},  {438, 155}, {685, 250}, {7, 402},   {430, 724}, {182, 998},
        {639, 626}, {731, 440}, {452, 242}, {399, 64},  {735, 762}, {119, 608},
        {838, 859}, {612, 551}, {281, 978}, {111, 544}, {53, 382},  {330, 110},
        {997, 673}, {227, 762}, {232, 613}, {91, 314},  {257, 76},  {133, 561},
        {66, 727},  {894, 607}, {287, 851}, {627, 320}, {722, 596}, {980, 250},
        {857, 625}, {362, 650}, {790, 913}, {922, 706}, {523, 538}, {930, 280},
        {144, 761}, {481, 600}, {337, 262}, {530, 325}, {342, 879}, {434, 614},
        {116, 297}, {955, 911}, {282, 71},  {249, 341}, {285, 367}, {624, 803},
        {953, 112}, {159, 645}, {886, 726}, {305, 63},  {130, 204}, {151, 45},
        {714, 875}, {986, 724}, {337, 383}, {102, 578}, {289, 764}, {913, 919},
        {164, 578}, {64, 411},  {323, 973}, {324, 402}, {808, 864}, {457, 252},
        {73, 60},   {864, 842}, {517, 169}, {644, 551}, {757, 879}, {426, 772},
        {872, 876}, {195, 619}, {659, 389}, {294, 109}, {994, 226}, {902, 620},
        {466, 331}, {781, 629}, {819, 936}, {497, 189}, {904, 0},   {939, 956},
        {227, 427}, {102, 382}, {984, 920}, {312, 449}, {954, 685}, {42, 419},
        {928, 667}, {412, 670}, {893, 424}, {879, 491}, {842, 272}, {662, 400},
        {22, 398},  {424, 531}, {309, 594}, {224, 635}, {320, 890}, {676, 337},
        {89, 729},  {843, 448}, {187, 945}, {349, 706}, {225, 476}, {214, 576},
        {433, 228}, {821, 19},  {660, 346}, {720, 138}, {871, 7},   {436, 348},
        {554, 858}, {225, 702}, {448, 161}, {179, 819}, {749, 824}, {572, 298},
        {592, 227}, {853, 132}, {238, 717}, {69, 224},  {716, 759}, {241, 654},
        {576, 220}, {321, 345}, {413, 361}, {841, 232}, {494, 62},  {735, 442},
        {480, 80},  {619, 984}, {880, 666}, {109, 950}, {917, 889}, {790, 34},
        {259, 99},  {321, 123}, {995, 793}, {540, 858}, {226, 357}, {45, 170},
        {999, 297}, {844, 909}, {494, 569}, {457, 578}, {450, 118}, {72, 978},
        {163, 509}, {937, 933}, {937, 51},  {779, 679}, {532, 171}, {531, 359},
        {56, 987},  {705, 869}, {399, 684}, {888, 637}, {407, 362}, {525, 206},
        {687, 121}, {414, 824}, {608, 486}, {76, 132},  {645, 693}, {562, 520},
        {929, 481}, {855, 146}, {86, 414},  {387, 746}, {154, 310}, {562, 667},
        {835, 388}, {930, 438}, {427, 13},  {873, 237}, {964, 649}, {587, 382},
        {183, 814}, {499, 88},  {950, 59},  {228, 119}, {926, 874}, {102, 983},
        {919, 857}, {388, 775}, {775, 405}, {688, 842}, {106, 301}, {841, 726},
        {789, 521}, {939, 603}, {961, 167}, {672, 611}, {568, 202}, {36, 202},
        {385, 409}, {427, 535}, {281, 229}, {278, 123}, {94, 752},  {578, 677},
        {502, 483}, {823, 529}, {47, 576},  {611, 458}, {258, 638}, {906, 818},
        {298, 599}, {767, 2},   {59, 886},  {118, 546}, {391, 847}, {547, 909},
        {475, 307}, {225, 296}, {858, 301}, {968, 805}, {661, 270}, {314, 411},
        {887, 17},  {998, 60},  {589, 465}, {240, 693}, {632, 76},  {998, 734},
        {319, 320}, {672, 514}, {547, 632}, {640, 438}, {736, 437}, {457, 719},
        {86, 676},  {777, 76},  {409, 375}, {493, 363}, {641, 218}, {846, 344},
        {170, 367}, {776, 798}, {264, 851}, {9, 811},   {138, 884}, {50, 210},
        {876, 202}, {400, 941}, {364, 502}, {366, 502}, {402, 807}, {868, 489},
        {870, 936}, {214, 972}, {509, 843}, {419, 447}, {546, 142}, {816, 323},
        {85, 962},  {566, 228}, {235, 58},  {568, 824}, {199, 80},  {128, 394},
        {475, 190}, {815, 719}, {928, 86},  {363, 772}, {808, 492}, {275, 58},
        {168, 725}, {353, 900}, {363, 661}, {440, 693}, {558, 587}, {541, 92},
        {673, 921}, {488, 524}, {396, 844}, {109, 901}, {994, 640}, {921, 96},
        {706, 761}, {714, 515}, {967, 183}, {842, 895}, {607, 299}, {578, 114},
        {375, 662}, {900, 572}, {451, 190}, {566, 723}, {346, 965}, {0, 656},
        {663, 122}, {341, 339}, {270, 657}, {698, 539}, {367, 542}, {26, 291},
        {485, 212}, {363, 980}, {661, 177}, {614, 302}, {392, 398}, {355, 777},
        {708, 438}, {194, 153}, {200, 570}, {598, 72},  {76, 213},  {683, 784},
        {304, 116}, {529, 702}, {275, 847}, {352, 549}, {49, 635},  {805, 607},
        {662, 759}, {223, 36},  {249, 473}, {410, 489}, {588, 401}, {257, 74},
        {276, 466}, {649, 166}, {547, 746}, {284, 933}, {121, 637}, {370, 292},
        {62, 476},  {819, 195}, {696, 961}, {522, 837}, {597, 399}, {998, 838},
        {782, 868}, {841, 488}, {843, 771}, {110, 205}, {659, 331}, {204, 644},
        {600, 65},  {250, 755}, {569, 348}, {715, 272}, {994, 584}, {792, 496},
        {757, 634}, {821, 656}, {423, 346}, {925, 682}, {158, 925}, {549, 846},
        {291, 316}, {132, 760}, {614, 58},  {671, 650}, {229, 931}, {585, 256},
        {471, 63},  {292, 328}, {112, 521}, {978, 484}, {174, 378}, {270, 928},
        {755, 682}, {204, 297}, {27, 343},  {597, 948}, {548, 165}, {915, 666},
        {992, 39},  {886, 466}, {467, 92},  {747, 786}, {881, 356}, {734, 134},
        {294, 850}, {280, 605}, {832, 922}, {297, 980}, {302, 313}, {323, 513},
        {604, 552}, {835, 636}, {30, 109},  {35, 559},  {967, 334}, {127, 712},
        {40, 546},  {989, 680}, {352, 238}, {674, 525}, {418, 556}, {897, 423},
        {47, 150},  {158, 570}, {305, 361}, {606, 355}, {367, 31},  {245, 959},
        {746, 827}, {801, 615}, {636, 112}, {533, 162}, {208, 888}, {950, 974},
        {696, 488}, {479, 418}, {144, 204}, {522, 458}, {671, 47},  {419, 486},
        {837, 137}, {213, 884}, {158, 474}, {567, 511}, {896, 237}, {137, 221},
        {711, 351}, {252, 845}, {313, 73},  {631, 132}, {853, 864}, {191, 657},
        {753, 62},  {128, 370}, {167, 51},  {885, 68},  {502, 646}, {162, 571},
        {842, 137}, {807, 468}, {476, 594}, {741, 235}, {742, 572}, {584, 21},
        {88, 90},   {516, 601}, {684, 747}, {96, 772},  {389, 348}, {670, 781},
        {161, 728}, {97, 730},  {459, 610}, {172, 422}, {444, 707}, {472, 98},
        {682, 928}, {607, 830}, {313, 630}, {540, 440}, {155, 544}, {890, 376},
        {601, 203}, {36, 690},  {97, 111},  {388, 621}, {390, 706}, {603, 933},
        {255, 415}, {868, 860}, {746, 935}, {559, 36},  {727, 416}, {110, 561},
        {366, 927}, {152, 326}, {999, 551}, {604, 916}, {40, 828},  {455, 892},
        {960, 381}, {463, 751}, {871, 52},  {491, 793}, {0, 116},   {511, 110},
        {22, 879},  {205, 5},   {557, 763}, {707, 223}, {763, 772}, {472, 652},
        {414, 787}, {572, 313}, {445, 615}, {78, 188},  {710, 668}, {180, 959},
        {787, 251}, {466, 324}, {710, 923}, {207, 71},  {742, 598}, {345, 348},
        {954, 472}, {299, 168}, {279, 459}, {46, 606},  {305, 641}, {900, 344},
        {922, 816}, {452, 172}, {878, 336}, {509, 648}, {901, 231}, {443, 908},
        {134, 734}, {572, 454}, {321, 997}, {765, 994}, {783, 199}, {813, 715},
        {264, 323}, {925, 658}, {456, 352}, {437, 130}, {935, 210}, {748, 484},
        {173, 626}, {842, 316}, {908, 657}, {131, 729}, {924, 144}, {656, 637},
        {380, 35},  {37, 340},  {739, 179}, {815, 819}, {114, 527}, {338, 667},
        {728, 868}, {341, 809}, {603, 138}, {608, 63},  {147, 429}, {572, 45},
        {224, 131}, {404, 452}, {668, 793}, {293, 748}, {905, 455}, {286, 794},
        {396, 928}, {328, 886}, {241, 832}, {935, 269}, {601, 11},  {448, 586},
        {223, 961}, {646, 83},  {25, 555},  {102, 966}, {582, 769}, {841, 886},
        {161, 416}, {536, 89},  {130, 64},  {271, 748}, {680, 14},  {664, 840},
        {32, 740},  {654, 518}, {363, 122}, {181, 159}, {845, 136}, {952, 231},
        {719, 414}, {558, 461}, {228, 976}, {951, 725}, {320, 731}, {210, 342},
        {600, 754}, {198, 161}, {55, 777},  {556, 754}, {99, 361},  {377, 527},
        {122, 391}, {414, 696}, {127, 519}, {739, 857}, {960, 538}, {307, 558},
        {516, 364}, {384, 805}, {666, 273}, {152, 257}, {926, 839}, {928, 418},
        {109, 685}, {258, 31},  {115, 500}, {62, 224},  {965, 5},   {812, 453},
        {981, 937}, {209, 236}, {785, 382}, {806, 446}, {361, 347}, {793, 206},
        {902, 280}, {172, 253}, {391, 342}, {307, 981}, {465, 158}, {654, 166},
        {340, 765}, {531, 409}, {551, 912}, {474, 100}, {38, 246},  {629, 326},
        {295, 86},  {867, 337}, {814, 296}, {600, 798}, {305, 808}, {694, 952},
        {842, 17},  {21, 258},  {998, 217}, {675, 6},   {548, 280}, {92, 140},
        {240, 13},  {205, 491}, {298, 104}, {122, 33},  {335, 875}, {640, 984},
        {570, 988}, {682, 242}, {899, 264}, {684, 530}, {354, 323}, {944, 244},
        {953, 727}, {365, 193}, {917, 372}, {439, 261}, {593, 358}, {334, 478},
        {780, 140}, {351, 131}, {979, 225}, {872, 485}, {478, 331}, {53, 533},
        {918, 76},  {249, 994}, {964, 556}, {627, 801}, {521, 742}, {64, 795},
        {967, 931}, {902, 52},  {541, 514}, {249, 481}, {709, 251}, {493, 790},
        {921, 432}, {189, 903}, {522, 107}, {924, 112}, {800, 499}, {335, 471},
        {255, 187}, {755, 313}, {884, 230}, {333, 755}, {768, 342}, {208, 286},
        {830, 969}, {656, 566}, {787, 99},  {403, 183}, {484, 10},  {671, 486},
        {659, 486}, {887, 721}, {475, 857}, {132, 849}};
    Solution mine;
    LOG(INFO) << "Should be ?: " << mine.removeStones(arr);
  }

  return 0;
}
}  // namespace interview
