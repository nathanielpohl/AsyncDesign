// This file contains the derivative class for a word count command.
#pragma once

#include <string>

#include "tools/csv_parser.h"

#include "cmd_modules/file_command.h"
#include "cmd_modules/virtual_constructor.h"

namespace cmd_modules {
class WordCount: public FileCommand{
public:
	WordCount() { word_count_ = 0;}
	WordCount(VirtualConstructor* VC)
		{VC->RegisterCommand(this);}
	Command* Clone(){ return new WordCount;}
	void Deserialize(tools::CSVParser &params);
	int Execute();
	std::string GetId(){ return "WORDCOUNT";}
private:
	unsigned int word_count_;
};
}
