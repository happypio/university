#include<iostream>
using namespace std;
int p[1001];
int main()
{
    int n,m,k,dif,wynik=0,licznik;
    cin>>n>>m>>k;
    for(int i=1;i<=m+1;i++)
    {
        cin>>p[i];
    }
    for(int i=1;i<=m;i++)
    {
        licznik=0;
        dif=p[i]^p[m+1];
        while(dif>0){
            if((dif&1)==1)
                licznik++;
            dif/=2;
        }
        if(licznik<=k)
            wynik++;
    }
    cout<<wynik<<endl;
    return 0;
}
