#include<iostream>
using namespace std;
int first[100005],second[100005],duzy=0,grupa=0,stala=0,zapisane=0;
long long wynik=0,suma1=0,suma2=0;
int main()
{
    int m,n;
    cin>>m>>n;
    for(int i=0;i<m;i++){
        cin>>first[i];
        if(first[i]>duzy){
            duzy=first[i];
            zapisane=i;
            grupa=0;
        }
        suma1+=first[i];
    }
    for(int i=0;i<n;i++){
        cin>>second[i];
        if(second[i]>duzy){
            duzy=second[i];
            zapisane=i;
            grupa=1;
        }
        suma2+=second[i];
    }
    if(grupa){
        wynik+=suma1;
         for(int i=0;i<n;i++){
        if(i!=zapisane){
            if(suma1<second[i])
                wynik+=suma1;
            else
                wynik+=second[i];
        }
    }
    }
    else{
        wynik+=suma2;
         for(int i=0;i<m;i++){
        if(i!=zapisane){
            if(suma2<first[i])
                wynik+=suma2;
            else
                wynik+=first[i];
        }
    }
    }
        cout<<wynik;
    return 0;
}
