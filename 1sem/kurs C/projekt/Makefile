CC=g++
CFLAGS = `pkg-config --cflags gtk+-3.0` 
	#-Wall	\
	#-Wextra \
	#-Werror
NAZWA = program
LIBS=`pkg-config --libs gtk+-3.0`

all: main.o menu.o obsluga.o granie.o ruchy.o komunikaty.o algorytm.o algorytmodp.o
	$(CC) -o $(NAZWA) main.o menu.o obsluga.o granie.o ruchy.o komunikaty.o algorytm.o algorytmodp.o $(LIBS)
main.o: main.cpp main.hpp obsluga.hpp
	$(CC) -c main.cpp $(CFLAGS)
menu.o: menu.cpp obsluga.hpp main.hpp
	$(CC) -c menu.cpp $(CFLAGS)
obsluga.o: obsluga.cpp obsluga.hpp main.hpp
	$(CC) -c obsluga.cpp $(CFLAGS)
granie.o: granie.cpp granie.hpp main.hpp obsluga.hpp ruchy.hpp algorytm.hpp
	$(CC) -c granie.cpp $(CFLAGS)
ruchy.o: ruchy.cpp ruchy.hpp main.hpp obsluga.hpp komunikaty.hpp granie.hpp
	$(CC) -c ruchy.cpp $(CFLAGS)
komunikaty.o: komunikaty.cpp komunikaty.hpp obsluga.hpp granie.hpp ruchy.hpp main.hpp algorytm.hpp
	$(CC) -c komunikaty.cpp $(CFLAGS)
algorytm.o: algorytm.cpp ruchy.hpp algorytm.hpp komunikaty.hpp
	$(CC) -c algorytm.cpp $(CFLAGS)
algorytmodp.o: algorytmodp.cpp algorytmodp.hpp ruchy.hpp algorytm.hpp komunikaty.hpp
	$(CC) -c algorytmodp.cpp $(CFLAGS)

