# makefile
all: main

main.o: main.cpp Parser.h QueryNodes.h
	g++ -std=c++11 -c -g main.cpp -w
	
main: main.o 
	g++ -std=c++11 -I..\Engine\ -c -o main main.o
	
run:
	./main
	
c:
	rm *.o main