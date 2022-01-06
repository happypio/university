#include<iostream>
using namespace std;
long long unsigned drzewko[2*(1<<17)];
int stala;
string dec_to_bin(long long x)
{
    char a[100]={0};
    for(int i=0;x>0;i++){
        a[i]=x%2+'0';
        x=x/2;
    }
    return a;
}
long long bin_to_dec(string a)
{
    long long x=0;
    for(int i=a.size()-1;i>=0;i--){

        x=x*2+a[i]-'0';
    }
    return x;
}
string oor(string a,string b)
{
    char wynik[100]={0};
    string wiekszy;
    int mini=min(a.size(),b.size()),maksi=max(a.size(),b.size()),i=0;
    if(a.size()>=b.size())
        wiekszy=a;
    else
        wiekszy=b;
    for(;i<mini;i++){
        if(a[i]=='1'||b[i]=='1')
            wynik[i]='1';
        else
            wynik[i]='0';
    }
        for(;i<maksi;i++)
        wynik[i]=wiekszy[i];
    return wynik;
}
string xxor(string a,string b)
{
    char wynik[100]={0};
    string wiekszy;
    int maksi=max(a.size(),b.size()),mini=min(a.size(),b.size()),i=0;
    if(a.size()>=b.size())
        wiekszy=a;
    else
        wiekszy=b;
    for(;i<mini;i++){
        if(a[i]=='1'&&b[i]=='1')
            wynik[i]='0';
        else
            if(a[i]=='1'||b[i]=='1')
                wynik[i]='1';
            else
            wynik[i]='0';
    }
    for(;i<maksi;i++)
        wynik[i]=wiekszy[i];
    return wynik;
}
void dodaj_wartosc(int p,long long unsigned x)
{
    int i=0,pozycja=stala+p;
    drzewko[pozycja]=x;
    pozycja/=2;
    while(pozycja>0){
        if(i==0){
            //drzewko[pozycja]=oor(drzewko[2*pozycja],drzewko[2*pozycja+1]);
            drzewko[pozycja]=drzewko[2*pozycja]|drzewko[2*pozycja+1];
            i=1;
        }
        else{
            //drzewko[pozycja]=xxor(drzewko[2*pozycja],drzewko[2*pozycja+1]);
            drzewka[pozycja]=drzewko[2*pozycja]^drzewko[2*pozycja+1];
            i=0;
        }
        pozycja/=2;
    }

}
int main()
{
    ios_base::sync_with_stdio(false);
    int n,m,p;
    long long unsigned x;
    cin>>n>>m;
    stala=(1<<n);
    for(int i=0;i<(1<<n);i++){
        cin>>x;
        //string a=dec_to_bin(x);
        dodaj_wartosc(i,x);
    }
    for(int i=0;i<m;i++){
        cin>>p>>x;
        //string a=dec_to_bin(x);
        dodaj_wartosc(p-1,x);
        //long long wynik=bin_to_dec(drzewko[1]);
        cout<<drzewko[1]<<endl;
    }
    return 0;
}
