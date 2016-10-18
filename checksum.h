// checksum.h
// Nathaniel Pohl 11/26/2015
// This file contains the class derivative for a checksum command.
#ifndef CHECKSUM_H
#define CHECKSUM_H
#include "cmd.h"
#include <string>
//#include <iostream>
//#include <fstream>

using namespace std;

class Checksum: public Command{
private:
	string filename;
	ifstream file;
	unsigned char checksum;
public:
	Checksum* clone(){ return new Checksum;}
	void deserialize(string);
	void execute();
	string getCommandId(){ return "CHECKSUM";}
};


#endif
