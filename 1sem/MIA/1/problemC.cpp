#include<iostream>
using namespace std;

unsigned long long rosyjskie_chlopy(long long a, long long b,long long m)
{
    unsigned long long wynik=0;
    while(a>0)
    {
        if(a%2==1)
            wynik=(wynik+b)%m;
        b=(b*2)%m;
        a=a/2;
    }
    return wynik;

}

int rozklad_binarny(int tab[],long long n)
{
    int i=0;
    while(n>0)
    {
        tab[i]=n%2;
        n=n/2;
        i++;
    }
    return i;

}

unsigned long long pot_mod(long long n, long long k, long long m, int z,int tab[])
{
    unsigned long long wynik=1,x=k%m;
    for(int i=0;i<z;i++)
    {
     if(tab[i]==1)
     {
        wynik=rosyjskie_chlopy(wynik,x,m)%m;
     }
     x=rosyjskie_chlopy(x,x,m);
     x=x%m;
    }
    return wynik;

}
int main()
{
    ios_base::sync_with_stdio(false);
    long long n,k,m,t,wynik;
    int tab[66],z;
    cin>>t;
    while (t>0)
        {
          cin>>n>>k>>m;
          z=rozklad_binarny(tab,n);
          wynik=pot_mod(n,k,m,z,tab);
            cout<<wynik<<endl;
          t--;
        }
        return 0;
}
