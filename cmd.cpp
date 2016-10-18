// cmd.cpp
// Nathaniel Pohl 11/24/2015
// This file contains the implmentation of cmd.h the command tracking class and
// thread pool class.
#include "cmd.h"
//#include <ifstream>
//#include <string>

using namespace std;

Command::Command(){
	// Nothing to initialize
}

Command::~Command(){
	// 'new' wasn't called, nothing to implement.
}

VirtualConstructor::VirtualConstructor(){
	pthread_mutex_init(&mtx, NULL);
}
		
VirtualConstructor::~VirtualConstructor(){
	pthread_mutex_destroy(&mtx);
}

VirtualConstructor* VirtualConstructor::instance(){
	if(!object){
		object = new VirtualConstructor;
	}
	return object;
}

void trimFront(string &line){
	size_t i = line.find_first_not_of(" \t");
	if(string::npos != i){
		line = line.substr(i);
	}
}

void trimBack(string &line){
	size_t i = line.find_last_not_of(" \t");
	if(string::npos != i){
		line = line.substr(0, i+1);
	}
}

string nextParameter(string &parameters){
	size_t i;
	string next = "";

	trimFront(parameters);
	trimBack(parameters);

	if(parameters.empty()){
		return next;
	}

	i = parameters.find(",");
	if(string::npos != i){
		next = parameters.substr(0, i);
		parameters.erase(0, i+1);
		trimFront(parameters);
		trimBack(next);
	}
	else {
		next = parameters;
		parameters.clear();
	}

	return next;
}


Command* VirtualConstructor::getCommand(istream* commandFile){
	string parameters;
	string commandName;
	Command* nextCommand = NULL;

	
	// Get a line that isn't commented or empty
	do{
		if(commandFile->eof()){
			return NULL;
		}

		pthread_mutex_lock(&mtx);
		getline(*commandFile, parameters);
		pthread_mutex_unlock(&mtx);
		
		if(parameters.empty() || (parameters[0] == '#')){
			continue;
		}

		commandName = nextParameter(parameters);
		
		nextCommand = registry[commandName];

	}while(!nextCommand);

	nextCommand = nextCommand->clone();
	nextCommand->deserialize(parameters);
	return nextCommand;
}


