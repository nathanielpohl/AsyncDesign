// This file contains the class derivative for the most stones removed with
// same row or column problem.
#pragma once

#include <string>

#include "tools/command.h"
#include "tools/csv_parser.h"

namespace interview {
class MostStonesRemovedWithSameRowOrColumn : public tools::Command {
 public:
  MostStonesRemovedWithSameRowOrColumn(std::string command_id);
  MostStonesRemovedWithSameRowOrColumn* Clone() {
    return new MostStonesRemovedWithSameRowOrColumn(command_id_);
  }
  void Deserialize(tools::CSVParser& params);
  int Execute();
};

}  // namespace interview
