// This file contains the class definition for the decode problem.
#include "interview/decode_string.h"

#include <glog/logging.h>

#include <sstream>
#include <string>

namespace interview {

//=============================================================================
DecodeString::DecodeString(std::string command_id) { command_id_ = command_id; }

//=============================================================================
void DecodeString::Deserialize(tools::CSVParser& /*params*/) {
  // Nothing to see here.
}

//=============================================================================
namespace {
/*
 * Given an encoded string, return its decoded string.

The encoding rule is: k[encoded_string], where the encoded_string inside the
square brackets is being repeated exactly k times. Note that k is guaranteed to
be a positive integer.

You may assume that the input string is always valid; there are no extra white
spaces, square brackets are well-formed, etc.

Furthermore, you may assume that the original data does not contain any digits
and that digits are only for those repeat numbers, k. For example, there will
not be input like 3a or 2[4].



Example 1:
Input: s = "3[a]2[bc]"
Output: "aaabcbc"

Example 2:
Input: s = "3[a2[c]]"
Output: "accaccacc"

Example 3:
Input: s = "2[abc]3[cd]ef"
Output: "abcabccdcdcdef"


Constraints:

1 <= s.length <= 30
s consists of lowercase English letters, digits, and square brackets '[]'.
s is guaranteed to be a valid input.
All the integers in s are in the range [1, 300].
*/

class Solution {
 public:
  bool isLowerCaseLetter(char ch) { return 'a' <= ch && ch <= 'z'; }

  bool isNumber(char ch) { return '0' <= ch && ch <= '9'; }

  std::string decodeString(const std::string& str) {
    std::stringstream result;

    enum class state { letter, number, bracket };

    state reading{state::letter};
    int number{0};
    int bracket_count{0};
    std::stringstream sub_str;

    for (const auto ch : str) {
      if (reading == state::letter) {
        if (isLowerCaseLetter(ch)) {
          result << ch;
        } else if (isNumber(ch)) {
          reading = state::number;
        } else {
          // Ah! something is wrong!
          LOG(FATAL) << "While in letter state we read a bracket!";
        }
      }

      if (reading == state::number) {
        if (isLowerCaseLetter(ch)) {
          // Ah! something is wrong!
          LOG(FATAL) << "While in number state we read a letter!";
        } else if (isNumber(ch)) {
          number *= 10;
          number += ch - '0';
        } else if (ch == '[') {
          reading = state::bracket;
        }
      }

      if (reading == state::bracket) {
        if (ch == '[') {
          if (bracket_count != 0) {
            // Skip the first bracket for the sub_str.
            sub_str << ch;
          }

          bracket_count++;
        } else if (ch == ']') {
          if (bracket_count == 1) {
            // On the closing bracket, run decodeString, and append to the
            // current string.
            std::string sub_result = decodeString(sub_str.str());

            for (int ii = 0; ii < number; ++ii) {
              result << sub_result;
            }

            // Reset incase there are any more letters or string to decode at
            // this level.
            reading = state::letter;
            number = 0;
            sub_str.str(std::string());
          } else {
            sub_str << ch;
          }

          bracket_count--;
        } else {
          // Append all letters and numbers to the sub_str.
          sub_str << ch;
        }
      }
    }

    return result.str();
  }
};

}  // namespace

//=============================================================================
int DecodeString::Execute() {
  LOG(INFO) << "###################################################";
  LOG(INFO) << "###               Decode String                ####";
  LOG(INFO) << "###################################################";

  {
    // Example 1
    std::string str{"3[a]2[bc]"};
    Solution mine;
    LOG(INFO) << "3[a]2[bc] should be aaabcbc: " << mine.decodeString(str);
  }

  {
    // Example 2
    std::string str{"3[a2[c]]"};
    Solution mine;
    LOG(INFO) << "3[a2[c]] should be accaccacc: " << mine.decodeString(str);
  }

  {
    // Example 3
    std::string str{"2[abc]3[cd]ef"};
    Solution mine;
    LOG(INFO) << "2[abc]3[cd]ef should be abcabccdcdcdef: "
              << mine.decodeString(str);
  }

  {
    // Literal only
    std::string str{"abc"};
    Solution mine;
    LOG(INFO) << "abc should be abc: " << mine.decodeString(str);
  }

  {
    // Multiple only
    std::string str{"3[a]"};
    Solution mine;
    LOG(INFO) << "3[a] should be aaa: " << mine.decodeString(str);
  }

  return 0;
}
}  // namespace interview
