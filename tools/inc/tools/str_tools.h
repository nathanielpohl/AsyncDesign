// This file contains the that operatre on strings.
#pragma once

#include <algorithm>
#include <cctype>
#include <string>

namespace tools {
//=============================================================================
static inline void TrimFront(std::string &line) {
  line.erase(line.begin(),
             std::find_if(line.begin(), line.end(),
                          [](unsigned char ch) { return !isspace(ch); }));
}
//=============================================================================
static inline void TrimBack(std::string &line) {
  line.erase(std::find_if(line.rbegin(), line.rend(),
                          [](unsigned char ch) { return !isspace(ch); })
                 .base(),
             line.end());
}
//=============================================================================
static inline void Trim(std::string &line) {
  TrimFront(line);
  TrimBack(line);
}
}  // namespace tools
