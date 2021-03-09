// This file contains the class derivative for a playing around with funcitonal
// programming.
#pragma once

#include <string>

#include "tools/command.h"
#include "tools/csv_parser.h"

namespace fpic_modules {
class FPInCppCh2 : public tools::Command {
 public:
  FPInCppCh2(std::string command_id);
  FPInCppCh2* Clone() { return new FPInCppCh2(command_id_); }
  void Deserialize(tools::CSVParser& params);
  int Execute();

 private:
};

}  // namespace fpic_modules
