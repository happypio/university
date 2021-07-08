#include<iostream>

using namespace std;

int main()
{
    cout<<"wprowadz liczbe wierzcholkow i krawedzi"<<endl;
    int n,m,a,b;
    cin>>n>>m;
    int t[n][n];
    cout<<endl<<"a teraz wprowadz z ktoego wierzcholka do ktorego mozna sie przemiescic"<<endl;
    for(int i=0;i<n;i++)
    for(int j=0;j<n;j++)
        t[i][j]=0;
    for(int i=0;i<m;i++)
    {
        cin>>a>>b;
        t[a][b]=2;

    }
        for(int i=0;i<n;i++)
    {

            for(int j=0;j<n;j++)
        cout<<t[i][j]<<" ";
        cout<<endl;
    }


    return 0;
}
