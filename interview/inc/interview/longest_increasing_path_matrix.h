// This file contains the class derivative for finding the longest increasing
// path in a matrix.
#pragma once

#include <string>

#include "tools/command.h"
#include "tools/csv_parser.h"

namespace interview {
class LongestIncreasingPathMatrix : public tools::Command {
 public:
  LongestIncreasingPathMatrix(std::string command_id);
  LongestIncreasingPathMatrix* Clone() {
    return new LongestIncreasingPathMatrix(command_id_);
  }
  void Deserialize(tools::CSVParser& params);
  int Execute();
};

}  // namespace interview
