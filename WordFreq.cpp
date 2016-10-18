// WordFreq.cpp
// Nathaniel Pohl 11/24/2015
// This file contains the derivative class of a word freqncy commmand
#include "WordFreq.h"
#include <time.h>

void WordFreq::deserialize(CSVParser &params){
	filename = params.next();
	word = params.next();
}

int WordFreq::execute(){
	ifstream file(filename, ifstream::in);
	
	if(!file.is_open()){
		string error = "Error: Can't open file: " + filename + "\n";
		cout << error;
		return -1;
	}

	string line;
	clock_t time = clock();

	while(getline(file, line)){
		size_t find = line.find(word);
		if(find == string::npos)
			continue;

		do {
			find = line.find(word, find + 1);
			freqCount++;
		} while(string::npos != find);
	}

	time = clock() - time;
	double seconds = double(time)/CLOCKS_PER_SEC;

	// Single prints are viewed as atomic, create a string, and print it
	string output = getId() + ", " + filename + ", " + word + ", " +
			to_string(freqCount) + ", " + to_string(seconds) + "\n";
	cout << output;

	return 0;
}

WordFreq WordFreqType(VirtualConstructor::instance());
