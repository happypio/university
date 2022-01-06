#include<iostream>
using namespace std;

int main()
{
    int szerokosc = 5,wysokosc=3;
    int **arr=new int*[wysokosc];
    for(int i=0;i<wysokosc;i++)
        arr[i]=new int [szerokosc];
    for(int i=0;i<3;i++)
        for(int j=0;j<5;j++)
        arr[i][j]=0;

        for(int i=0;i<3;i++)
        {
            cout<<"wiersz "<<i<<endl;
            for(int j=0;j<5;j++)
        {
            cout<<arr+i<<" "<<&arr[i]<<endl; //adres pierwszego rzedu wskaznikow (kolejnych tablic wskaznikow) czyli adres
        //wskaznika kierujacego na  poczatkowy wskaznik tablicy
            cout<<(*(arr+i))+j<<" "<<(arr[i])+j<<" "<<&arr[i][j]<<endl; //to na co wskazuje adres pierwszego rzedu wskaznikow
            //czyli na wskaznik, ktory jest adresem wartosci w danej komorce;
            cout<<*(arr[i]+j)<<" "<<arr[i][j]<<endl;//wartosci w danej komorce pod adresem wskaznika;
        }
            cout<<"koniec rzedu "<<i<<endl;
        }
    return 0;
}
