// FileCommand.h
// Nathaniel Pohl 11/30/2015
// This file contains the a derivative class of Command, that includes
// paramters needed for reading from a file.
#ifndef FILECOMMAND_H
#define FILECOMMAND_H
#include "Command.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;


class FileCommand: public Command {
protected:
	string filename;
public:
	FileCommand(){}
	virtual ~FileCommand(){}
	virtual Command* clone() = 0;
	virtual void deserialize(CSVParser &params) = 0;
	virtual int  execute() = 0;
	virtual string getId() = 0;
};

#endif
