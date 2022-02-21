// This file contains the class definition for the exam room problem.
#include "interview/exam_room.h"

#include <glog/logging.h>

#include <sstream>
#include <string>
#include <vector>

namespace interview {

//=============================================================================
ExamRoom::ExamRoom(std::string command_id) { command_id_ = command_id; }

//=============================================================================
void ExamRoom::Deserialize(tools::CSVParser& /*params*/) {
  // Nothing to see here.
}

//=============================================================================
namespace {
/*
There is an exam room with n seats in a single row labeled from 0 to n - 1.

When a student enters the room, they must sit in the seat that maximizes the
distance to the closest person. If there are multiple such seats, they sit in
the seat with the lowest number. If no one is in the room, then the student sits
at seat number 0.

Design a class that simulates the mentioned exam room.

Implement the ExamRoom class:

ExamRoom(int n) Initializes the object of the exam room with the number of the
seats n. int seat() Returns the label of the seat at which the next student will
set. void leave(int p) Indicates that the student sitting at seat p will leave
the room. It is guaranteed that there will be a student sitting at seat p.


Example 1:

Input
["ExamRoom", "seat", "seat", "seat", "seat", "leave", "seat"]
[[10], [], [], [], [], [4], []]
Output
[null, 0, 9, 4, 2, null, 5]

Explanation
ExamRoom examRoom = new ExamRoom(10);
examRoom.seat(); // return 0, no one is in the room, then the student sits at
seat number 0. examRoom.seat(); // return 9, the student sits at the last seat
number 9. examRoom.seat(); // return 4, the student sits at the last seat
number 4. examRoom.seat(); // return 2, the student sits at the last seat
number 2. examRoom.leave(4); examRoom.seat(); // return 5, the student sits at
the last seat number 5.



Constraints:

1 <= n <= 109
It is guaranteed that there is a student sitting at seat p.
At most 104 calls will be made to seat and leave.

*/

class ExamRoomProblem {
 public:
  ExamRoomProblem(int n) { seats_occupied.resize(n, false); }

  int seat() {
    int longest_count = -0;
    int longest_index = -0;

    int current_count = 0;
    int current_index = 0;

    for (int ii = 0; ii < (int)seats_occupied.size(); ++ii) {
      if (seats_occupied[ii] == false) {
        if (current_count == 0) {
          current_index = ii;
        }

        current_count++;
      } else {
        if (current_count > longest_count) {
          longest_count = current_count;
          longest_index = current_index;
        }

        current_count = 0;
      }

      // Last seat check.
      if (ii == (int)seats_occupied.size() - 1 &&
          current_count > longest_count) {
        longest_count = current_count;
        longest_index = current_index;
      }
    }

    int propose_index = longest_index + (longest_count / 2);
    if (longest_index == 0) {
      // Fill the first slot if it's open and the best.
      propose_index = 0;
      seats_occupied[propose_index] = true;
      LOG(INFO) << "RETURN FRONT";
      return propose_index;
    } else if (longest_index + longest_count == (int)seats_occupied.size()) {
      // Fill the last slot if it's open and the best.
      propose_index = (int)seats_occupied.size() - 1;
      seats_occupied[propose_index] = true;
      LOG(INFO) << "RETURN BACK";
      return propose_index;
    } else if (longest_count == 1) {
      // If all we have are single open desks, fill them.
      seats_occupied[propose_index] = true;
      LOG(INFO) << "RETURN SINGLE: " << propose_index;
      return propose_index;
    }

    // Search again since we want the first index that is longest_count/2 away
    // from all other students.
    int mark_seat = 0;
    current_count = 0;
    current_index = 0;
    for (int ii = 0; ii < (int)seats_occupied.size(); ++ii) {
      if (seats_occupied[ii] == false) {
        if (current_count == 0) {
          current_index = ii;
        }

        current_count++;
        if (current_count == ((longest_count) / 2)) {
          LOG(INFO) << "    MARKING: " << ii;
          mark_seat = ii;
        }
      } else {
        if (mark_seat + ((longest_count) / 2)) {
          LOG(INFO) << "    MARKING: Done: " << ii;
          propose_index = mark_seat;
          break;
        }

        LOG(INFO) << "    MARKING: esrased: ii: " << ii
                  << " current_count: " << current_count
                  << " blob: " << mark_seat + ((longest_count) / 2);
        mark_seat = 0;
        current_count = 0;
      }

      // Last seat check.
      if (ii == (int)seats_occupied.size() - 1 &&
          current_count == ((longest_count) / 2)) {
        propose_index = mark_seat;
      }
    }

    seats_occupied[propose_index] = true;

    LOG(INFO) << "RETURN: " << propose_index;
    return propose_index;
  }

