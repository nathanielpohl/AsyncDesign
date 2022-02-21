// This file contains the class derivative for the exam room problem.
#pragma once

#include <string>

#include "tools/command.h"
#include "tools/csv_parser.h"

namespace interview {
class ExamRoom : public tools::Command {
 public:
  ExamRoom(std::string command_id);
  ExamRoom* Clone() { return new ExamRoom(command_id_); }
  void Deserialize(tools::CSVParser& params);
  int Execute();
};

}  // namespace interview
