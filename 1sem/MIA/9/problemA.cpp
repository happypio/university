#include<iostream>
using namespace std;
string s;
int znaki[30];
void litery()
{
    for(int unsigned i=0;i<s.size();i++)
            znaki[s[i]-'a']++;
}
int main()
{
    int nieparzyste=0,parzyste=0;
    cin>>s;
    litery();
    for(int i=0;i<='z'-'a';i++){
        if(znaki[i]%2==1)
            nieparzyste++;
        else
            if(znaki[i]!=0)
                parzyste++;
    }
    //cout<<nieparzyste<<" "<<parzyste<<endl;
    if(nieparzyste==0&&parzyste>0)
        cout<<"First";
    else
        if(nieparzyste%2==1)
            cout<<"First";
        else
            cout<<"Second";
    return 0;
}
