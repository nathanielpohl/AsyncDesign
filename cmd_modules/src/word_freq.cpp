// This file contains the derivative class of a word freqncy commmand
#include "cmd_modules/word_freq.h"

#include <time.h>
#include <tools/csv_parser.h>

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
  ifstream file(filename_, ifstream::in);

  if (!file.is_open()) {
    std::string error = "Error: Can't open file: " + filename_ + "\n";
    cout << error;
    return -1;
  }

  std::string line;
  clock_t time = clock();

  while (getline(file, line)) {
    size_t find = line.find(word_);
    if (find == std::string::npos) continue;

    do {
      find = line.find(word_, find + 1);
      freq_count_++;
    } while (std::string::npos != find);
  }

  time = clock() - time;
  double seconds = double(time) / CLOCKS_PER_SEC;

  // Single prints are viewed as atomic, create a string, and print it
  std::string output = GetId() + ", " + filename_ + ", " + word_ + ", " +
                       std::to_string(freq_count_) + ", " +
                       std::to_string(seconds) + "\n";
  std::cout << output;

  return 0;
}
}  // namespace cmd_modules
