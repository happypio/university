#ifndef funkcje_h
#define funkcje_h

typedef struct Ulamek{
	int licznik;
	int mianownik;
}Ulamek;

Ulamek *nowy_ulamek(int licznik, int mianownik);
void nowy_ulamek2(int licznik,int mianownik, Ulamek *u);
Ulamek *dodaj(Ulamek *u1, Ulamek *u2);
void dodaj2(Ulamek *u1, Ulamek *u2, Ulamek *u);
Ulamek *odejmij(Ulamek *u1, Ulamek *u2);
void odejmij2(Ulamek *u1, Ulamek *u2, Ulamek *u);
Ulamek *pomnoz(Ulamek *u1, Ulamek *u2);
void pomnoz2(Ulamek *u1,Ulamek *u2, Ulamek *u);
Ulamek *podziel(Ulamek *u1, Ulamek *u2);
void podziel2(Ulamek *u1, Ulamek *u2, Ulamek *u);
void wypisz_ulamek(Ulamek *u);
#endif
