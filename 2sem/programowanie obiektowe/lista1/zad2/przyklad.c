#include<stdio.h>
#include<stdlib.h>
#include"funkcje.h"

int main(void)
{
    Ulamek *u1;
    Ulamek *u2;
    Ulamek *u;
    int a,b;

    printf("TEST 1:\n");
    printf("Podaj pierwszy ulamek (licznik i mianownik) : \n");
    scanf("%d %d",&a,&b);
    u1=nowy_ulamek(a,b);
    printf("Podaj drugi ulamek (licznik i mianownik) : \n");
    scanf("%d %d",&a,&b);
    u2=nowy_ulamek(a,b);
    printf("Twoje ulamki to: \n");
    wypisz_ulamek(u1);
    wypisz_ulamek(u2);
    printf("Suma podanych ulamkow to: ");
    u=dodaj(u1,u2);
    wypisz_ulamek(u);
    printf("Roznica podanych ulamkow to: ");
    u=odejmij(u1,u2);
    wypisz_ulamek(u);
    printf("Iloczyn podanych ulamkow to: ");
    u=pomnoz(u1,u2);
    wypisz_ulamek(u);
    printf("Iloraz podanych ulamkow to: ");
    u=podziel(u1,u2);
    wypisz_ulamek(u);

    printf("TEST 2:\n");
    printf("Podaj pierwszy ulamek (licznik i mianownik) : \n");
    scanf("%d %d",&a,&b);
    nowy_ulamek2(a,b,u1);
    printf("Podaj drugi ulamek (licznik i mianownik) : \n");
    scanf("%d %d",&a,&b);
    nowy_ulamek2(a,b,u2);
    printf("Twoje ulamki to: \n");
    wypisz_ulamek(u1);
    wypisz_ulamek(u2);
    printf("Suma podanych ulamkow to: ");
    dodaj2(u1,u2,u);
    wypisz_ulamek(u);
    printf("Roznica podanych ulamkow to: ");
    odejmij2(u1,u2,u);
    wypisz_ulamek(u);
    printf("Iloczyn podanych ulamkow to: ");
    pomnoz2(u1,u2,u);
    wypisz_ulamek(u);
    printf("Iloraz podanych ulamkow to: ");
    podziel2(u1,u2,u);
    wypisz_ulamek(u);
    return 0;
}
