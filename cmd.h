// cmd.h
// Nathaniel Pohl 11/24/2015
// This file contains the class that must be derived to make new commands, and 
// the class that all derived classes must register with.
#ifndef CMD_H
#define CMD_H
#include <time.h>
#include <iostream>
#include <fstream>
#include <pthread.h>
#include <string>
#include <unordered_map>

using namespace std;

class Command{
private:
	string parameters;
public:
	Command();
	~Command();
	virtual Command* clone() = 0;
	virtual void deserialize(string str) = 0;
	virtual void execute() = 0;
	virtual string getCommandId() = 0;
};



class VirtualConstructor {
	VirtualConstructor();
	static VirtualConstructor* object;
	unordered_map<string, Command*> registry;
	pthread_mutex_t mtx;
public:
	~VirtualConstructor();
	static VirtualConstructor* instance();
	void registerCommand(Command *cmd) 
		{registry[cmd->getCommandId()] = cmd;}
	Command* getCommand(istream*);
};

// Initialize the Singleton to work properly.
VirtualConstructor* VirtualConstructor::object = 0;
#endif
