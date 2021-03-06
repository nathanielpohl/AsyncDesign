// This file contains the a derivative class of Command, that includes
// paramters needed for reading from a file.
#pragma once

#include <iostream>
#include <fstream>
#include <string>

#include "tools/csv_parser.h"

#include "cmd_modules/command.h"

namespace cmd_modules {
class FileCommand: public Command {
public:
	FileCommand(){}
	virtual ~FileCommand(){}
	virtual Command* Clone() = 0;
	virtual void Deserialize(tools::CSVParser &params) = 0;
	virtual int Execute() = 0;
	virtual std::string GetId() = 0;
protected:
	std::string filename_;
};
}
