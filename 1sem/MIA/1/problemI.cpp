#include<iostream>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    long long n,a,b,maks_suma,maks_suma_w_miejscu;
    cin>>n>>a>>b;
    //long long t[n];
    //for(int i=0;i<n;i++)
        //cin>>t[i];
    long long x;
    cin>>x;
    maks_suma=x;
    maks_suma_w_miejscu=x;
    if(a>0)
    for(int i=1;i<n;i++)
    {
        cin>>x;
       if(x+maks_suma_w_miejscu>x)
            maks_suma_w_miejscu=x+maks_suma_w_miejscu;
       else
            maks_suma_w_miejscu=x;
        if(maks_suma_w_miejscu>maks_suma)
        maks_suma=maks_suma_w_miejscu;
    }

    if(a<0)
        for(int i=1;i<n;i++)
    {
        cin>>x;
       if(x+maks_suma_w_miejscu<x)
            maks_suma_w_miejscu=x+maks_suma_w_miejscu;
       else
            maks_suma_w_miejscu=x;
          if(maks_suma_w_miejscu<maks_suma)
        maks_suma=maks_suma_w_miejscu;
    }
    long long wynik;
    if(a==0)
        wynik=b;
    else
        wynik=a*maks_suma + b;
    cout<<wynik;

    return 0;
}
