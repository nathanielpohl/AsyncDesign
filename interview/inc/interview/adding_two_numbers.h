// This file contains the class derivative for adding two numbers represented
// as linked lists.
#pragma once

#include <string>

#include "tools/command.h"
#include "tools/csv_parser.h"

namespace interview {
class AddingTwoNumbers : public tools::Command {
 public:
  AddingTwoNumbers(std::string command_id);
  AddingTwoNumbers* Clone() { return new AddingTwoNumbers(command_id_); }
  void Deserialize(tools::CSVParser& params);
  int Execute();
};

}  // namespace interview
