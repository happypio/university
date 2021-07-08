#include<iostream>
using namespace std;
int quarries;
long long gra(long long n){
    if(n%4==0)
        return n;
    if(n%4==1)
        return 1;
    if(n%4==2)
        return n+1;
    if(n%4==3)
        return 0;
}
int main()
{
    long long ciezarowki,kamienie,wynik=0;
    cin>>quarries;
    for(int i=0;i<quarries;i++){
        cin>>kamienie>>ciezarowki;
        wynik=wynik^(gra(kamienie-1)^gra(kamienie+ciezarowki-1));
    }
    if(wynik)
        cout<<"tolik";
    else
        cout<<"bolik";
    return 0;
}
