CC=gcc
CFLAGS = -Wall	\
	-Wextra \
	-Werror
NAZWA = przyklad

all: przyklad.o zad1.o
	$(CC) -o $(NAZWA) przyklad.o zad1.o
przyklad.o: przyklad.c funkcje.h
	$(CC) -c przyklad.c $(CFLAGS)
zad1.o: zad1.c funkcje.h
	$(CC) -c zad1.c $(CFLAGS)

