// This file contains the implmentation of csv_parser.h the class which tructs
// strings for Command, VirtualConstructor, and all derivative classes there
// of.
#include "tools/csv_parser.h"

#include <string>

namespace tools {
//=============================================================================
void CSVParser::TrimFront(std::string &line) const {
  size_t i = line.find_first_not_of(" \t");
  if (std::string::npos != i) {
    line = line.substr(i);
  }
}

//=============================================================================
void CSVParser::TrimBack(std::string &line) const {
  size_t i = line.find_last_not_of(" \t");
  if (std::string::npos != i) {
    line = line.substr(0, i + 1);
  }
}

//=============================================================================
CSVParser::CSVParser(const std::string &str) {
  row_.assign(str);
  TrimFront(row_);
  TrimBack(row_);
}

//=============================================================================
void CSVParser::SetRow(const std::string &str) {
  row_.assign(str);
  TrimFront(row_);
  TrimBack(row_);
}

//=============================================================================
std::string CSVParser::Next() {
  size_t i;
  std::string next;

  if (row_.empty()) {
    return next;
  }

  i = row_.find(",");
  if (std::string::npos != i) {
    next = row_.substr(0, i);
    row_.erase(0, i + 1);
    TrimFront(row_);
    TrimBack(next);
  } else {
    next = row_;
    row_.clear();
  }

  return next;
}
}  // namespace tools
