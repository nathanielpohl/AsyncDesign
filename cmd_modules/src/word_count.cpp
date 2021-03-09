// This file contains the class derivative implmentation of a word count
// command
#include "cmd_modules/word_count.h"

#include <time.h>

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
  ifstream file(filename_, ifstream::in);

  if (!file.is_open()) {
    std::string error = "Error: Can't open file: " + filename_ + "\n";
    cout << error;
    return -1;
  }

  std::string word;
  clock_t time = clock();

  while (file >> word) {
    word_count_++;
  }

  time = clock() - time;
  double seconds = double(time) / CLOCKS_PER_SEC;

  // Single prints are viewed as atomic, create a string, and print it
  std::string output = GetId() + ", " + filename_ + ", " +
                       std::to_string(word_count_) + ", " +
                       std::to_string(seconds) + "\n";
  std::cout << output;

  return 0;
}
}  // namespace cmd_modules
