#include<iostream>
#include<vector>
#include<utility>

using namespace std;

void dfs(bool dojscie[],vector< pair<int,int> >tab[],int x,int j)
{
    dojscie[x]=1;
    for(int unsigned i=0;i<tab[x].size();i++)
    {
        if(!dojscie[tab[x][i].first]&&tab[x][i].second==j)
        {
            dfs(dojscie,tab,tab[x][i].first,j);

        }
    }
}
int main()
{
    int m,n,a,b,c,q,u,v,wynik;
    cin>>n>>m;
    vector< pair<int,int> > drzewo[n+1];
    for(int i=0;i<m;i++){
        cin>>a>>b>>c;
        drzewo[a].push_back(make_pair(b,c));
        drzewo[b].push_back(make_pair(a,c));
    }
    cin>>q;
    for(int i=0;i<q;i++){
        cin>>u>>v;
        wynik=0;
        for(int j=1;j<101;j++){
            bool dojscie[105]={0};
            dfs(dojscie,drzewo,u,j);
            if(dojscie[v])
                wynik++;
        }
        cout<<wynik<<endl;
    }
    return 0;
}
