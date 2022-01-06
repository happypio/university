#include<iostream>
#include<algorithm>
using namespace std;
int kolory[6];
int main()
{
    string slowo;
    cin>>slowo;
    for (int i=0;i<6;i++)
    {
        if(slowo[i]=='R')
            kolory[0]++;
        if(slowo[i]=='O')
            kolory[1]++;
        if(slowo[i]=='Y')
            kolory[2]++;
        if(slowo[i]=='G')
            kolory[3]++;
        if(slowo[i]=='B')
            kolory[4]++;
        if(slowo[i]=='V')
            kolory[5]++;
    }
    sort(kolory,kolory+6);
    if (kolory[5]==6)
        cout<<1;
    if (kolory[5]==5)
        cout<<1;
    if (kolory[5]==4)
        cout<<2;
    if (kolory[5]==3&&kolory[4]==3)
        cout<<2;
    if (kolory[5]==3&&kolory[4]==2)
        cout<<3;
    if (kolory[5]==3&&kolory[4]==1)
        cout<<5;
    if (kolory[5]==2&&kolory[4]==2&&kolory[3]==2)
        cout<<6;
    if (kolory[5]==2&&kolory[4]==2&&kolory[3]==1)
        cout<<8;
    if (kolory[5]==2&&kolory[4]==1)
        cout<<15;
    if (kolory[5]==1)
        cout<<30;
    return 0;
}
