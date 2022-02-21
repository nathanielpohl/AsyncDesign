// This file contains the class derivative for fitting as much fruit into a basket as you can.
#pragma once

#include <string>

#include "tools/command.h"
#include "tools/csv_parser.h"

namespace interview {
class FruitIntoBasket : public tools::Command {
 public:
  FruitIntoBasket(std::string command_id);
  FruitIntoBasket* Clone() { return new FruitIntoBasket(command_id_); }
  void Deserialize(tools::CSVParser& params);
  int Execute();
};

}  // namespace interview
