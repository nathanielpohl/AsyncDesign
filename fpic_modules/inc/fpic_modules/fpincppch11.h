// This file contains the class derivative for a playing around with functional
// programming.
#pragma once

#include <string>

#include "tools/command.h"
#include "tools/csv_parser.h"

namespace fpic_modules {
class FPInCppCh11 : public tools::Command {
 public:
  FPInCppCh11(std::string command_id);
  FPInCppCh11* Clone() { return new FPInCppCh11(command_id_); }
  void Deserialize(tools::CSVParser& params);
  int Execute();
};

}  // namespace fpic_modules
