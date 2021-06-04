// This file contains the logic to read in the command file and then
// spin off a thread pool, and than complete the work that is assigned
// in the command file that is passed in on the command line.

#include <glog/logging.h>

#include <fstream>
#include <iostream>
#include <string>
#include <thread>

#include "async_design/virtual_constructor.h"
#include "tools/command.h"

namespace {
static const int kPoolThreadCount = std::thread::hardware_concurrency();

//=============================================================================
void ThreadRoutine() {
  async_design::VirtualConstructor::Instance()->Execute();
}
}  // namespace

//=============================================================================
int main(int argc, char* argv[]) {
  // Initialize Google’s logging library.
  google::InitGoogleLogging(argv[0]);

  std::vector<std::thread> thread_pool(kPoolThreadCount);

  if (argc != 2) {
    LOG(FATAL) << "Usage: async_design_bin <command file>";
  }

  std::ifstream command_file(argv[1]);

  if (!command_file.is_open()) {
    LOG(FATAL) << "Error: Can't open file.";
  }

  // Initialize the virtual constructor class.
  async_design::VirtualConstructor::Instance()->Init(&command_file);

  for (auto& thread : thread_pool) {
    thread = std::thread(ThreadRoutine);
  }

  for (auto& thread : thread_pool) {
    thread.join();
  }

  command_file.close();
}
