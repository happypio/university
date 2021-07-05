#include<stdio.h>
#include<stdlib.h>
#include "funkcje.h"

int main(void)
{
    float x,y,x1,y1,wymiar;
    printf("Podaj wspolrzedne lewego dolnego wierzcholka kwadratu oraz dlugosc jego boku: \n");
    scanf("%f %f %f",&x, &y, &wymiar);
    t[0]=nowy_kwadrat(x,y,wymiar);
    printf("Podaj wspolrzedne lewego dolnego wierzcholka trojkata, gornego wierzcholka oraz dlugosc jego podstawy: \n");
    scanf("%f %f %f %f %f",&x, &y,&x1, &y1, &wymiar);
    t[1]=nowy_trojkat(x,y,x1,y1,wymiar);
    printf("Podaj wspolrzedne srodka kola oraz dlugosc jego promienia: \n");
    scanf("%f %f %f",&x, &y, &wymiar);
    t[2]=nowe_kolo(x,y,wymiar);
    printf("Pole kwadratu to: %f , pole kola to: %f , pole trojkata to: %f \n",pole(t[0]),pole(t[1]),pole(t[2]));
    printf("Suma pol figur w tablicy to: %f\n",sumapol(3));

    printf("Stare wspolrzedne dolnego wierzcholka kwadratu to: %f %f \n",t[0]->x,t[0]->y);
    printf("Stare wspolrzedne dolnego wierzcholka i gornego wierzcholka trojkata to: %f %f %f %f\n",t[1]->x,t[1]->y,t[1]->x1,t[1]->y1);
    printf("Stare wspolrzedne srodka kola to: %f %f \n",t[2]->x,t[2]->y);

    printf("O jaki wektor chcesz przesunac kwadrat? \n");
    scanf("%f %f",&x, &y);
    przesun(t[0],x,y);
    printf("O jaki wektor chcesz przesunac trojkat? \n");
    scanf("%f %f",&x, &y);
    przesun(t[1],x,y);
    printf("O jaki wektor chcesz przesunac kolo? \n");
    scanf("%f %f", &x, &y);
    przesun(t[2],x,y);

    printf("Nowe wspolrzedne dolnego wierzcholka kwadratu to: %f %f \n",t[0]->x,t[0]->y);
    printf("Nowe wspolrzedne dolnego wierzcholka i gornego wierzcholka trojkata to: %f %f %f %f\n",t[1]->x,t[1]->y,t[1]->x1,t[1]->y1);
    printf("Nowe wspolrzedne srodka kola to: %f %f \n",t[2]->x,t[2]->y);
}
