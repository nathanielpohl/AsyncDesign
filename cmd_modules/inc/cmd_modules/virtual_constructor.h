// This file contains the class that all deveritive classes of Command
// have to register with to be recognized by main program.
#pragma once

#include <pthread.h>

#include <memory>
#include <string>
#include <unordered_map>

#include "cmd_modules/command.h"

namespace cmd_modules {
using namespace std;

class VirtualConstructor {
 public:
  ~VirtualConstructor();
  void Init();
  static VirtualConstructor* Instance();
  Command* CreateCommand(istream*);

 private:
  static VirtualConstructor* object_;

  typedef unordered_map<string, std::unique_ptr<Command>> CommandRegistry;

  CommandRegistry registry_;
  pthread_mutex_t mtx_;

  VirtualConstructor();
};
}  // namespace cmd_modules
