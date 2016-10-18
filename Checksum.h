// Checksum.h
// Nathaniel Pohl 11/26/2015
// This file contains the class derivative for a checksum command.
#ifndef CHECKSUM_H
#define CHECKSUM_H
#include "FileCommand.h"
#include "VirtualConstructor.h"
#include <string>

using namespace std;

class Checksum: public FileCommand{
private:
	unsigned char checksum;
public:
	Checksum(){ checksum = 0;}
	Checksum(VirtualConstructor* VC)
		{VC->registerCommand(this);}
	Checksum* clone(){ return new Checksum;}
	void deserialize(CSVParser &params);
	int execute();
	string getId(){ return "CHECKSUM";}
};


#endif
