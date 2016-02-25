
# makefile
all: main

main.o: main.cpp Engine.h Header.h Table.h
	g++ -std=c++11 -c -g main.cpp

main: main.o
	g++ -std=c++11 -g -o main main.o
	
run:
	./main

c:
	rm *.o main
