// This file contains the derivative class for a word count command.
#pragma once

#include <string>

#include "cmd_modules/file_command.h"
#include "cmd_modules/virtual_constructor.h"
#include "tools/csv_parser.h"

namespace cmd_modules {
class WordCount : public FileCommand {
 public:
  WordCount(std::string command_id);
  Command* Clone() { return new WordCount(command_id_); }
  void Deserialize(tools::CSVParser& params);
  int Execute();

 private:
  unsigned int word_count_;
};
}  // namespace cmd_modules
