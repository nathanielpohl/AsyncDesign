// Command.h
// Nathaniel Pohl 11/24/2015
// This file contains the base class that must be derived to make new
// commands.
#ifndef COMMAND_H
#define COMMAND_H
#include "CSVParser.h"
#include <string>

using namespace std;


class Command{
public:
	Command(){}
	virtual ~Command(){}
	virtual Command* clone() = 0;
	virtual void deserialize(CSVParser &params) = 0;
	virtual int execute() = 0;
	virtual string getId() = 0;
};

#endif
