CC=g++
FLAGS=-Wall -Wextra -std=c++11 -pthread
src=$(wildcard *.cpp)
objects= $(src:.cpp=.o)

Command: $(objects)
	$(CC) -o Command $(FLAGS)  $?

.cpp.o:
	$(CC) -c $(FLAGS) $<

clean:
	rm -f *.o *.gch
