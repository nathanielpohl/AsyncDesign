// This file contains the class that all deveritive classes of Command
// have to register with to be recognized by main program.
#pragma once

#include <pthread.h>

#include <memory>
#include <string>
#include <unordered_map>

#include "tools/command.h"

namespace cmd_modules {
class VirtualConstructor {
 public:
  ~VirtualConstructor();
  void Init();
  static VirtualConstructor* Instance();
  tools::Command* CreateCommand(std::istream* command_file);

 private:
  static VirtualConstructor* object_;

  typedef std::unordered_map<std::string, std::unique_ptr<tools::Command>>
      CommandRegistry;

  CommandRegistry registry_;
  pthread_mutex_t mtx_;

  VirtualConstructor();
};
}  // namespace cmd_modules
