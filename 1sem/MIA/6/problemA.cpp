#include<iostream>
using namespace std;
int main(){
    long long n,a=1,b=1,suma=0,temp;
    cin>>n;
    for(int i=1;i<=n;i++){
        suma=(suma+a)%1000000007,temp=a%1000000007,a=(a+b)%1000000007,b=temp;}
    cout<<suma;
    return 0;}
