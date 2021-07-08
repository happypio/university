#include<iostream>
#include<map>
using namespace std;
map<long long,int>mapka;
map<long long,long long>mapka_mex;
void dodaj_na_przedziale(long long a,long long b,long long u,long long lo,long long hi)
{
    if(a==lo&&b==hi){
        mapka[u]=1;
        return;
    }
    if(b<=a) return;
    long long mid=(lo+hi)/2;
    dodaj_na_przedziale(a,min(b,mid),2*u,lo,mid);
    dodaj_na_przedziale(max(a,mid),b,2*u+1,mid,hi);
}
void usun_na_przedziale(long long a,long long b,long long u,long long lo,long long hi)
{
    if(a==lo&&b==hi){
        mapka[u]=0;
        return;
    }
    if(b<=a) return;
    long long mid=(lo+hi)/2;
    usun_na_przedziale(a,min(b,mid),2*u,lo,mid);
    usun_na_przedziale(max(a,mid),b,2*u+1,mid,hi);
}
long long mex_na_przedziale(long long a,long long b,long long u,long long lo,long long hi)
{
    if(a==lo&&b==hi){
        return mapka_mex[u];
    }
    if(b<=a) return 0;
    long long mid=(lo+hi)/2;
    //if(mapka_mex(2u==0))

    mex_na_przedziale(a,min(b,mid),2*u,lo,mid);
    mex_na_przedziale(max(a,mid),b,2*u+1,mid,hi);
}
int main()
{
    cout<<mapka[2];
    int n,q;
    long long l,r;
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>q>>l>>r;
        if(q==1){

        }
        else{
            if(q==2){

            }
            else{

            }
        }
    }

    return 0;
}
