CC=g++
FLAGS=-Wall -Wextra -std=c++11
objects= main.o cmd.o checksum.o wordcount.o wordfreq.o

cmdEx: $(objects)
	$(CC) -o $(FLAGS) $@ $?

.cpp.o:
	$(CC) -c $(FLAGS) $<

clean:
	rm -f *.o *.gch
