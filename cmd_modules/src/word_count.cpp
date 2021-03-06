// This file contains the class derivative implmentation of a word count
// command
#include "cmd_modules/word_count.h"

#include <time.h>

#include "tools/csv_parser.h"

namespace cmd_modules {
void WordCount::Deserialize(tools::CSVParser &params){
	filename_ = params.Next();
}

int WordCount::Execute(){
	ifstream file(filename_, ifstream::in);

	if(!file.is_open()){
		string error = "Error: Can't open file: " + filename_ + "\n";
		cout << error;
		return -1;
	}

	string word;
	clock_t time = clock();

	while(file >> word) {
		word_count_++;
	}

	time = clock() - time;
	double seconds = double(time)/CLOCKS_PER_SEC;

	// Single prints are viewed as atomic, create a string, and print it
	string output = GetId() + ", " + filename_ + ", " + to_string(word_count_) + 
			", " + to_string(seconds) + "\n";
	cout << output;

	return 0;
}

WordCount WordCountType(VirtualConstructor::Instance());
}
