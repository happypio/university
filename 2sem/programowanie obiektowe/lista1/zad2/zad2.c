#include<stdio.h>
#include<stdlib.h>
#include"funkcje.h"
int NWD(int a, int b)
{
    if(a<0)
        a=-a;
    if(b<0)
        b=-b;
    while(a!=b)
       if(a>b)
           a-=b;
       else
           b-=a;
    return a;
}

int NWW(int a, int b)
{
    return (a*b)/NWD(a,b);
}
Ulamek *nowy_ulamek(int licznik, int mianownik)
{
    Ulamek *u=(Ulamek*)calloc(sizeof(Ulamek),1);
    if(mianownik<0){
        licznik*=(-1);
        mianownik*=(-1);
    }
    if(mianownik==0){
        printf("BLAD! ZLY ULAMEK!\n");
        return u;
        }
    int dzielnik= NWD(licznik,mianownik);
    licznik/=dzielnik;
    mianownik/=dzielnik;
    u->licznik=licznik;
    u->mianownik=mianownik;
    return u;
}
void nowy_ulamek2(int licznik,int mianownik, Ulamek *u)
{
    if(mianownik<0){
        licznik*=(-1);
        mianownik*=(-1);
    }
    if(mianownik==0){
        printf("BLAD! ZLY ULAMEK!\n");
        return;
        }
    int dzielnik= NWD(licznik,mianownik);
    licznik/=dzielnik;
    mianownik/=dzielnik;
    u->licznik=licznik;
    u->mianownik=mianownik;
    return;
}
Ulamek *dodaj(Ulamek *u1, Ulamek *u2)
{
    int licznik,mianownik;
    mianownik=NWW(u1->mianownik,u2->mianownik);
    licznik=(u1->licznik)*(mianownik/(u1->mianownik)) + (u2->licznik)*(mianownik/(u2->mianownik));
    Ulamek *wynik=nowy_ulamek(licznik,mianownik);
    return wynik;
}
void dodaj2(Ulamek *u1, Ulamek *u2, Ulamek *u)
{
    int licznik,mianownik;
    mianownik=NWW(u1->mianownik,u2->mianownik);
    licznik=(u1->licznik)*(mianownik/(u1->mianownik)) + (u2->licznik)*(mianownik/(u2->mianownik));
    nowy_ulamek2(licznik,mianownik,u);
    return;
}
Ulamek *odejmij(Ulamek *u1, Ulamek *u2)
{
    int licznik,mianownik;
    mianownik=NWW(u1->mianownik,u2->mianownik);
    licznik=(u1->licznik)*(mianownik/(u1->mianownik)) - (u2->licznik)*(mianownik/(u2->mianownik));
    Ulamek *wynik=nowy_ulamek(licznik,mianownik);
    return wynik;
}
void odejmij2(Ulamek *u1, Ulamek *u2, Ulamek *u)
{
    int licznik,mianownik;
    mianownik=NWW(u1->mianownik,u2->mianownik);
    licznik=(u1->licznik)*(mianownik/(u1->mianownik)) - (u2->licznik)*(mianownik/(u2->mianownik));
    nowy_ulamek2(licznik,mianownik,u);
    return;

}
Ulamek *pomnoz(Ulamek *u1, Ulamek *u2)
{
    int licznik,mianownik;
    mianownik=(u1->mianownik)*(u2->mianownik);
    licznik=(u1->licznik)*(u2->licznik);
    Ulamek *wynik=nowy_ulamek(licznik,mianownik);
    return wynik;
}
void pomnoz2(Ulamek *u1,Ulamek *u2, Ulamek *u)
{
    int licznik,mianownik;
    mianownik=(u1->mianownik)*(u2->mianownik);
    licznik=(u1->licznik)*(u2->licznik);
    nowy_ulamek2(licznik,mianownik,u);
    return;
}
Ulamek *podziel(Ulamek *u1, Ulamek *u2)
{
    int licznik,mianownik;
    mianownik=(u1->mianownik)*(u2->licznik);
    licznik=(u1->licznik)*(u2->mianownik);
    Ulamek *wynik=nowy_ulamek(licznik,mianownik);
    return wynik;
}
void podziel2(Ulamek *u1, Ulamek *u2, Ulamek *u)
{
    int licznik,mianownik;
    mianownik=(u1->mianownik)*(u2->licznik);
    licznik=(u1->licznik)*(u2->mianownik);
    nowy_ulamek2(licznik,mianownik,u);
    return;
}
void wypisz_ulamek(Ulamek *u)
{
    printf("%d / %d\n",u->licznik,u->mianownik);
    return;
}
