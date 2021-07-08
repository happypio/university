#include<iostream>

using namespace std;

int czas=0,kolejka=0,uplyw=0,maksi=0;

int main()
{
    int n,pierwszy=1;
    cin>>n;
    for(int i=0;i<n;i++)
    {
        int t,c;
        cin>>t>>c;
        if(pierwszy){
            kolejka+=c;
        }
        else{
            uplyw=t-czas;
            kolejka=max(kolejka-=uplyw,0);
            kolejka+=c;
        }
        czas+=(t-czas);
        //cout<<czas<<" ";
        if(pierwszy)
            pierwszy=0;
        if(kolejka>maksi)
            maksi=kolejka;
    }
            cout<<czas+kolejka<<" "<<maksi;
    return 0;
}
