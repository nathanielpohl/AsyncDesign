// This file contains the class derivative for checking for valid email
// addresses.
#pragma once

#include <string>

#include "tools/command.h"
#include "tools/csv_parser.h"

namespace interview {
class UniqueEmailAddresses : public tools::Command {
 public:
  UniqueEmailAddresses(std::string command_id);
  UniqueEmailAddresses* Clone() {
    return new UniqueEmailAddresses(command_id_);
  }
  void Deserialize(tools::CSVParser& params);
  int Execute();
};

}  // namespace interview
