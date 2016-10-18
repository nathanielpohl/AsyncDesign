// wordfreq.h
// Nathaniel Pohl 11/26/2015
// This file contains the class derivative for a word frequncy command.
#ifndef WORDFREQ_H
#define WORDFREQ_H
#include "cmd.h"
#include <string>
//#include <ifstream>

using namespace std;

class WordFreq: public Command{
private:
	string word;
	string filename;
	ifstream file;
	unsigned int freqCount;
public:
	Command* clone(){ return new WordFreq;}
	void deserialize (string);
	void execute();
	string getCommandId(){ return "WORDFREQ";}
};

#endif
