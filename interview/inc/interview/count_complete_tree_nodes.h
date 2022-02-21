// This file contains the class derivative for counting the number of nodes in a
// complete tree.
#pragma once

#include <string>

#include "tools/command.h"
#include "tools/csv_parser.h"

namespace interview {
class CountCompleteTreeNodes : public tools::Command {
 public:
  CountCompleteTreeNodes(std::string command_id);
  CountCompleteTreeNodes* Clone() {
    return new CountCompleteTreeNodes(command_id_);
  }
  void Deserialize(tools::CSVParser& params);
  int Execute();
};

}  // namespace interview
