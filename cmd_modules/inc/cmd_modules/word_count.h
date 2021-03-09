// This file contains the derivative class for a word count command.
#pragma once

#include <string>

#include "tools/csv_parser.h"
#include "tools/file_command.h"

namespace cmd_modules {
class WordCount : public tools::FileCommand {
 public:
  WordCount(std::string command_id);
  Command* Clone() { return new WordCount(command_id_); }
  void Deserialize(tools::CSVParser& params);
  int Execute();

 private:
  unsigned int word_count_;
};
}  // namespace cmd_modules
