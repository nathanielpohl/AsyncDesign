// This file contains the class derivative for guess the word problem.
#pragma once

#include <string>

#include "tools/command.h"
#include "tools/csv_parser.h"

namespace interview {
class GuessTheWord : public tools::Command {
 public:
  GuessTheWord(std::string command_id);
  GuessTheWord* Clone() {
    return new GuessTheWord(command_id_);
  }
  void Deserialize(tools::CSVParser& params);
  int Execute();
};

}  // namespace interview
