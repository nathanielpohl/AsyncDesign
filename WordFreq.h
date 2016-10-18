// WordFreq.h
// Nathaniel Pohl 11/26/2015
// This file contains the derivative class for a word frequncy command.
#ifndef WORDFREQ_H
#define WORDFREQ_H
#include "FileCommand.h"
#include "VirtualConstructor.h"
#include <string>

using namespace std;


class WordFreq: public FileCommand{
private:
	string word;
	unsigned int freqCount;
public:
	WordFreq(){ freqCount = 0;}
	WordFreq(VirtualConstructor* VC)
		{VC->registerCommand(this);}
	Command* clone(){ return new WordFreq;}
	void deserialize(CSVParser &params);
	int execute();
	string getId(){ return "WORDFREQ";}
};

#endif
