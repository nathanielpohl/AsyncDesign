// CSVParser.cpp
// Nathaniel Pohl 11/30/2015
// This file contains the implmentation of SCVParser.h the 
// class which cleanly takes apart messy strings for Command, 
// VirtualConstructor, and all derivative classes there of.
#include "CSVParser.h"

using namespace std;


void CSVParser::trimFront(string &line) const {
	size_t i = line.find_first_not_of(" \t");
	if(string::npos != i){
		line = line.substr(i);
	}
}

void CSVParser::trimBack(string &line) const {
	size_t i = line.find_last_not_of(" \t");
	if(string::npos != i){
		line = line.substr(0, i+1);
	}
}

CSVParser::CSVParser(const string &str) {
	row.assign(str);
	trimFront(row);
	trimBack(row);
}

void CSVParser::setRow(const string &str){
	row.assign(str);
	trimFront(row);
	trimBack(row);
}

string CSVParser::next(){
	size_t i;
	string next;

	if(row.empty()){
		return next;
	}

	i = row.find(",");
	if(string::npos != i){
		next = row.substr(0, i);
		row.erase(0, i+1);
		trimFront(row);
		trimBack(next);
	}
	else {
		next = row;
		row.clear();
	}

	return next;
}
