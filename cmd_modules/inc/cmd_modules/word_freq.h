// This file contains the derivative class for a word frequncy command.
#pragma once

#include <string>

#include "tools/csv_parser.h"

#include "cmd_modules/file_command.h"
#include "cmd_modules/virtual_constructor.h"

namespace cmd_modules {
class WordFreq: public FileCommand{
public:
	WordFreq(){ freq_count_ = 0;}
	WordFreq(VirtualConstructor* VC)
		{VC->RegisterCommand(this);}
	Command* Clone(){ return new WordFreq;}
	void Deserialize(tools::CSVParser &params);
	int Execute();
	std::string GetId(){ return "WORDFREQ";}
private:
	std::string word_;
	unsigned int freq_count_;
};
}
