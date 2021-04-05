// This file contains the implmentation of virtual_constructor.h the
// class which keeps track of all implemented commands.
#include "async_design/virtual_constructor.h"

#include <fstream>
#include <iostream>

#include "async_design/command_modules.h"
#include "tools/csv_parser.h"

namespace async_design {
//=============================================================================
VirtualConstructor::VirtualConstructor() = default;

//=============================================================================
VirtualConstructor::~VirtualConstructor() = default;

//=============================================================================
void VirtualConstructor::Init() {
#define REGISTER_COMMAND(scope, name, command_id)                    \
  do {                                                               \
    auto COMMAND_##name = std::make_unique<scope::name>(command_id); \
    registry_[command_id] = std::move(COMMAND_##name);               \
  } while (0);
  LIST_OF_COMMANDS(REGISTER_COMMAND);
#undef REGISTER_COMMAND
}

//=============================================================================
VirtualConstructor* VirtualConstructor::Instance() {
  if (!object_) object_ = new VirtualConstructor;

  return object_;
}

//=============================================================================
tools::Command* VirtualConstructor::CreateCommand(std::istream* command_file) {
  tools::CSVParser params;
  std::string next_command;

  // Get a line that isn't commented or empty
  do {
    if (command_file->eof()) {
      return NULL;
    }

    mtx_.lock();
    getline(*command_file, next_command);
    mtx_.unlock();

    if (next_command.empty() || (next_command[0] == '#')) {
      continue;
    }

    params.SetRow(next_command);
    next_command = params.Next();

    CommandRegistry::const_iterator iter = registry_.find(next_command);
    if (iter == registry_.end()) {
      std::cout << "Error: Unregistered command: " << next_command << std::endl;
      continue;
    }
  } while (!registry_[next_command]);

  auto cloned_command = registry_[next_command]->Clone();
  cloned_command->Deserialize(params);
  return cloned_command;
}

//=============================================================================
// Initialize the Singleton to work properly.
VirtualConstructor* VirtualConstructor::object_ = 0;
}  // namespace async_design