// This file contains the base class that must be derived to make new
// commands.
#pragma once

#include <string>

#include "tools/csv_parser.h"

namespace tools {
class Command {
 public:
  Command() {}
  virtual ~Command() {}
  virtual Command* Clone() = 0;
  virtual void Deserialize(CSVParser& params) = 0;
  virtual int Execute() = 0;
  std::string GetId() { return command_id_; }

 protected:
  std::string command_id_;
};
}  // namespace tools
