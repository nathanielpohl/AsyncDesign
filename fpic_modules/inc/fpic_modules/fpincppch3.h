// This file contains the class derivative for a playing around with functional
// programming.
#pragma once

#include <string>

#include "tools/command.h"
#include "tools/csv_parser.h"

namespace fpic_modules {
class FPInCppCh3 : public tools::Command {
 public:
  FPInCppCh3(std::string command_id);
  FPInCppCh3* Clone() { return new FPInCppCh3(command_id_); }
  void Deserialize(tools::CSVParser& params);
  int Execute();
};

}  // namespace fpic_modules
