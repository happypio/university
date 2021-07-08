#include<iostream>
using namespace std;
const int stala=(1<<17);
int drzewko[26][2*stala];

void dodaj(char c, int x)
{
    int a=c-'a',pozycja=stala+x;
    drzewko[a][pozycja]++;
    pozycja/=2;
    while(pozycja>=1){
        drzewko[a][pozycja]++;
        pozycja/=2;
    }

}
void usun(char c,int x)
{
    int a=c-'a',pozycja=stala+x;
    drzewko[a][pozycja]--;
    pozycja/=2;
    while(pozycja>=1){
        drzewko[a][pozycja]--;
        pozycja/=2;
    }

}
int rozne_na_przedziale(int a,int b,int u,int i,int lo,int hi)
{

    if(a==lo&&b==hi){
        if(drzewko[i][u]>0)
            return 1;
        else
            return 0;
    }
    if(b<=a)
        return 0;
    int mid=(lo+hi)/2;
    if(rozne_na_przedziale(a,min(mid,b),2*u,i,lo,mid)||rozne_na_przedziale(max(mid,a),b,2*u+1,i,mid,hi))
        return 1;
    else
        return 0;
}
int rozne(int a,int b,int u,int lo,int hi)
{
    int wynik=0;
    for(int i=0;i<26;i++){
        wynik+=rozne_na_przedziale(a,b,u,i,lo,hi);
    }
    return wynik;
}
int main()
{
    ios_base::sync_with_stdio(false);
    string s;
    char c;
    int q,t,a,b,x;
    cin>>s>>q;
    for(int unsigned i=0;i<s.size();i++)
        dodaj(s[i],i);
    for(int i=0;i<q;i++){
            cin>>t;
        if(t==1){
            cin>>x>>c;
            usun(s[x-1],x-1);
            dodaj(c,x-1);
            s[x-1]=c;
        }
        else{
            cin>>a>>b;
            cout<<rozne(a-1,b,1,0,stala)<<endl;
        }
    }
    return 0;
}
