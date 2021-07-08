#include<iostream>
using namespace std;
const int stala=(1<<3);
int drzewko[stala*2];

int wartosc_w_punkcie(int x)
{
    int pozycja=x+stala;
    int wynik=drzewko[pozycja];
    pozycja/=2;
    while(pozycja>0){
        wynik=wynik+ drzewko[pozycja];
        pozycja/=2;
    }
    return wynik;

}

void dodaj_na_przedziale(int a,int b,int u,int lo,int hi,int wartosc)
{
    if(a==lo&&b==hi){
        drzewko[u]=drzewko[u]+wartosc;
        return;
    }
    if(b<=a) return;
    int mid=(lo+hi)/2;
    dodaj_na_przedziale(a,min(b,mid),2*u,lo,mid,wartosc);
    dodaj_na_przedziale(max(a,mid),b,2*u+1,mid,hi,wartosc);
}
int main()
{
    int ilosc_liczb_w_ciagu,x,a,b;
    cin>>ilosc_liczb_w_ciagu;
    for(int i=0;i<ilosc_liczb_w_ciagu;i++)
            cin>>drzewko[stala+i];
    cout<<"Co chcesz dodac i na jakim przedziale(1-n): ";
    cin>>x>>a>>b;
    dodaj_na_przedziale(a-1,b,1,0,stala,x);
    cout<<"Ktora liczbe chcesz odczytac z kolei (1-n)";
    cin>>x;
    cout<<wartosc_w_punkcie(x-1)<<endl;
    for(int i=0;i<2*stala;i++)
        cout<<drzewko[i]<<" ";

    return 0;
}
