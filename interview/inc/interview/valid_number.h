// This file contains the class derivative for a validating a number.
#pragma once

#include <string>

#include "tools/command.h"
#include "tools/csv_parser.h"

namespace interview {
class ValidNumber : public tools::Command {
 public:
  ValidNumber(std::string command_id);
  ValidNumber* Clone() { return new ValidNumber(command_id_); }
  void Deserialize(tools::CSVParser& params);
  int Execute();
};

}  // namespace interview
