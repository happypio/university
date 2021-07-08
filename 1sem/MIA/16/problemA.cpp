#include<iostream>
#include<bits/stdc++.h>
using namespace std;
int a[19]={4,9,25,49,2,3,5,7,11,13,17,19,23,29,31,37,41,43,47};
int main()
{
    string odpowiedz;
    int dzielniki=1;
    for(int i=0;i<19;i++){
        cout<<a[i]<<endl;
        fflush(stdout);
        cin>>odpowiedz;
        if(odpowiedz[0]=='y')
            dzielniki++;
        if(dzielniki>2)
            i=20;
    }
    if(dzielniki>2)
        cout<<"composite";
    else
        cout<<"prime";
    fflush(stdout);
    return 0;
}
