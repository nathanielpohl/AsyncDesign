:warning: | This README is outdate as of 5/27/2021, sorry! Read/modify the setup.sh to get started.
:---: | :---

# AsyncDesign
An asynchronous, independent-command running program.

## Make Instruction:

### Dependancies: 
g++ compiler that implements c++11 or greater and pthreads
### To make run:
```bash
make
./Command <command file>
```


## Overview:
My implementation spins off a thread pool. Each thread invokes the 
VirtualConstructor singleton class to create a new command. The threads pass an 
istream* to the VirtualConstructor so that the input file can be arbitrarely
long. The abstract Command class is derived to to create new commands. When a 
thread invokes the createCommand() member function in VirtualConstructor, a 
Command derivatie is identified in the member variable registy<string,command*>
and cloned. This new Command is then passed back to the thread to be exicuted.


## Assumptions:
The number of threads will be constant the entire run time.

Commands will only read from files, never write.

Whitespace in a command file is unimportant.

Future child classes of Command will only write to standard out by printing a single string (since single prints are atomic)

There are no dependancies on the results of earlier commands.

WordCount: A blank word parameter in word count will return the count of all characters in the file.

Errors in the command file are non-fatal to the entire program, but should be reported to std::out.


## Extending New Commands:

To extend my implementation just create a new <class>.h and <class>.cpp and inherate one of the abstracts; Command or FileCommand. Make sure to implament a constructor that takes a VirtualConstructor*, and to create a global instance of the newly implemented Command derivative with this constructor. The make file will automatically pick up new *.cpp file, and the VirtualConstructor singleton
will keep track of the newly registered command.


## Future Thoughts:

Create another abstract class from Command that will keep track of input files	and mutexes so that it can be derived into a class that allows writing to files to be thread safe.


Allowing file dependancies fix:

1. Either change the Command file sytax to state that one command relieson another's completion or

2. Take a performance hit, disallow abitrarely long input files and parse the entire command file at once to resolve dependancies at runtime.


Add logic to allow either the command file to specify how many threads it wants and when to change the thread pool size, or allow the program to automatically scale the number of threads based off of such factors as time to complete current commands, number of cores, predicted amount of time to complete next command, etc.


Write a linux driver that takes in commands from various sources and pipes them into my program's command file istream, and redirect the std::out output of my program to something specific stream for those aggregated sources.


## Class Diagram: 

```
 +-------+  n           1  +---------------------+    uses
 |Command|<---------------O|VirtualConstructor   |----------+
 +-------+                 +---------------------+          |
 |       |<----------------|registry(id, command)|          v
 +---+---+     creates     +---------------+-----+    +-----+---+
     ^                                     ^          |CSVParser|
     | inherits                            |          +---------+
 +---+-------+                             |          |row      |
 |FileCommand|                             |          +---------+
 +-----------+                             |
 |filname    |                             |
 +-----+-----+                             |
       ^          inherits                 |
    +--+----------+------------+           |
    |             |            |           |
+---+----+   +----+----+  +----+---+       |
|Checksum|   |WordCount|  |WordFreq|       |
+--------+   +---------+  +--------+       |
|checksum|   |wordCount|  |wordFreq|       |
+---+----+   +----+----+  +----+---+       |
    |             |            |           |
    +-------------+------------+-----------+
              registers
```
