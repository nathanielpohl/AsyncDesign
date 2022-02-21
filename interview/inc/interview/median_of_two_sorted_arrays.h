// This file contains the class derivative for finding the meadian of two sorted
// arrays.
#pragma once

#include <string>

#include "tools/command.h"
#include "tools/csv_parser.h"

namespace interview {
class MedianOfTwoSortedArrays : public tools::Command {
 public:
  MedianOfTwoSortedArrays(std::string command_id);
  MedianOfTwoSortedArrays* Clone() {
    return new MedianOfTwoSortedArrays(command_id_);
  }
  void Deserialize(tools::CSVParser& params);
  int Execute();
};

}  // namespace interview
