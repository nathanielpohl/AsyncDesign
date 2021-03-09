// This file contains the derivative class for a word frequncy command.
#pragma once

#include <string>

#include "cmd_modules/file_command.h"
#include "cmd_modules/virtual_constructor.h"
#include "tools/csv_parser.h"

namespace cmd_modules {
class WordFreq : public FileCommand {
 public:
  WordFreq(std::string command_id);
  Command* Clone() { return new WordFreq(command_id_); }
  void Deserialize(tools::CSVParser& params);
  int Execute();

 private:
  std::string word_;
  unsigned int freq_count_;
};
}  // namespace cmd_modules
