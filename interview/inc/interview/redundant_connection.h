// This file contains the class derivative for finding a redundant connection in
// an undirected graph.
#pragma once

#include <string>

#include "tools/command.h"
#include "tools/csv_parser.h"

namespace interview {
class RedundantConnection : public tools::Command {
 public:
  RedundantConnection(std::string command_id);
  RedundantConnection* Clone() { return new RedundantConnection(command_id_); }
  void Deserialize(tools::CSVParser& params);
  int Execute();
};

}  // namespace interview
