// This file contains the class derivative for a playing around with functional
// programming.
#pragma once

#include <string>

#include "tools/command.h"
#include "tools/csv_parser.h"

namespace fpic_modules {
class FPInCppCh10 : public tools::Command {
 public:
  FPInCppCh10(std::string command_id);
  FPInCppCh10* Clone() { return new FPInCppCh10(command_id_); }
  void Deserialize(tools::CSVParser& params);
  int Execute();
};

}  // namespace fpic_modules
