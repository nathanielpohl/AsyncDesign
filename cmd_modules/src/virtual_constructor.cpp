// This file contains the implmentation of virtual_constructor.h the
// class which keeps track of all implemented commands.
#include "cmd_modules/virtual_constructor.h"

#include <fstream>
#include <iostream>

#include "tools/csv_parser.h"

namespace cmd_modules {
//=============================================================================
VirtualConstructor::VirtualConstructor() { pthread_mutex_init(&mtx_, NULL); }

//=============================================================================
VirtualConstructor::~VirtualConstructor() { pthread_mutex_destroy(&mtx_); }

//=============================================================================
VirtualConstructor* VirtualConstructor::Instance() {
  if (!object_) object_ = new VirtualConstructor;

  return object_;
}

//=============================================================================
void VirtualConstructor::RegisterCommand(Command* cmd) {
  registry_[cmd->GetId()] = cmd;
}

//=============================================================================
Command* VirtualConstructor::CreateCommand(istream* command_file) {
  tools::CSVParser params;
  Command* next_command = NULL;

  // Get a line that isn't commented or empty
  do {
    if (command_file->eof()) {
      return NULL;
    }

    std::string str;
    pthread_mutex_lock(&mtx_);
    getline(*command_file, str);
    pthread_mutex_unlock(&mtx_);

    if (str.empty() || (str[0] == '#')) {
      continue;
    }

    params.SetRow(str);
    str = params.Next();

    CommandRegistry::const_iterator iter = registry_.find(str);
    if (iter == registry_.end()) {
      str = "Error: Unregistered command: " + str + "\n";
      std::cout << str;
      continue;
    }
    next_command = registry_[str];
  } while (!next_command);

  next_command = next_command->Clone();
  next_command->Deserialize(params);
  return next_command;
}

//=============================================================================
// Initialize the Singleton to work properly.
VirtualConstructor* VirtualConstructor::object_ = 0;
}  // namespace cmd_modules
