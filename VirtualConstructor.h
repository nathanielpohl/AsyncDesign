// VirtualConstructor.h
// Nathaniel Pohl 11/24/2015
// This file contains the class that all deveritive classes of Command
// have to register with to be recognized by main program.
#ifndef VIRTUALCONSTRUCTOR_H
#define VIRTUALCONSTRUCTOR_H
#include "Command.h"
#include "CSVParser.h"
#include <pthread.h>
#include <string>
#include <unordered_map>

using namespace std;


class VirtualConstructor {
	VirtualConstructor();
	static VirtualConstructor* object;

	typedef unordered_map<string, Command*> commandRegistry;

	//~ unordered_map<string, Command*> registry;
	commandRegistry registry;
	pthread_mutex_t mtx;
public:
	~VirtualConstructor();
	static VirtualConstructor* instance();
	void registerCommand(Command *cmd);
	Command* createCommand(istream*);
};

#endif
