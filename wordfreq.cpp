// wordfreq.cpp
// Nathaniel Pohl 11/24/2015
// This file contains the class derivative implmentation of a word freqncy 
#include "wordfreq.h"
#include <time.h>

void WordFreq::deserialize(string str){
	filename = nextParameter(str);
	word = nextParameter(str);
}

void WordFreq::execute(){
	clock_t time;
	double seconds;
	string line;
        size_t find = 0;

        file.open(filename);
        if(!file.is_open()){
                cout << "Error: Can't open file: " << filename << endl;
                return;
        }

	time = clock();

	while(getline(file, line)){
                find = line.find(word);
                if(find == string::npos){
                        continue;
                }
                do{
                        find = line.find(word, find + 1);
                        freqCount++;
                }while(string::npos != find);
        }

	time = clock() - time;
	seconds = double(time)/CLOCKS_PER_SEC;

        // Single prints are viewed as atomic, create a string, and print it.
        output = this->getCommandId() + ", " + filename + ", " + word + ", " +
                to_string(freqCount) + ", " + to_string(seconds) + "\n";
        cout << output;

        file.close();
}

WordFreq wf;
VirtualConstructor::instance()->VirtualConstructor::registerCommand(&wf);
