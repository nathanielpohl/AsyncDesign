// This file contains the a derivative class of Command, that includes
// paramters needed for reading from a file.
#pragma once

#include <fstream>
#include <iostream>
#include <string>

#include "tools/command.h"
#include "tools/csv_parser.h"

namespace tools {
class FileCommand : public Command {
 public:
  FileCommand() {}
  virtual ~FileCommand() {}
  virtual Command* Clone() = 0;
  virtual void Deserialize(CSVParser& params) = 0;
  virtual int Execute() = 0;

 protected:
  std::string filename_;
};
}  // namespace tools
