// This file contains the class derivative for a playing around with functional
// programming.
#pragma once

#include <string>

#include "tools/command.h"
#include "tools/csv_parser.h"

namespace fpic_modules {
class FPInCppCh6 : public tools::Command {
 public:
  FPInCppCh6(std::string command_id);
  FPInCppCh6* Clone() { return new FPInCppCh6(command_id_); }
  void Deserialize(tools::CSVParser& params);
  int Execute();

 private:
};

}  // namespace fpic_modules
