CC=gcc
CFLAGS = -Wall	\
	-Wextra \
	-Werror
NAZWA = przyklad

all: przyklad.o zad2.o
	$(CC) -o $(NAZWA) przyklad.o zad2.o
przyklad.o: przyklad.c funkcje.h
	$(CC) -c przyklad.c $(CFLAGS)
zad2.o: zad2.c funkcje.h
	$(CC) -c zad2.c $(CFLAGS)

