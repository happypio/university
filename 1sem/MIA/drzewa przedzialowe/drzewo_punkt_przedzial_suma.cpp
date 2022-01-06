#include<iostream>
using namespace std;

void dodawanie_elementu(int x,int wartosc,int liscie,int drzewo[])
{
    int pozycja=x+liscie;
    drzewo[pozycja]=wartosc;
    pozycja/=2;
    while(pozycja>0){
        drzewo[pozycja]=drzewo[2*pozycja]+drzewo[2*pozycja+1];
        pozycja/=2;
    }

}

int suma_na_przedziale(int a,int b,int u,int lo,int hi,int drzewo[])
{
    if(a==lo&&b==hi)
        return drzewo[u];
    if(b<=a) return 0;
    int mid=(lo+hi)/2;
    int L=suma_na_przedziale(a,min(b,mid),2*u,lo,mid,drzewo);
    int R=suma_na_przedziale(max(a,mid),b,2*u+1,mid,hi,drzewo);
    return L+R;
}
int main()
{
    int ilosc_liczb_w_ciagu,liscie=1,n,a,b;
    cin>>ilosc_liczb_w_ciagu;
    for(;liscie<ilosc_liczb_w_ciagu;liscie=liscie*2);
    int drzewo[2*liscie]={0};
    for(int i=0;i<ilosc_liczb_w_ciagu;i++){
            cin>>n;
            dodawanie_elementu(i,n,liscie,drzewo);
    }
    cout<<endl<<"Wpisz przedzial od ktorego chcesz sume:";//od 1 do n (potem konwertujemy na tablice)
        cin>>a>>b;
        cout<<endl<<"suma to: "<<suma_na_przedziale(a-1,(b-1)+1,1,0,liscie,drzewo)<<endl;

    for(int i=0;i<2*liscie;i++)
        cout<<drzewo[i]<<" ";


    return 0;
}
