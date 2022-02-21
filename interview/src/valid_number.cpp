// This file contains the scratch pad notes that I generated from working
// through "Functional Programming in C++" from Ivan Cuckic.
#include "interview/valid_number.h"

#include <glog/logging.h>

#include <string>
#include <vector>

namespace interview {

//=============================================================================
ValidNumber::ValidNumber(std::string command_id) { command_id_ = command_id; }

//=============================================================================
void ValidNumber::Deserialize(tools::CSVParser& /*params*/) {
  // Nothing to see here.
}

//=============================================================================
namespace {
/*
A valid number can be split up into these components (in order):

A decimal number or an integer.
(Optional) An 'e' or 'E', followed by an integer.
A decimal number can be split up into these components (in order):

(Optional) A sign character (either '+' or '-').
One of the following formats:
One or more digits, followed by a dot '.'.
One or more digits, followed by a dot '.', followed by one or more digits.
A dot '.', followed by one or more digits.
An integer can be split up into these components (in order):

(Optional) A sign character (either '+' or '-').
One or more digits.
For example, all the following are valid numbers: ["2", "0089", "-0.1", "+3.14",
"4.", "-.9", "2e10", "-90E3", "3e+7", "+6e-1", "53.5e93", "-123.456e789"], while
the following are not valid numbers: ["abc", "1a", "1e", "e3", "99e2.5", "--6",
"-+3", "95a54e53"].

Given a string s, return true if s is a valid number.

 */

class Solution {
 public:
  inline bool isSign(char c) { return c == '-' || c == '+'; }

  inline bool isDigit(char c) { return ('0' <= c && c <= '9'); }

  inline bool isDot(char c) { return c == '.'; }

  inline bool isExp(char c) { return c == 'e' || c == 'E'; }

  bool numberCheck(char c) {
    // Begining of a number
    if (state_ == states::begin) {
      if (isSign(c)) {
        total_state_ |= states::sign;
        state_ = states::digit | states::dot;
        return true;
      } else if (isDigit(c)) {
        total_state_ |= states::digit;
        state_ = states::digit | states::dot | states::exp;
        return true;
      } else if (isDot(c)) {
        total_state_ |= states::dot;
        state_ = states::fraction;
        return true;
      }
      return false;
    }

    if (state_ & states::digit && isDigit(c)) {
      total_state_ |= states::digit;
      state_ = states::digit | states::dot | states::exp;
      return true;
    }

    if (state_ & states::dot && isDot(c)) {
      total_state_ |= states::dot;
      state_ = states::fraction | states::exp;
      return true;
    }

    if (state_ & states::fraction && isDigit(c)) {
      total_state_ |= states::fraction;
      state_ = states::fraction | states::exp;
      return true;
    }

    if (state_ & states::exp && isExp(c)) {
      total_state_ |= states::exp;
      state_ = states::expSign | states::expDigit;
      return true;
    }

    if (state_ & states::expSign && isSign(c)) {
      total_state_ |= states::expSign;
      state_ = states::expDigit;
      return true;
    }

    if (state_ & states::expDigit && isDigit(c)) {
      total_state_ |= states::expDigit;
      state_ = states::expDigit;
      return true;
    }

    return false;
  }

  bool isNumber(const std::string& s) {
    bool result = false;
    for (const auto& c : s) {
      result = numberCheck(c);
      if (result == false) {
        break;
      }
    }
    // Check to make sure that there was a number on at least one side of the
    // decimimal if we had one.
    if (total_state_ & states::dot) {
      bool at_least_one_number =
          total_state_ & states::digit || total_state_ & states::fraction;
      result &= at_least_one_number;
    }

    // Check to make sure that if there was an 'e'/'E' that an interger came
    // afterwards.
    if (total_state_ & states::exp) {
      bool e_followed_by_int = total_state_ & states::expDigit;
      result &= e_followed_by_int;
    }

    return result;
  }

 private:
  enum states {
    begin = 0,
    sign = 1,
    digit = 2,
    dot = 4,
    fraction = 8,
    exp = 16,
    expSign = 32,
    expDigit = 64
  };

  int state_ = states::begin;
  int total_state_ = states::begin;
};

}  // namespace

//=============================================================================
int ValidNumber::Execute() {
  LOG(INFO) << "###################################################";
  LOG(INFO) << "####                Valid Number               ####";
  LOG(INFO) << "###################################################";

  {
    std::vector<std::string> numbers{"2",     "0089A",   "-0.1",        "+3.14",
                                     "4.",    ".4",      "4.4",         ".0e7",
                                     "-.9",   "2e10",    "-90E3",       "3e+7",
                                     "+6e-1", "53.5e93", "-123.456e789"};
    for (const auto& number : numbers) {
      Solution mine;
      LOG(INFO) << "Should be 1:" << mine.isNumber(number) << "\t" << number;
    }

    std::vector<std::string> not_numbers{"abc",
                                         "1a",
                                         "1e",
                                         "e3",
                                         ".",
                                         "-.",
                                         ".e",
                                         "e",
                                         "459277e38+"
                                         "e1",
                                         "e-",
                                         "1e-",
                                         "99e2.5",
                                         "--6",
                                         "-+3",
                                         "95a54e53"};
    for (const auto& number : not_numbers) {
      Solution mine;
      LOG(INFO) << "Should be 0:" << mine.isNumber(number) << "\t" << number;
    }
  }

  return 0;
}
}  // namespace interview
