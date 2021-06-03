// This file contains the class that all deveritive classes of Command
// have to register with to be recognized by main program.
#pragma once

#include <atomic>
#include <memory>
#include <mutex>
#include <string>
#include <unordered_map>

#include "tools/command.h"

namespace async_design {
class VirtualConstructor {
 public:
  ~VirtualConstructor();
  void Init(std::ifstream* command_file);
  void Execute();
  static VirtualConstructor* Instance();

 private:
  VirtualConstructor();
  tools::Command* CreateCommand();

  static VirtualConstructor* object_;

  typedef std::unordered_map<std::string, std::unique_ptr<tools::Command>>
      CommandRegistry;

  std::atomic_bool init_ = false;
  CommandRegistry registry_;
  std::mutex mtx_;
  std::ifstream* command_file_;
};
}  // namespace async_design
