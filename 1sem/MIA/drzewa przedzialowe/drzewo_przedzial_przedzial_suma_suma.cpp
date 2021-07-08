#include<iostream>
#include<climits>
using namespace std;
const int stala=(1<<3);
int drzewkoS[stala*2],drzewkoS2[stala*2];

void dodawanie_elementu(int x,int wartosc)
{
    int pozycja=x+stala;
    drzewkoS2[pozycja]=wartosc;
    pozycja/=2;
    while(pozycja>0){
        drzewkoS2[pozycja]=drzewkoS2[2*pozycja]+drzewkoS2[2*pozycja+1];
        pozycja/=2;
     }

}

void dodaj_na_przedziale(int a,int b,int u,int lo,int hi,int wartosc)
{
    if(a==lo&&b==hi){
        drzewkoS[u]=drzewkoS[u]+wartosc;
        drzewkoS2[u]=drzewkoS2[u]+(hi-lo)*wartosc;
        return;
    }
    if(b<=a) return;
    int mid=(lo+hi)/2;
    dodaj_na_przedziale(a,min(b,mid),2*u,lo,mid,wartosc);
    dodaj_na_przedziale(max(a,mid),b,2*u+1,mid,hi,wartosc);
    drzewkoS2[u]=drzewkoS2[2*u]+drzewkoS2[2*u+1] +(hi-lo)*drzewkoS[u];
}
int suma_na_przedziale(int a,int b,int u,int lo,int hi)
{
    if(a==lo&&b==hi)
        return drzewkoS2[u];
    if(b<=a) return 0;
    int mid=(lo+hi)/2;
    int L=suma_na_przedziale(a,min(b,mid),2*u,lo,mid);
    int R=suma_na_przedziale(max(a,mid),b,2*u+1,mid,hi);
    return L+R+drzewkoS[u]*(b-a);
}
int main()
{
    int ilosc_liczb_w_ciagu,x,a,b;
    cin>>ilosc_liczb_w_ciagu;
    for(int i=0;i<ilosc_liczb_w_ciagu;i++){
            cin>>x;
            drzewkoS[stala+i]=x;
            dodawanie_elementu(i,x);
    }
    cout<<"Co chcesz dodac i na jakim przedziale(1-n): ";
    cin>>x>>a>>b;
    dodaj_na_przedziale(a-1,b,1,0,stala,x);
    cout<<"Podaj przedzial z ktorego chcesz odczytac sume(1-n)";
    cin>>a>>b;
    cout<<suma_na_przedziale(a-1,b,1,0,stala)<<endl;

    for(int i=0;i<2*stala;i++)
        cout<<drzewkoS[i]<<" ";
    cout<<endl;
    for(int i=0;i<2*stala;i++)
        cout<<drzewkoS2[i]<<" ";

    return 0;
}
