// This file contains the implmentation of virtual_constructor.h the
// class which keeps track of all implemented commands.
#include "async_design/virtual_constructor.h"

#include <glog/logging.h>

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
void VirtualConstructor::Init(std::ifstream* command_file) {
  if (init_) {
    LOG(ERROR) << "VirtualConsturctor is already initialized.";
    return;
  }
  init_ = true;

#define REGISTER_COMMAND(scope, name, command_id)                    \
  do {                                                               \
    auto COMMAND_##name = std::make_unique<scope::name>(command_id); \
    registry_[command_id] = std::move(COMMAND_##name);               \
  } while (0);
  LIST_OF_COMMANDS(REGISTER_COMMAND);
#undef REGISTER_COMMAND

  command_file_ = command_file;
}

//=============================================================================
void VirtualConstructor::Execute() {
  if (init_ == false) {
    LOG(ERROR) << "VirtualConstructor is not initailized.";
    return;
  }

  while (true) {
    tools::Command* current_command =
        async_design::VirtualConstructor::Instance()->CreateCommand();
    if (!current_command) break;

    current_command->Execute();
    delete current_command;
  }
}

//=============================================================================
VirtualConstructor* VirtualConstructor::Instance() {
  if (!object_) object_ = new VirtualConstructor;

  return object_;
}

//=============================================================================
tools::Command* VirtualConstructor::CreateCommand() {
  tools::CSVParser params;
  std::string next_command;

  // Get a line that isn't commented or empty
  do {
    if (command_file_->eof()) {
      return NULL;
    }

    mtx_.lock();
    getline(*command_file_, next_command);
    mtx_.unlock();

    if (next_command.empty() || (next_command[0] == '#')) {
      continue;
    }

    params.SetRow(next_command);
    next_command = params.Next();

    CommandRegistry::const_iterator iter = registry_.find(next_command);
    if (iter == registry_.end()) {
      LOG(ERROR) << "Unregistered command: " << next_command;
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
