#include<iostream>
#include<map>
using namespace std;
map<long long,long long>mapka;
long long bylem_tu;
void operacja_1(long long u,long long v,int w)
{

    while(u!=v){
        if(u>v){
            mapka[u]+=w;
            u/=2;
        }
        else{
            mapka[v]+=w;
            v/=2;
        }
    }
}
long long operacja_2(long long u,long long v)
{
    long long wynik=0;
    while(u!=v){
        if(u>v){
            wynik+=mapka[u];
            u/=2;
        }
        else{
            wynik+=mapka[v];
            v/=2;
        }

    }
    return wynik;
}
int main()
{
    int q,g,w;
    long long u,v;
    cin>>q;
    for(int i=0;i<q;i++){
        cin>>g;
        if(g==1){
            cin>>u>>v>>w;
            operacja_1(u,v,w);
        }
        else{
            cin>>u>>v;
            cout<<operacja_2(u,v)<<endl;
        }
    }
    return 0;
}
