// This file contains the class derivative for a checksum command.
#pragma once

#include <string>

#include "cmd_modules/file_command.h"
#include "cmd_modules/virtual_constructor.h"
#include "tools/csv_parser.h"

namespace cmd_modules {
class Checksum : public FileCommand {
 public:
  Checksum(std::string command_id);
  Checksum* Clone() { return new Checksum(command_id_); }
  void Deserialize(tools::CSVParser& params);
  int Execute();

 private:
  unsigned char checksum_;
};

}  // namespace cmd_modules
