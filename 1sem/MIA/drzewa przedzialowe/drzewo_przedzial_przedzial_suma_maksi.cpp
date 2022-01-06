#include<iostream>
#include<climits>
using namespace std;
const int stala=(1<<3);
int drzewkoS[stala*2],drzewkoM[stala*2];
int male=INT_MIN;

void dodawanie_elementu(int x,int wartosc)
{
    int pozycja=x+stala;
    drzewkoM[pozycja]=wartosc;
    pozycja/=2;
    while(pozycja>0){
        drzewkoM[pozycja]=max(drzewkoM[2*pozycja],drzewkoM[2*pozycja+1]);
        pozycja/=2;
    }

}

void dodaj_na_przedziale(int a,int b,int u,int lo,int hi,int wartosc)
{
    if(a==lo&&b==hi){
        drzewkoS[u]=drzewkoS[u]+wartosc;
        drzewkoM[u]+=wartosc;
        return;
    }
    if(b<=a) return;
    int mid=(lo+hi)/2;
    dodaj_na_przedziale(a,min(b,mid),2*u,lo,mid,wartosc);
    dodaj_na_przedziale(max(a,mid),b,2*u+1,mid,hi,wartosc);
    drzewkoM[u]=max(drzewkoM[2*u],drzewkoM[2*u+1]);
}
int maks_na_przedziale(int a,int b,int u,int lo,int hi)
{
    if(a==lo&&b==hi)
        return drzewkoM[u];
    if(b<=a) return male;
    int mid=(lo+hi)/2;
    int L=maks_na_przedziale(a,min(b,mid),2*u,lo,mid);
    int R=maks_na_przedziale(max(a,mid),b,2*u+1,mid,hi);
    return max(L,R)+drzewkoS[u];
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
    cout<<"Podaj przedzial z ktorego chcesz odczytac max(1-n)";
    cin>>a>>b;
    cout<<maks_na_przedziale(a-1,b,1,0,stala)<<endl;

    for(int i=0;i<2*stala;i++)
        cout<<drzewkoS[i]<<" ";
    cout<<endl;
    for(int i=0;i<2*stala;i++)
        cout<<drzewkoM[i]<<" ";

    return 0;
}
