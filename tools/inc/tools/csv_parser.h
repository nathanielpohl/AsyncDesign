// This file contains the definition of the string parsing classes to
// read commamd files more easily.
#pragma once

#include <string>

#include "tools/str_tools.h"

namespace tools {
class CSVParser {
  void TrimFront(std::string &line) const;
  void TrimBack(std::string &line) const;

 public:
  CSVParser() {}
  CSVParser(const std::string &str);
  void SetRow(const std::string &str);
  std::string Next();

 private:
  std::string row_;
};
}  // namespace tools
