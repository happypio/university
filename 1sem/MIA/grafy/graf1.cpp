#include<iostream>
#include<vector>

using namespace std;

void dfs(bool dojscie[],vector<int>tab[],int x)
{
    dojscie[x]=1;
    for(int unsigned i=0;i<tab[x].size();i++)
    {
        if(!dojscie[tab[x][i]])
            dfs(dojscie,tab,tab[x][i]);
    }
}

int main()
{
    int n,k,a,b;//ilosc wierzcholkow i krawedzi i zmienne na krawedzie
    cout<<"wprowadz liczbe wierzcholkow i krawedzi:"<<endl;
        cin>>n>>k;
    vector<int> tab[n];
    cout<<"wprowadz z ktorego wierzcholka do ktorego mozna sie przemiescic:"<<endl;
    for(int i=0;i<k;i++)
    {
        cin>>a>>b;
        tab[a].push_back(b);
    }
    for(int i=0;i<n;i++)
    {
        cout<<"wierzcholek "<<i<<endl;
        for(int unsigned j=0;j<tab[i].size();j++)
        cout<<tab[i][j]<<" ";
    cout<<endl;
    }
    //robimy dfs
    bool dojscie[n]={0};
    dfs(dojscie,tab,1);
    for(int i=0;i<n;i++)
    {
        cout<<"do wierzchloka "<<i;
        if(dojscie[i])
            cout<<" da sie dojsc"<<endl;
        else
            cout<<" nie da sie dojsc"<<endl;
    }


}
