// This file contains the class derivative for the decode string problem.
#pragma once

#include <string>

#include "tools/command.h"
#include "tools/csv_parser.h"

namespace interview {
class DecodeString : public tools::Command {
 public:
  DecodeString(std::string command_id);
  DecodeString* Clone() { return new DecodeString(command_id_); }
  void Deserialize(tools::CSVParser& params);
  int Execute();
};

}  // namespace interview
