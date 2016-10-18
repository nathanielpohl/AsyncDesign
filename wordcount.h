// wordcount.h
// Nathaniel Pohl 11/26/2015
// This file contains the class derivative for a word count command.
#ifndef WORDCOUNT_H
#define WORDCOUNT_H
#include "cmd.h"
//#include <string>
//#include <ifstream>

using namespace std;

class WordCount: public Command{
private:
	string filename;
	ifstream file;
	unsigned int wordCount;
public:
	Command* clone(){ return new WordCount;}
	void deserialize(string);
	void execute();
	string getCommandId(){ return "WORDCOUNT";}
};

#endif
