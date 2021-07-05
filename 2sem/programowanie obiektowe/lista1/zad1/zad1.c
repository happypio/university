#include<stdio.h>
#include<stdlib.h>
#include"funkcje.h"
const float PI = 3.141592;

Figura *t[100];

Figura *nowy_kwadrat(float x,float y,float wymiar)
{
    Figura *f=(Figura*)calloc(sizeof(Figura),1);
    f->x=x;
    f->y=y;
    if(wymiar < 0)
        printf("BLAD! Probowales utworzyc kwadrat o ujemnym wymiarze.");
    else
        f->wymiar=wymiar;
    f->figura= Kwadrat;
    return f;
}

Figura *nowy_trojkat(float x,float y,float x1, float y1,float wymiar)
{
    Figura *f=(Figura*)calloc(sizeof(Figura),1);
    if(y==y1){
        printf("BLAD! Nie uda sie utworzyc trojkata!");
        return f;
        }
    f->x=x;
    f->y=y;
    f->x1=x1;
    f->y1=y1;
    if(wymiar < 0)
        printf("BLAD! Probowales utworzyc trojkat o ujemnym wymiarze.");
    else
        f->wymiar=wymiar;
    f->figura= Trojkat;
    return f;
}

Figura *nowe_kolo(float x,float y,float wymiar)
{
    Figura *f=(Figura*)calloc(sizeof(Figura),1);
    f->x=x;
    f->y=y;
    if(wymiar < 0)
        printf("BLAD! Probowales utworzyc kolo o ujemnym promieniu.");
    else
        f->wymiar=wymiar;
    f->figura= Kolo;
    return f;
}

float modul(float a){
    if(a>0) return a;
    return -a;
}
float pole (Figura *f){
    float h = modul(f->y-f->y1);
    switch(f->figura)
    {
    case Trojkat:
        return (f->wymiar * h) / 2;
    break;
    case Kolo:
        return PI * f->wymiar * f->wymiar;
    break;
    case Kwadrat:
        return f->wymiar * f->wymiar;
    break;
    }
    return 0;
}

void przesun(Figura *f,float x,float y){
    if(f->figura==Trojkat){
        f->x1+=x;
        f->y1+=y;
    }
        f->x+=x;
        f->y+=y;
    return;
}

float sumapol(int size){
    float wynik=0;
    for(int i=0;i<size;i++)
        wynik+=pole(t[i]);
    return wynik;
}
