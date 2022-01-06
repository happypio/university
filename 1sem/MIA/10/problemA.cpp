#include<iostream>
using namespace std;
int main()
{
    int n,m,poczatek;
    cin>>n>>m;
    poczatek=n/m;
    while(m>0){
        if(m*(poczatek+1)==n){
            cout<<poczatek+1<<" ";
            n=n-poczatek-1;
        }
        else{
            cout<<poczatek<<" ";
            n-=poczatek;
        }
        m--;
    }
    return 0;
}
