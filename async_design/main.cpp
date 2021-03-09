// This file contains the logic to read in the command file and then
// spin off a thread pool, and than complete the work that is assigned
// in the command file that is passed in on the command line.

#include <fstream>
#include <iostream>
#include <string>
#include <thread>

#include "cmd_modules/virtual_constructor.h"
#include "tools/command.h"

static const int kPoolThreadCount = std::thread::hardware_concurrency();

//=============================================================================
void ThreadRoutine(std::istream* file) {
  while (true) {
    tools::Command* current_command =
        cmd_modules::VirtualConstructor::Instance()->CreateCommand(file);
    if (!current_command) break;

    current_command->Execute();
    delete current_command;
  }
}

//=============================================================================
int main(int argc, char* argv[]) {
  std::vector<std::thread> thread_pool(kPoolThreadCount);

  // Initialize the virtual constructor class.
  cmd_modules::VirtualConstructor::Instance()->Init();

  if (argc != 2) {
    std::cout << "Usage: async_command <command file>" << std::endl;
    return 1;
  }

  std::ifstream command_file(argv[1]);

  if (!command_file.is_open()) {
    std::cout << "Error: Can't open file." << std::endl;
    return 1;
  }

  for (auto& thread : thread_pool) {
    thread = std::thread(ThreadRoutine, &command_file);
  }

  for (auto& thread : thread_pool) {
    thread.join();
  }

  command_file.close();
}
