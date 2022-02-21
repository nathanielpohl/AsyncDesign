// This file contains the class derivative for a playing around with functional
// programming.
#pragma once

#include <string>

#include "tools/command.h"
#include "tools/csv_parser.h"

namespace fpic_modules {
class FPInCppCh7 : public tools::Command {
 public:
  FPInCppCh7(std::string command_id);
  FPInCppCh7* Clone() { return new FPInCppCh7(command_id_); }
  void Deserialize(tools::CSVParser& params);
  int Execute();
};

}  // namespace fpic_modules
