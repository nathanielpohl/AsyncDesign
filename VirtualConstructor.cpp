// VirtualConstructor.cpp
// Nathaniel Pohl 11/24/2015
// This file contains the implmentation of VirtualConstructor.h the 
// class which keeps track of all implemented commands.
#include "VirtualConstructor.h"
#include <fstream>
#include <iostream>

using namespace std;


VirtualConstructor::VirtualConstructor(){
	pthread_mutex_init(&mtx, NULL);
}

VirtualConstructor::~VirtualConstructor(){
	pthread_mutex_destroy(&mtx);
}

VirtualConstructor* VirtualConstructor::instance(){
	if(!object)
		object = new VirtualConstructor;

	return object;
}

void VirtualConstructor::registerCommand(Command *cmd) {
	registry[cmd->getId()] = cmd;
}

Command* VirtualConstructor::createCommand(istream *commandFile){
	CSVParser params;
	//~ unordered_map<string, Command*>::const_itera
	Command* nextCommand = NULL;

	// Get a line that isn't commented or empty
	do{
		if(commandFile->eof()){
			return NULL;
		}

		string str;
		pthread_mutex_lock(&mtx);
		getline(*commandFile, str);
		pthread_mutex_unlock(&mtx);
		
		if(str.empty() || (str[0] == '#')){
			continue;
		}

		params.setRow(str);
		str = params.next();

		commandRegistry::const_iterator iter = registry.find(str);
		if(iter == registry.end()){
			str = "Error: Unregistered command: " + str + "\n";
			cout << str;
			continue;
		}
		nextCommand = registry[str];
	}while(!nextCommand);

	nextCommand = nextCommand->clone();
	nextCommand->deserialize(params);
	return nextCommand;
}

// Initialize the Singleton to work properly.
VirtualConstructor* VirtualConstructor::object = 0;
