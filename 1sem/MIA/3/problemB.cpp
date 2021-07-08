#include<iostream>
using namespace std;
int canyon[2][100005];
bool dojscie[2][100005];
bool skoki(int pozycja,int n,int k,int sciana,int poziom)
{
    if(pozycja<=0||pozycja<=poziom) return false;
    if(pozycja>n) return true;
    if(canyon[sciana][pozycja]) return false;
    if(dojscie[sciana][pozycja]) return false;
    dojscie[sciana][pozycja]=true;
    if(skoki(pozycja+k,n,k,(sciana+1)%2,poziom+1)) return true;
    if(skoki(pozycja+1,n,k,sciana,poziom+1)) return true;
    if(skoki(pozycja-1,n,k,sciana,poziom+1)) return true;

    return false;

}
int main()
{
    ios_base::sync_with_stdio(false);
    int n,k;
    cin>>n>>k;
    char c;
    for(int j=0;j<2;j++)
        for(int i=1;i<=n;i++)
        {
            cin>>c;
            if(c=='X')
                canyon[j][i]=1;
            else
                canyon[j][i]=0;
        }

    if(skoki(1,n,k,0,0))
        cout<<"YES";
    else
        cout<<"NO";

    return 0;
}