  void leave(int p) { seats_occupied[p] = false; }

 private:
  std::vector<bool> seats_occupied;
};

/**
 * Your ExamRoom object will be instantiated and called as such:
 * ExamRoom* obj = new ExamRoom(n);
 * int param_1 = obj->seat();
 * obj->leave(p);
 */

}  // namespace

//=============================================================================
int ExamRoom::Execute() {
  LOG(INFO) << "###################################################";
  LOG(INFO) << "###                 Exam Room                  ####";
  LOG(INFO) << "###################################################";

  // TODO: There are off-by-one errors in my code that I'm not going to fix from
  // the autograder on leet code.
  {
    // Example 1
    ExamRoomProblem* examRoom = new ExamRoomProblem(10);
    std::stringstream result;
    result << '{';
    result << examRoom->seat() << ", ";
    result << examRoom->seat() << ", ";
    result << examRoom->seat() << ", ";
    result << examRoom->seat() << ", ";
    examRoom->leave(4);
    result << "_, ";
    result << examRoom->seat() << "}";

    // The first seat thing is messing me up on all these test cases. I expected
    // 0, 9, 4, 7....
    LOG(INFO) << "Should be {0, 9, 4 ,2 , _, 5}: " << result.str();
  }

  {
    // Wrong answer
    ExamRoomProblem* examRoom = new ExamRoomProblem(5);
    std::stringstream result;
    result << '{';
    result << examRoom->seat() << ", ";
    result << examRoom->seat() << ", ";
    result << examRoom->seat() << ", ";
    result << examRoom->seat() << ", ";
    result << examRoom->seat() << ", ";
    examRoom->leave(1);
    result << "_, ";
    result << examRoom->seat() << "}";

    LOG(INFO) << "Should be {0, 4, 2 ,1 , 3, _, 1}: " << result.str();
  }

  {
    // Wrong answer
    ExamRoomProblem* examRoom = new ExamRoomProblem(8);
    std::stringstream result;
    result << '{';
    result << examRoom->seat() << ", ";
    result << examRoom->seat() << ", ";
    result << examRoom->seat() << ", ";
    examRoom->leave(0);
    result << "_, ";
    examRoom->leave(7);
    result << "_, ";
    result << examRoom->seat() << ", ";
    result << examRoom->seat() << ", ";
    result << examRoom->seat() << ", ";
    result << examRoom->seat() << ", ";
    result << examRoom->seat() << ", ";
    result << examRoom->seat() << ", ";
    result << examRoom->seat() << "}";

    LOG(INFO) << "Should be {0, 7, 3, _, _, 7, 0, 5, 1, 2, 4, 6}: "
              << result.str();
  }

  {
    ExamRoomProblem* examRoom = new ExamRoomProblem(3);
    std::stringstream result;
    result << '{';
    result << examRoom->seat() << ", ";
    result << examRoom->seat() << ", ";
    result << examRoom->seat() << ", ";
    examRoom->leave(0);
    result << "_, ";
    result << examRoom->seat() << ", ";
    examRoom->leave(1);
    result << "_, ";
    result << examRoom->seat() << ", ";
    examRoom->leave(2);
    result << "_, ";
    result << examRoom->seat() << "}";

    LOG(INFO) << "Should be {0, 2, 1 , _, 0, _, 1, _, 2}: " << result.str();
  }

  {
    ExamRoomProblem* examRoom = new ExamRoomProblem(4);
    std::stringstream result;
    result << '{';
    result << examRoom->seat() << ", ";
    result << examRoom->seat() << ", ";
    result << examRoom->seat() << ", ";
    result << examRoom->seat() << ", ";
    examRoom->leave(0);
    result << "_, ";
    result << examRoom->seat() << ", ";
    examRoom->leave(1);
    result << "_, ";
    result << examRoom->seat() << ", ";
    examRoom->leave(2);
    result << "_, ";
    result << examRoom->seat() << ", ";
    examRoom->leave(3);
    result << "_, ";
    result << examRoom->seat() << "}";

    LOG(INFO) << "Should be {0, 3, 1 ,2 , _, 0, _, 1, _, 2, _, 3}: "
              << result.str();
  }

  {
    // Example 1
    ExamRoomProblem* examRoom = new ExamRoomProblem(10);
    std::stringstream result;
    result << '{';
    result << examRoom->seat() << ", ";
    result << examRoom->seat() << ", ";
    result << examRoom->seat() << ", ";
    result << examRoom->seat() << ", ";
    result << examRoom->seat() << ", ";
    examRoom->leave(9);
    result << "_, ";
    result << examRoom->seat() << "}";

    LOG(INFO) << "Should be {0, 9, 4, 2, 6, _, 9}: " << result.str();
  }

  return 0;
}
}  // namespace interview
