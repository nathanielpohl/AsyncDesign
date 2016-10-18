// WordCount.h
// Nathaniel Pohl 11/26/2015
// This file contains the derivative class for a word count command.
#ifndef WORDCOUNT_H
#define WORDCOUNT_H
#include "FileCommand.h"
#include "VirtualConstructor.h"

using namespace std;


class WordCount: public FileCommand{
private:
	unsigned int wordCount;
public:
	WordCount() { wordCount = 0;}
	WordCount(VirtualConstructor* VC)
		{VC->registerCommand(this);}
	Command* clone(){ return new WordCount;}
	void deserialize(CSVParser &params);
	int execute();
	string getId(){ return "WORDCOUNT";}
};

#endif
