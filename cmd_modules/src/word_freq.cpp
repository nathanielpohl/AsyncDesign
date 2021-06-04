// This file contains the derivative class of a word freqncy commmand
#include "cmd_modules/word_freq.h"

#include <glog/logging.h>

#include <chrono>

#include "tools/csv_parser.h"

namespace cmd_modules {
//=============================================================================
WordFreq::WordFreq(std::string command_id) : freq_count_(0) {
  command_id_ = command_id;
}

//=============================================================================
void WordFreq::Deserialize(tools::CSVParser &params) {
  filename_ = params.Next();
  word_ = params.Next();
}

//=============================================================================
int WordFreq::Execute() {
  std::ifstream file(filename_, std::ifstream::in);

  if (!file.is_open()) {
    LOG(ERROR) << "Can't open file: " << filename_;
    return -1;
  }

  std::string line;
  auto start = std::chrono::steady_clock::now();

  while (getline(file, line)) {
    size_t find = line.find(word_);
    if (find == std::string::npos) continue;

    do {
      find = line.find(word_, find + 1);
      freq_count_++;
    } while (std::string::npos != find);
  }

  auto end = std::chrono::steady_clock::now();
  std::chrono::duration<double> diff = end - start;

  // Single prints are viewed as atomic, create a string, and print it
  LOG(INFO) << GetId() << ", " << filename_ << ", " << word_ << ", "
            << std::to_string(freq_count_) << ", "
            << std::to_string(diff.count());

  return 0;
}
}  // namespace cmd_modules
