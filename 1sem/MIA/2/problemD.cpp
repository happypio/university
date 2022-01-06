#include<iostream>
#include<vector>
#include<queue>
#include<utility>
using namespace std;
vector<pair<int,int> >drzewo[100005];
vector<int> droga;
int dist[100005],nastepny[1000050];
bool dojscie[100005];
int poprzednik=-1;
priority_queue<pair<int,int>, vector<pair<int,int> >, greater<pair<int,int> > > lista;

void dijikstra(int x)
{
    lista.push(make_pair(0,x));
    dist[x]=0;
    while(!lista.empty()){
        int u=lista.top().second;
        lista.pop();
        for(int unsigned i=0;i<drzewo[u].size();i++){
            int v=drzewo[u][i].second,weight=drzewo[u][i].first;
            if(dist[v]>dist[u]+weight){
                dist[v]=dist[u]+weight;
                nastepny[v]=u;
                lista.push(make_pair(dist[v],v));
            }
        }
    }

}

void dfs(int x,int p)
{
    dojscie[x]=1;
    for(int unsigned i=0;i<drzewo[x].size();i++){
        if(dojscie[drzewo[x][i].second]!=1){
            if(drzewo[x][i].second!=nastepny[x])
                dfs(drzewo[x][i].second,x);
        }
    }

    if(x==1 or x==poprzednik){
        droga.push_back(x);
        poprzednik=p;
    }
}
int main()
{
    int u,v,w,m,n,source=1;
    cin>>n>>m;
    for(int i=0;i<m;i++){
        cin>>u>>v>>w;
        drzewo[u].push_back(make_pair(w,v));
        drzewo[v].push_back(make_pair(w,u));
    }
    for(int i=0;i<n;i++)
        dist[i]=INT_MAX;
    dijikstra(source);
    dfs(0,0);
    if(dojscie[1]==0){
        cout<<"impossible"<<endl;
        return 0;
    }
    cout<<droga.size()<<" ";
    for(int i=droga.size()-1;i>=0;i--)
        cout<<droga[i]<<" ";
    cout<<endl;
    return 0;
}
