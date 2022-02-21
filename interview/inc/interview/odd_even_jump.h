// This file contains the class derivative for the odd even jump problem.
#pragma once

#include <string>

#include "tools/command.h"
#include "tools/csv_parser.h"

namespace interview {
class OddEvenJump : public tools::Command {
 public:
  OddEvenJump(std::string command_id);
  OddEvenJump* Clone() {
    return new OddEvenJump(command_id_);
  }
  void Deserialize(tools::CSVParser& params);
  int Execute();
};

}  // namespace interview
