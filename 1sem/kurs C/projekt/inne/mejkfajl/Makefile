CC=g++
all: pierwszy.o dodawanie.o
	$(CC) pierwszy.o dodawanie.o -o program
pierwszy.o: pierwszy.cpp naglowek.hpp
	$(CC) pierwszy.cpp -c -o pierwszy.o
dodawanie.o: dodawanie.cpp naglowek.hpp
	$(CC) dodawanie.cpp -c -o dodawanie.o
