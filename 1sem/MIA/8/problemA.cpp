#include<iostream>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    int n,zero=0,jeden=0;
    string slowo;
    cin>>n>>slowo;
    for(int i=0;i<n;i++){
        if(slowo[i]=='0')
            zero++;
        else
            jeden++;
    }
    if(zero>jeden)
        cout<<zero-jeden;
    else
        cout<<jeden-zero;
    return 0;
}

