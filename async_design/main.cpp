// This file contains the logic to read in the command file and then
// spin off a thread pool, and than complete the work that is assigned
// in the command file that is passed in on the command line.
#include <pthread.h>

#include <fstream>
#include <iostream>
#include <string>

#include "cmd_modules/virtual_constructor.h"
#include "tools/command.h"

static constexpr int kPoolThreadCount = 4;

//=============================================================================
struct ThreadInfo {
  int thread_id;
  std::istream* file;
};

//=============================================================================
void* ThreadRoutine(void* data) {
  ThreadInfo* info = static_cast<ThreadInfo*>(data);

  while (true) {
    tools::Command* current_command =
        cmd_modules::VirtualConstructor::Instance()->CreateCommand(info->file);
    if (!current_command) break;

    current_command->Execute();
    delete current_command;
  }

  pthread_exit(NULL);
}

//=============================================================================
int main(int argc, char* argv[]) {
  pthread_t thread[kPoolThreadCount];
  pthread_attr_t attr;
  ThreadInfo info[kPoolThreadCount];
  int res;
  void* status = NULL;

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

  pthread_attr_init(&attr);

  for (int i = 0; i < kPoolThreadCount; i++) {
    info[i].thread_id = i;
    info[i].file = &command_file;
    res = pthread_create(&thread[i], &attr, ThreadRoutine, (void*)&info[i]);
    if (res) {
      std::cout << "Error: Can't create thread: " << std::to_string(i)
                << std::endl;
    }
  }

  pthread_attr_destroy(&attr);

  for (int i = 0; i < kPoolThreadCount; i++) {
    pthread_join(thread[i], &status);
    if (status) {
      std::cout << "Error: Joining thread: " << std::to_string(i) << std::endl;
    }
  }

  command_file.close();

  pthread_exit(NULL);
}
