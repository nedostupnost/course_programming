all: compiling linking clear 

compiling:
	clang -Wall -c main.c wordsCount.c

linking:
	clang main.o wordsCount.o -o main

run:
	./main

clear:
	rm *.o