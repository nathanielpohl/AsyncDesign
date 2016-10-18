// wordcount.cpp
// Nathaniel Pohl 11/26/2015
// This file contains the class derivative implmentation of a word count command
#include "wordcount.h"
#include <time.h>

void WordCount::deserialize(string str){
	filename = nextParameter(str)
}

void WordCount::execute(){
	clock_t time;
	double seconds;
	string word;

	file.open(filename);
        if(!file.is_open()){
                cout << "Error: Can't open file: " << filename << endl;
                return;
        }


	time = clock();

	while(file >> word){
                wordCount++;
        }

	time = clock() - time;
	seconds = double(time)/CLOCKS_PER_SEC;

        // Single prints are viewed as atomic, create a string, and print it.
        output = this->getCommandId() + ", " + filename + ", " +
                to_string(wordCount) + ", " + to_string(seconds) + "\n";
        cout << output;

        file.close();
}

WordCount wc;
VirtualConstructor::instance()->VirtualConstructor::registerCommand(&wc);
