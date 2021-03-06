// This file contains the class that all deveritive classes of Command
// have to register with to be recognized by main program.
#pragma once

#include <pthread.h>
#include <string>
#include <unordered_map>

#include "cmd_modules/command.h"

namespace cmd_modules {
using namespace std;

class VirtualConstructor {
	static VirtualConstructor* object_;

	typedef unordered_map<string, Command*> CommandRegistry;

	CommandRegistry registry_;
	pthread_mutex_t mtx_;

	VirtualConstructor();
public:
	~VirtualConstructor();
	static VirtualConstructor* Instance();
	void RegisterCommand(Command *cmd);
	Command* CreateCommand(istream*);
};
}

