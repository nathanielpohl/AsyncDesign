// This file contains the class derivative implmentation of a word count
// command
#include "cmd_modules/word_count.h"

#include <glog/logging.h>

#include <chrono>

#include "tools/csv_parser.h"

namespace cmd_modules {
//=============================================================================
WordCount::WordCount(std::string command_id) : word_count_(0) {
  command_id_ = command_id;
}

//=============================================================================
void WordCount::Deserialize(tools::CSVParser &params) {
  filename_ = params.Next();
}

//=============================================================================
int WordCount::Execute() {
  std::ifstream file(filename_, std::ifstream::in);

  if (!file.is_open()) {
    LOG(ERROR) << "Can't open file: " << filename_;
    return -1;
  }

  std::string word;
  auto start = std::chrono::steady_clock::now();

  while (file >> word) {
    word_count_++;
  }

  auto end = std::chrono::steady_clock::now();
  std::chrono::duration<double> diff = end - start;

  // Single prints are viewed as atomic, create a string, and print it
  LOG(INFO) << GetId() << ", " << filename_ << ", "
            << std::to_string(word_count_) << ", "
            << std::to_string(diff.count());
  return 0;
}
}  // namespace cmd_modules
