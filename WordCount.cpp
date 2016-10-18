// wordcount.cpp
// Nathaniel Pohl 11/26/2015
// This file contains the class derivative implmentation of a word count
// command
#include "WordCount.h"
#include <time.h>

void WordCount::deserialize(CSVParser &params){
	filename = params.next();
}

int WordCount::execute(){
	ifstream file(filename, ifstream::in);

	if(!file.is_open()){
		string error = "Error: Can't open file: " + filename + "\n";
		cout << error;
		return -1;
	}

	string word;
	clock_t time = clock();

	while(file >> word) {
		wordCount++;
	}

	time = clock() - time;
	double seconds = double(time)/CLOCKS_PER_SEC;

	// Single prints are viewed as atomic, create a string, and print it
	string output = getId() + ", " + filename + ", " + to_string(wordCount) + 
			", " + to_string(seconds) + "\n";
	cout << output;

	return 0;
}

WordCount WordCountType(VirtualConstructor::instance());
