#include<iostream>
using namespace std;

int main()
{
    int zmienna,x, *adres;
    cin>>zmienna;
    adres=&zmienna;
    *adres=zmienna;
    cout<<adres<<" "<<*adres;
    *adres=2;
    cout<<" "<<zmienna<<adres<<endl;
    int **drugiw;
    drugiw=&adres;
    cout<<**drugiw<<endl;


    int tab[5];
    int *wskaz;
    wskaz=tab;
    wskaz++;
    *wskaz=2;
    cout<<tab[1]<<" ";
    cout<<wskaz;
    return 0;
}
