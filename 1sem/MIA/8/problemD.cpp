#include<iostream>
#include<map>
using namespace std;
map<int,int>mapka;
int jazda(int zbiornik,int d)
{
    int koszt1=0;koszt2=0;
    int maksymalny=zbiornik;
    for(int i=0;i<d;i++){
        if(zbiornik==0&&mapka[i]==0)
            return -1;
        if(mapka[i]!=0){
            zbiornik=maksymalny;
            koszt1=mapka[i];
        }
        zbiornik--;
    }
    int wynik=0;

    return wynik;
}
int main()
{
    int d,zbiornik,m,a,b;
    cin>>d>>zbiornik>>m;
    for(int i=0;i<m;i++){
        cin>>a>>b;
        mapka[a-1]=b;
    }
    cout<<jazda(zbiornik,d);
    return 0;
}
