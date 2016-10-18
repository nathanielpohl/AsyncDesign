// main.cpp
// Nathaniel Pohl 11/24/2015
// This file contains the logic to read in the command file and then spin off
// a thread pool, and than complete the work that is assigned in the command 
// file that is passed in on the command line.

#include "cmd.h"
//#include "checksum.h"
//#include "wordcount.h"
//#include "wordfreq.h"
#include <iostream>
#include <fstream>
#include <string>
#include <pthread.h>

using namespace std;

const int POOL_THREAD_COUNT = 16;

struct threadInfo {
	int threadId;
	istream* file;
}typedef threadInfo;

void* thread_routine(void* data){
	threadInfo* info = (threadInfo*) data;
	Command* currentCommand = NULL;

	while (true){
		currentCommand = VirtualConstructor::instance()->getCommand(
				info->file);
		if(currentCommand == NULL){
			break;
		}
		currentCommand->execute();	
		delete currentCommand;
	}
	
	pthread_exit(NULL);
}

int main(int argc, char* argv[]){
	pthread_t thread[POOL_THREAD_COUNT];
	pthread_attr_t attr;
	threadInfo info[POOL_THREAD_COUNT];
	int res;
	ifstream commandFile;
	void* status = NULL;

	if(argc != 2){
		cout << "Usage: cmdEx <command File>" << endl;
		return 1;
	}

	commandFile.open(argv[1]);

	if(!commandFile.is_open()){
		cout << "Error: Can't open file." << endl;
		return 1;
	}

	pthread_attr_init(&attr);

	for(int i = 0; i < POOL_THREAD_COUNT; i++){
		info[i].threadId = i;
		info[i].file = &commandFile;
		res = pthread_create(&thread[i], &attr, thread_routine,
				(void *) &info[i]);
		if(res){
			cout << "Error: Can't create thread: " << i << endl;
		}
	}
	
	pthread_attr_destroy(&attr);

	for(int i = 0; i < POOL_THREAD_COUNT; i++){
		pthread_join(thread[i], &status);
		if(status){
			cout << "Error: Joining thread: " << i << endl;
		}
	}
	
	commandFile.close();

	pthread_exit(NULL);
}
