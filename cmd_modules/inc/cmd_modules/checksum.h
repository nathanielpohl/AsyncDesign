// This file contains the class derivative for a checksum command.
#pragma once

#include <string>

#include "tools/csv_parser.h"

#include "cmd_modules/virtual_constructor.h"
#include "cmd_modules/file_command.h"

namespace cmd_modules {
class Checksum: public FileCommand{
public:
	Checksum(){ checksum_ = 0;}
	Checksum(VirtualConstructor* VC)
		{VC->RegisterCommand(this);}
	Checksum* Clone(){ return new Checksum;}
	void Deserialize(tools::CSVParser &params);
	int Execute();
	std::string GetId(){ return "CHECKSUM";}
private:
	unsigned char checksum_;
};

}
