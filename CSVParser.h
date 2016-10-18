// CSVParser.h
// Nathaniel Pohl 11/30/2015
// This file contains the definition of the string parsing classes to
// read commamd files more easily.
#ifndef CSVPARSER_H
#define CSVPARSER_H
#include <string>

using namespace std;


class CSVParser {
	string row;

	void trimFront(string &line) const;
	void trimBack(string &line) const;
public:
	CSVParser(){}
	CSVParser(const string &str);
	void setRow(const string &str);
	string next();
};

#endif
