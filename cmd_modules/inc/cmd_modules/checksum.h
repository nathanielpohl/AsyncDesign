// This file contains the class derivative for a checksum command.
#pragma once

#include <string>

#include "tools/csv_parser.h"
#include "tools/file_command.h"

namespace cmd_modules {
class Checksum : public tools::FileCommand {
 public:
  Checksum(std::string command_id);
  Checksum* Clone() { return new Checksum(command_id_); }
  void Deserialize(tools::CSVParser& params);
  int Execute();

 private:
  unsigned char checksum_;
};

}  // namespace cmd_modules
